/****************************************************************************
** Meta object code from reading C++ file 'jlhcrequestbase.h'
**
** Created: Fri Aug 19 08:59:41 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/service/jlhcrequestbase.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'jlhcrequestbase.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_JLhcRequestBase[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      33,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_JLhcRequestBase[] = {
    "JLhcRequestBase\0\0lhcResult(bool)\0"
    "on_socket_rcvLoginHashConfirm(bool)\0"
};

const QMetaObject JLhcRequestBase::staticMetaObject = {
    { &JRequestBase::staticMetaObject, qt_meta_stringdata_JLhcRequestBase,
      qt_meta_data_JLhcRequestBase, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &JLhcRequestBase::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *JLhcRequestBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *JLhcRequestBase::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_JLhcRequestBase))
        return static_cast<void*>(const_cast< JLhcRequestBase*>(this));
    return JRequestBase::qt_metacast(_clname);
}

int JLhcRequestBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = JRequestBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: lhcResult((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: on_socket_rcvLoginHashConfirm((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void JLhcRequestBase::lhcResult(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
