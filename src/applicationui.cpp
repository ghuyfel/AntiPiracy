/*
 * Copyright (c) 2011-2015 BlackBerry Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "applicationui.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>

using namespace bb::cascades;

ApplicationUI::ApplicationUI() :
        QObject()
{
    /*
     *
     * DON'T FORGET TO ADD THIS TO YOUR PRO FILE :
     * LIBS += -lbb -lbbsystem
     *
     */


    // Instantiate the object before creating the object if you need to access it from QML
    m_installSourceLocator = new InstallSourceLocator(this);

    // Create scene document from main.qml asset, the parent is set
    // to ensure the document gets destroyed properly at shut down.
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);

    // Make the object accessible from QML (if you need it, not mandatory)
    qml->setContextProperty("_installSourceLocator", m_installSourceLocator);

    // Create root object for the UI
    AbstractPane *root = qml->createRootObject<AbstractPane>();

    // Set created root object as the application scene
    Application::instance()->setScene(root);

    // This will delete the object when the checkup is done, for freeing memory when it's not needed anymore.
    // You don't have to delete it if you want to have access to its Q_PROPERTY later.
    bool ok = connect(m_installSourceLocator, SIGNAL(okToDelete()), m_installSourceLocator, SLOT(deleteLater()));
    Q_ASSERT(ok);
    Q_UNUSED(ok);

    // Change the unlock key to whatever you want.
    // You may want to delete the unlock key from your own server instead of hard coding it.
    bool unlockKeyChanged = m_installSourceLocator->setUnlockKey("MyUnlockKey");
    if (!unlockKeyChanged)
        qDebug() << "Error while saving unlock key, default unlock key is your vendor name as stated in bar-descriptor.xml";

    // This function must be called after your UI is created (after setScene(root) )
    m_installSourceLocator->checkIfDownloadedFromBBW();
}
