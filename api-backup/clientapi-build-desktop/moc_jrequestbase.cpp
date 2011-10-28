/****************************************************************************
** Meta object code from reading C++ file 'jrequestbase.h'
**
** Created: Fri Aug 19 08:59:41 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/service/jrequestbase.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'jrequestbase.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_JRequestBase[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,
      34,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      47,   42,   13,   13, 0x08,
      75,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_JRequestBase[] = {
    "JRequestBase\0\0connectResult(bool)\0"
    "error()\0code\0on_socket_SocketCode(JCode)\0"
    "on_socket_SocketError(QString)\0"
};

const QMetaObject JRequestBase::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_JRequestBase,
      qt_meta_data_JRequestBase, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &JRequestBase::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *JRequestBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *JRequestBase::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_JRequestBase))
        return static_cast<void*>(const_cast< JRequestBase*>(this));
    return QObject::qt_metacast(_clname);
}

int JRequestBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: connectResult((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: error(); break;
        case 2: on_socket_SocketCode((*reinterpret_cast< JCode(*)>(_a[1]))); break;
        case 3: on_socket_SocketError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void JRequestBase::connectResult(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void JRequestBase::error()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
