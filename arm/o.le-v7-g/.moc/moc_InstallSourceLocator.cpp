/****************************************************************************
** Meta object code from reading C++ file 'InstallSourceLocator.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/InstallSourceLocator/InstallSourceLocator.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'InstallSourceLocator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_InstallSourceLocator[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       2,   39, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   21,   21,   21, 0x05,
      55,   21,   21,   21, 0x05,
      76,   21,   21,   21, 0x05,
      89,   21,   21,   21, 0x05,

 // slots: signature, parameters, type, tag, flags
     122,   21,   21,   21, 0x08,

 // properties: name, type, flags
     181,  176, 0x01495103,
     209,  201, 0x0a495103,

 // properties: notify_signal_id
       0,
       3,

       0        // eod
};

static const char qt_meta_stringdata_InstallSourceLocator[] = {
    "InstallSourceLocator\0\0"
    "appInstalledFromBBWChanged(bool)\0"
    "errorString(QString)\0okToDelete()\0"
    "sourceOfDownloadChanged(QString)\0"
    "onKeyPromptFinished(bb::system::SystemUiResult::Type)\0"
    "bool\0appInstalledFromBBW\0QString\0"
    "sourceOfDownload\0"
};

void InstallSourceLocator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        InstallSourceLocator *_t = static_cast<InstallSourceLocator *>(_o);
        switch (_id) {
        case 0: _t->appInstalledFromBBWChanged((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 1: _t->errorString((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->okToDelete(); break;
        case 3: _t->sourceOfDownloadChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->onKeyPromptFinished((*reinterpret_cast< bb::system::SystemUiResult::Type(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData InstallSourceLocator::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject InstallSourceLocator::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_InstallSourceLocator,
      qt_meta_data_InstallSourceLocator, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &InstallSourceLocator::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *InstallSourceLocator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *InstallSourceLocator::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_InstallSourceLocator))
        return static_cast<void*>(const_cast< InstallSourceLocator*>(this));
    return QObject::qt_metacast(_clname);
}

int InstallSourceLocator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = getAppInstalledFromBBW(); break;
        case 1: *reinterpret_cast< QString*>(_v) = getSourceOfDownload(); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setAppInstalledFromBBW(*reinterpret_cast< bool*>(_v)); break;
        case 1: setSourceOfDownload(*reinterpret_cast< QString*>(_v)); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void InstallSourceLocator::appInstalledFromBBWChanged(const bool & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void InstallSourceLocator::errorString(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void InstallSourceLocator::okToDelete()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void InstallSourceLocator::sourceOfDownloadChanged(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
