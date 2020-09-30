/****************************************************************************
** Meta object code from reading C++ file 'usbdev.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "usbdev.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'usbdev.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_usbdev_t {
    QByteArrayData data[17];
    char stringdata0[160];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_usbdev_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_usbdev_t qt_meta_stringdata_usbdev = {
    {
QT_MOC_LITERAL(0, 0, 6), // "usbdev"
QT_MOC_LITERAL(1, 7, 11), // "deviceReady"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 11), // "deviceError"
QT_MOC_LITERAL(4, 32, 5), // "errId"
QT_MOC_LITERAL(5, 38, 9), // "writeData"
QT_MOC_LITERAL(6, 48, 4), // "data"
QT_MOC_LITERAL(7, 53, 10), // "openDevice"
QT_MOC_LITERAL(8, 64, 11), // "closeDevice"
QT_MOC_LITERAL(9, 76, 13), // "setDeviceName"
QT_MOC_LITERAL(10, 90, 1), // "f"
QT_MOC_LITERAL(11, 92, 8), // "setSpeed"
QT_MOC_LITERAL(12, 101, 5), // "speed"
QT_MOC_LITERAL(13, 107, 19), // "getOscannLightReady"
QT_MOC_LITERAL(14, 127, 19), // "setOscannLightReady"
QT_MOC_LITERAL(15, 147, 5), // "value"
QT_MOC_LITERAL(16, 153, 6) // "parent"

    },
    "usbdev\0deviceReady\0\0deviceError\0errId\0"
    "writeData\0data\0openDevice\0closeDevice\0"
    "setDeviceName\0f\0setSpeed\0speed\0"
    "getOscannLightReady\0setOscannLightReady\0"
    "value\0parent"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_usbdev[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       2,   82, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,
       3,    1,   60,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   63,    2, 0x0a /* Public */,
       7,    0,   66,    2, 0x0a /* Public */,
       8,    0,   67,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
       9,    1,   68,    2, 0x02 /* Public */,
      11,    1,   71,    2, 0x02 /* Public */,
      13,    0,   74,    2, 0x02 /* Public */,
      14,    1,   75,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Bool,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Bool,
    QMetaType::Bool, QMetaType::Bool,   15,

 // constructors: parameters
    0x80000000 | 2, QMetaType::QObjectStar,   16,
    0x80000000 | 2,

 // constructors: name, argc, parameters, tag, flags
       0,    1,   78,    2, 0x0e /* Public */,
       0,    0,   81,    2, 0x2e /* Public | MethodCloned */,

       0        // eod
};

void usbdev::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { usbdev *_r = new usbdev((*reinterpret_cast< QObject*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        case 1: { usbdev *_r = new usbdev();
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        default: break;
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        usbdev *_t = static_cast<usbdev *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->deviceReady(); break;
        case 1: _t->deviceError((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 2: _t->writeData((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: { bool _r = _t->openDevice();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: _t->closeDevice(); break;
        case 5: _t->setDeviceName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->setSpeed((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 7: { bool _r = _t->getOscannLightReady();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 8: { bool _r = _t->setOscannLightReady((*reinterpret_cast< const bool(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (usbdev::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&usbdev::deviceReady)) {
                *result = 0;
            }
        }
        {
            typedef void (usbdev::*_t)(const int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&usbdev::deviceError)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject usbdev::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_usbdev.data,
      qt_meta_data_usbdev,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *usbdev::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *usbdev::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_usbdev.stringdata0))
        return static_cast<void*>(const_cast< usbdev*>(this));
    return QObject::qt_metacast(_clname);
}

int usbdev::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void usbdev::deviceReady()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void usbdev::deviceError(const int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
