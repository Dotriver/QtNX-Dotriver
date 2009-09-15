/****************************************************************************
** Meta object code from reading C++ file 'qtnxproxy.h'
**
** Created: Thu Jun 4 13:00:29 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qtnxproxy.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtnxproxy.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QtNXProxy[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      23,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QtNXProxy[] = {
    "QtNXProxy\0\0okPressed()\0cancelPressed()\0"
};

const QMetaObject QtNXProxy::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QtNXProxy,
      qt_meta_data_QtNXProxy, 0 }
};

const QMetaObject *QtNXProxy::metaObject() const
{
    return &staticMetaObject;
}

void *QtNXProxy::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtNXProxy))
        return static_cast<void*>(const_cast< QtNXProxy*>(this));
    return QDialog::qt_metacast(_clname);
}

int QtNXProxy::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: okPressed(); break;
        case 1: cancelPressed(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
