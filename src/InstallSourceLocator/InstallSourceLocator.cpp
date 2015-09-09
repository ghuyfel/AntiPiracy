/*
 * InstallSourceLocator.cpp
 *
 *  Created on: 2015-09-08
 *      Author: Roger
 */

#include "InstallSourceLocator.h"

#include <bb/cascades/Application>
#include <bb/PpsObject>
#include <bb/system/SystemUiResult>

#include <QDebug>
#include <QDir>
#include <QFileInfoList>
#include <QSettings>

using namespace bb::cascades;
using namespace bb::system;

InstallSourceLocator::InstallSourceLocator(QObject *_parent) :
    QObject(),
    m_keyPrompt(NULL),
    m_wrongKeyToast(NULL),
    m_appInstalledFromBBW(false),
    m_sourceOfDownload("")
{
    if (_parent) { this->setParent(_parent); }
}

void InstallSourceLocator::checkIfDownloadedFromBBW() {
    // The next code will check if the app was downloaded from BBW if the app runs in Release mode
    QDir dir("/pps/system/installer/appdetails/");
    dir.setFilter(QDir::Files | QDir::System | QDir::Hidden | QDir::NoDotAndDotDot | QDir::AllEntries);
    QFileInfoList fileInfoList = dir.entryInfoList();

    for (int i = 0; i < fileInfoList.size(); i++) {
        QString completePath = fileInfoList[i].path() + "/" + fileInfoList[i].fileName() + (fileInfoList[i].isDir() ? "/" : "");
        if (this->checkFile(completePath)) { break; };
    }

    // If the app runs in debug mode, it will fake like it was downloaded from BBW
    #if defined(QT_DEBUG)
        setAppInstalledFromBBW(true);
    #endif

    // If the unlock key was already provided, it will fake like it was downloaded from BBW
    QSettings settings;
    settings.beginGroup("InstallSourceLocator");
    if (settings.value("appIsLegit").toBool())
        this->setAppInstalledFromBBW(true);

    if (!this->getAppInstalledFromBBW()) {
        if (!m_keyPrompt) { m_keyPrompt = new SystemPrompt(this); }

        bool ok = connect(m_keyPrompt, SIGNAL(finished(bb::system::SystemUiResult::Type)), this, SLOT(onKeyPromptFinished(bb::system::SystemUiResult::Type)));
        Q_ASSERT(ok);
        if (!ok) {
            emit errorString("Couldn't connect to SystemPrompt finished signal");
            return;
        }

        m_keyPrompt->setTitle(tr("App downloaded from: ") + this->getSourceOfDownload());
        m_keyPrompt->setBody(tr("This app wasn't downloaded from BlackBerry World. Enter a key to unlock the app."));
        m_keyPrompt->show();
    }
}

bool InstallSourceLocator::checkFile(const QString& path) {
    bool installedFromBBW = false;
    bool appFound = false;

    bb::PpsObject ppsObject(path);
    if (ppsObject.open( bb::PpsOpenMode::Subscribe )) {
        bool readOk;
        QByteArray data = ppsObject.read(&readOk);
        if(!readOk) { return appFound; }

        QString packageName = Application::instance()->applicationDirPath();
        packageName.remove(0, packageName.indexOf("appdata/") + QString("appdata/").size());
        packageName = packageName.left(packageName.indexOf("/app/native"));

        if (data.contains(packageName.toUtf8())) {
            qDebug() << "App found:" << packageName;
            appFound = true;

            bool decodeOk;
            const QVariantMap map = bb::PpsObject::decode(data, &decodeOk);
            if(!decodeOk) { return appFound; }

            const QVariantMap ppsFile = map["@" + path.split("/").last()].toMap();
            if (ppsFile.isEmpty()) { return appFound; }

            QMapIterator<QString, QVariant> j(ppsFile);
            while (j.hasNext()) {
                j.next();

                if (j.key() != packageName)
                    continue;

                const QVariantMap thisApp = ppsFile[j.key()].toMap();
                QString extras = thisApp.value("extras").toString();

                QStringList allExtras = extras.split(",");
                for (int i = 0; i < allExtras.size(); i++) {
                    QStringList keyValue = allExtras[i].split("::");
                    if (!keyValue.isEmpty()) {
                        if (keyValue.first() == "source") {
                            qDebug() << keyValue;
                            this->setSourceOfDownload(keyValue.last());
                            installedFromBBW = (keyValue.last() == "AppWorld");
                            this->setAppInstalledFromBBW(installedFromBBW);
                            break;
                        }
                    }
                }
            }
        }
    }
    else {
        if (ppsObject.errorString() != "No such file or directory") {
            qDebug() << "Can't open file: " + ppsObject.errorString();
        }
    }
    ppsObject.close();

    return appFound;
}

QString InstallSourceLocator::getKeyToUnlock() {
    QSettings settings;
    settings.beginGroup("InstallSourceLocator");
    return settings.value("keyToUnlock", Application::instance()->organizationName()).toString();
}

void InstallSourceLocator::onKeyPromptFinished(SystemUiResult::Type type) {
    QSettings settings;
    settings.beginGroup("InstallSourceLocator");
    QString unlockKey = settings.value("unlockKey", Application::instance()->organizationName()).toString();

    if (!m_wrongKeyToast) { m_wrongKeyToast = new SystemToast(this); }
    m_wrongKeyToast->button()->setLabel(tr("Ok"));

    bool ok = connect(m_wrongKeyToast, SIGNAL(finished(bb::system::SystemUiResult::Type)), m_wrongKeyToast, SLOT(deleteLater()));
    ok = ok && connect(m_wrongKeyToast, SIGNAL(finished(bb::system::SystemUiResult::Type)), this, SIGNAL(okToDelete()));
    if (!ok) {
        emit errorString("Couldn't connect to SystemToast finished signal");
    }

    if ((type == SystemUiResult::ConfirmButtonSelection) && (m_keyPrompt->inputFieldTextEntry() == unlockKey)) {
        this->setAppIsLegit(true);
        m_wrongKeyToast->setBody(tr("App has been unlocked permanently. Thanks!"));
        m_wrongKeyToast->show();
    }
    else {
        bool ok = connect(m_wrongKeyToast, SIGNAL(finished(bb::system::SystemUiResult::Type)), Application::instance(), SLOT(quit()));
        if (!ok) {
            emit errorString("Couldn't connect to SystemToast finished signal");
            Application::instance()->quit();
        }
        m_wrongKeyToast->setBody(tr("Contact the developer if you want to unlock this app."));
        m_wrongKeyToast->show();
    }

    m_keyPrompt->deleteLater();
}

void InstallSourceLocator::setAppIsLegit(const bool& appIsLegit) {
    QSettings settings;
    settings.beginGroup("InstallSourceLocator");
    settings.setValue("appIsLegit", appIsLegit);
    this->setAppInstalledFromBBW(appIsLegit);
}

bool InstallSourceLocator::setUnlockKey(const QString& newKey) {
    QSettings settings;
    settings.beginGroup("InstallSourceLocator");
    settings.setValue("unlockKey", newKey);
    return (settings.value("unlockKey", "").toString() == newKey);
}
