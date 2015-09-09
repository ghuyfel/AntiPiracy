/*
 * InstallSourceLocator.h
 *
 *  Created on: 2015-09-08
 *      Author: Roger
 */

#ifndef INSTALLSOURCELOCATOR_H_
#define INSTALLSOURCELOCATOR_H_

#include <QObject>
#include <bb/system/SystemPrompt>
#include <bb/system/SystemToast>

class InstallSourceLocator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool appInstalledFromBBW READ getAppInstalledFromBBW WRITE setAppInstalledFromBBW NOTIFY appInstalledFromBBWChanged);
    Q_PROPERTY(QString sourceOfDownload READ getSourceOfDownload WRITE setSourceOfDownload NOTIFY sourceOfDownloadChanged);

public:
    InstallSourceLocator(QObject *_parent = 0);
    virtual ~InstallSourceLocator() {}

    void checkIfDownloadedFromBBW();
    bool setUnlockKey(const QString& newKey);

private Q_SLOTS:
    void onKeyPromptFinished(bb::system::SystemUiResult::Type);

private:
    bool getAppInstalledFromBBW() { return m_appInstalledFromBBW; }
    void setAppInstalledFromBBW(const bool& newValue) {
        if (m_appInstalledFromBBW != newValue) {
            m_appInstalledFromBBW = newValue;
            setAppIsLegit(m_appInstalledFromBBW);
            emit appInstalledFromBBWChanged(m_appInstalledFromBBW);
        }
    }

    QString getSourceOfDownload() { return m_sourceOfDownload; }
    void setSourceOfDownload(const QString& newValue) {
        if (m_sourceOfDownload != newValue) {
            m_sourceOfDownload = newValue;
            emit sourceOfDownloadChanged(m_sourceOfDownload);
        }
    }

    bool checkFile(const QString& path);
    QString getKeyToUnlock();
    void setAppIsLegit(const bool& appIsLegit);

    bb::system::SystemPrompt* m_keyPrompt;
    bb::system::SystemToast* m_wrongKeyToast;

    bool m_appInstalledFromBBW;
    QString m_sourceOfDownload;

signals:
    void appInstalledFromBBWChanged(const bool&);
    void errorString(const QString&);
    void okToDelete();
    void sourceOfDownloadChanged(const QString&);
};

#endif /* INSTALLSOURCELOCATOR_H_ */
