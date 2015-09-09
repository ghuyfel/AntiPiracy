Anti Piracy (beginner)
--------------
BB10 sample app that shows how to prevent your app from being pirated and used without being purchased from BlackBerry World (ie: sideloading a bar file)

If the app was sideloaded, a SystemPrompt will show asking to enter an unlock key (you can change the unlock key, default value is your vendor name). Providing an incorrect unlock key will close the app.

Note that if you run the app in debug mode or if an unlock key was already provided before, the code will fake like it was installed from BlackBerry World and the app will launch without asking anything.

Don't forget to include an unlock key to BlackBerry reviewers when submitting a release to BlackBerry World, as they are probably not downloading from BlackBerry World (maybe they are, I have no idea!).

This code was barely tested, I can't assure that it will work in all environments and all conditions. I can't be held responsible if this code doesn't work for your app, use at your own risk.



Here's what needs to be added to your project :

1) Copy "InstallSourceLocator" folder in your "src" folder

2) Add this to your ".pro" file :
```sh
LIBS += -lbb -lbbsystem
```

3) In "applicationui.hpp", add this :

```sh
#include "src/InstallSourceLocator/InstallSourceLocator.h"

// ...

private:
    InstallSourceLocator* m_installSourceLocator;

```

4) In "applicationui.cpp", add this to your constructor :

```sh
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

```



LICENSE
--------------
The MIT License (MIT)

Copyright (c) 2015 Roger Leblanc

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


(Translation: You can altere, copy, modify, or do whatever you want with this code and you don't need to thank me or give any credits)