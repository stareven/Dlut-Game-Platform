/****************************************************************************
** Meta object code from reading C++ file 'jrequestportsocket.h'
**
** Created: Fri Aug 19 08:59:40 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/network/jrequestportsocket.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'jrequestportsocket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_JRequestPortSocket[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x05,
      43,   19,   19,   19, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_JRequestPortSocket[] = {
    "JRequestPortSocket\0\0rcvPassLoginHash(bool)\0"
    "rcvServerPort(quint16)\0"
};

const QMetaObject JRequestPortSocket::staticMetaObject = {
    { &JSocketBase::staticMetaObject, qt_meta_stringdata_JRequestPortSocket,
      qt_meta_data_JRequestPortSocket, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &JRequestPortSocket::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *JRequestPortSocket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *JRequestPortSocket::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_JRequestPortSocket))
        return static_cast<void*>(const_cast< JRequestPortSocket*>(this));
    return JSocketBase::qt_metacast(_clname);
}

int JRequestPortSocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = JSocketBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: rcvPassLoginHash((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: rcvServerPort((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void JRequestPortSocket::rcvPassLoginHash(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void JRequestPortSocket::rcvServerPort(quint16 _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
