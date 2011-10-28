/****************************************************************************
** Meta object code from reading C++ file 'jconnectionbase.h'
**
** Created: Fri Aug 19 09:00:00 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/network/jconnectionbase.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'jconnectionbase.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_JConnectionBase[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x08,
      39,   16,   16,   16, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_JConnectionBase[] = {
    "JConnectionBase\0\0on_socket_readyRead()\0"
    "on_socket_disconnected()\0"
};

const QMetaObject JConnectionBase::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_JConnectionBase,
      qt_meta_data_JConnectionBase, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &JConnectionBase::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *JConnectionBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *JConnectionBase::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_JConnectionBase))
        return static_cast<void*>(const_cast< JConnectionBase*>(this));
    return QObject::qt_metacast(_clname);
}

int JConnectionBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_socket_readyRead(); break;
        case 1: on_socket_disconnected(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
