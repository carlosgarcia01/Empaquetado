/****************************************************************************
** Meta object code from reading C++ file 'oscann_adaptor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "oscann_adaptor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'oscann_adaptor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CVInterfaceAdaptor_t {
    QByteArrayData data[10];
    char stringdata0[461];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CVInterfaceAdaptor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CVInterfaceAdaptor_t qt_meta_stringdata_CVInterfaceAdaptor = {
    {
QT_MOC_LITERAL(0, 0, 18), // "CVInterfaceAdaptor"
QT_MOC_LITERAL(1, 19, 15), // "D-Bus Interface"
QT_MOC_LITERAL(2, 35, 16), // "aura.CVInterface"
QT_MOC_LITERAL(3, 52, 19), // "D-Bus Introspection"
QT_MOC_LITERAL(4, 72, 341), // "  <interface name=\"aura.CVIn..."
QT_MOC_LITERAL(5, 381, 18), // "changeSettingsDBus"
QT_MOC_LITERAL(6, 400, 0), // ""
QT_MOC_LITERAL(7, 401, 5), // "value"
QT_MOC_LITERAL(8, 407, 2), // "id"
QT_MOC_LITERAL(9, 410, 17) // "displayImagesDbus"

    },
    "CVInterfaceAdaptor\0D-Bus Interface\0"
    "aura.CVInterface\0D-Bus Introspection\0"
    "  <interface name=\"aura.CVInterface\">\n    <signal name=\"changeSett"
    "ingsDBus\">\n      <arg direction=\"out\" type=\"i\" name=\"value\"/>\n"
    "      <arg direction=\"out\" type=\"i\" name=\"id\"/>\n    </signal>\n"
    "    <signal name=\"displayImagesDbus\">\n      <arg direction=\"out\" "
    "type=\"b\" name=\"value\"/>\n    </signal>\n  </interface>\n\0"
    "changeSettingsDBus\0\0value\0id\0"
    "displayImagesDbus"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CVInterfaceAdaptor[] = {

 // content:
       7,       // revision
       0,       // classname
       2,   14, // classinfo
       2,   18, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // classinfo: key, value
       1,    2,
       3,    4,

 // signals: name, argc, parameters, tag, flags
       5,    2,   28,    6, 0x06 /* Public */,
       9,    1,   33,    6, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    7,    8,
    QMetaType::Void, QMetaType::Bool,    7,

       0        // eod
};

void CVInterfaceAdaptor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CVInterfaceAdaptor *_t = static_cast<CVInterfaceAdaptor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changeSettingsDBus((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->displayImagesDbus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CVInterfaceAdaptor::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CVInterfaceAdaptor::changeSettingsDBus)) {
                *result = 0;
            }
        }
        {
            typedef void (CVInterfaceAdaptor::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CVInterfaceAdaptor::displayImagesDbus)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject CVInterfaceAdaptor::staticMetaObject = {
    { &QDBusAbstractAdaptor::staticMetaObject, qt_meta_stringdata_CVInterfaceAdaptor.data,
      qt_meta_data_CVInterfaceAdaptor,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CVInterfaceAdaptor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CVInterfaceAdaptor::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CVInterfaceAdaptor.stringdata0))
        return static_cast<void*>(const_cast< CVInterfaceAdaptor*>(this));
    return QDBusAbstractAdaptor::qt_metacast(_clname);
}

int CVInterfaceAdaptor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDBusAbstractAdaptor::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void CVInterfaceAdaptor::changeSettingsDBus(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CVInterfaceAdaptor::displayImagesDbus(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_CapturerInterfaceAdaptor_t {
    QByteArrayData data[26];
    char stringdata0[1618];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CapturerInterfaceAdaptor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CapturerInterfaceAdaptor_t qt_meta_stringdata_CapturerInterfaceAdaptor = {
    {
QT_MOC_LITERAL(0, 0, 24), // "CapturerInterfaceAdaptor"
QT_MOC_LITERAL(1, 25, 15), // "D-Bus Interface"
QT_MOC_LITERAL(2, 41, 22), // "aura.CapturerInterface"
QT_MOC_LITERAL(3, 64, 19), // "D-Bus Introspection"
QT_MOC_LITERAL(4, 84, 1327), // "  <interface name=\"aura.Capt..."
QT_MOC_LITERAL(5, 1273, 19), // "newControlAddedDBus"
QT_MOC_LITERAL(6, 1293, 0), // ""
QT_MOC_LITERAL(7, 1294, 8), // "ctrlName"
QT_MOC_LITERAL(8, 1303, 6), // "ctrlID"
QT_MOC_LITERAL(9, 1310, 12), // "ctrlMinValue"
QT_MOC_LITERAL(10, 1323, 12), // "ctrlMaxValue"
QT_MOC_LITERAL(11, 1336, 9), // "ctrlValue"
QT_MOC_LITERAL(12, 1346, 20), // "newValidationImgDBus"
QT_MOC_LITERAL(13, 1367, 4), // "logo"
QT_MOC_LITERAL(14, 1372, 13), // "saveImageDbus"
QT_MOC_LITERAL(15, 1386, 9), // "timestamp"
QT_MOC_LITERAL(16, 1396, 5), // "msgTo"
QT_MOC_LITERAL(17, 1402, 10), // "signalTest"
QT_MOC_LITERAL(18, 1413, 17), // "statusChangedDBus"
QT_MOC_LITERAL(19, 1431, 10), // "cameraType"
QT_MOC_LITERAL(20, 1442, 5), // "width"
QT_MOC_LITERAL(21, 1448, 6), // "height"
QT_MOC_LITERAL(22, 1455, 3), // "fps"
QT_MOC_LITERAL(23, 1459, 15), // "updateImageDBus"
QT_MOC_LITERAL(24, 1475, 1), // "x"
QT_MOC_LITERAL(25, 1477, 1) // "y"

    },
    "CapturerInterfaceAdaptor\0D-Bus Interface\0"
    "aura.CapturerInterface\0D-Bus Introspection\0"
    "  <interface name=\"aura.CapturerInterface\">\n    <signal name=\"save"
    "ImageDbus\">\n      <arg direction=\"out\" type=\"s\" name=\"timestamp"
    "\"/>\n      <arg direction=\"out\" type=\"u\" name=\"msgTo\"/>\n    </"
    "signal>\n    <signal name=\"updateImageDBus\">\n      <arg direction=\""
    "out\" type=\"i\" name=\"x\"/>\n      <arg direction=\"out\" type=\"i\""
    " name=\"y\"/>\n      <arg direction=\"out\" type=\"i\" name=\"width\"/"
    ">\n      <arg direction=\"out\" type=\"i\" name=\"height\"/>\n    </si"
    "gnal>\n    <signal name=\"newValidationImgDBus\">\n      <arg directio"
    "n=\"out\" type=\"b\" name=\"logo\"/>\n    </signal>\n    <signal name="
    "\"newControlAddedDBus\">\n      <arg direction=\"out\" type=\"s\" name"
    "=\"ctrlName\"/>\n      <arg direction=\"out\" type=\"i\" name=\"ctrlID"
    "\"/>\n      <arg direction=\"out\" type=\"i\" name=\"ctrlMinValue\"/>\n"
    "      <arg direction=\"out\" type=\"i\" name=\"ctrlMaxValue\"/>\n     "
    " <arg direction=\"out\" type=\"i\" name=\"ctrlValue\"/>\n    </signal>"
    "\n    <signal name=\"statusChangedDBus\">\n      <arg direction=\"out\""
    " type=\"i\" name=\"cameraType\"/>\n      <arg direction=\"out\" type=\""
    "i\" name=\"width\"/>\n      <arg direction=\"out\" type=\"i\" name=\"h"
    "eight\"/>\n      <arg direction=\"out\" type=\"i\" name=\"fps\"/>\n   "
    " </signal>\n    <signal name=\"signalTest\"/>\n  </interface>\n\0"
    "newControlAddedDBus\0\0ctrlName\0ctrlID\0"
    "ctrlMinValue\0ctrlMaxValue\0ctrlValue\0"
    "newValidationImgDBus\0logo\0saveImageDbus\0"
    "timestamp\0msgTo\0signalTest\0statusChangedDBus\0"
    "cameraType\0width\0height\0fps\0updateImageDBus\0"
    "x\0y"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CapturerInterfaceAdaptor[] = {

 // content:
       7,       // revision
       0,       // classname
       2,   14, // classinfo
       6,   18, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // classinfo: key, value
       1,    2,
       3,    4,

 // signals: name, argc, parameters, tag, flags
       5,    5,   48,    6, 0x06 /* Public */,
      12,    1,   59,    6, 0x06 /* Public */,
      14,    2,   62,    6, 0x06 /* Public */,
      17,    0,   67,    6, 0x06 /* Public */,
      18,    4,   68,    6, 0x06 /* Public */,
      23,    4,   77,    6, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    7,    8,    9,   10,   11,
    QMetaType::Void, QMetaType::Bool,   13,
    QMetaType::Void, QMetaType::QString, QMetaType::UInt,   15,   16,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   19,   20,   21,   22,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   24,   25,   20,   21,

       0        // eod
};

void CapturerInterfaceAdaptor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CapturerInterfaceAdaptor *_t = static_cast<CapturerInterfaceAdaptor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newControlAddedDBus((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 1: _t->newValidationImgDBus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->saveImageDbus((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        case 3: _t->signalTest(); break;
        case 4: _t->statusChangedDBus((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 5: _t->updateImageDBus((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CapturerInterfaceAdaptor::*_t)(const QString & , int , int , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CapturerInterfaceAdaptor::newControlAddedDBus)) {
                *result = 0;
            }
        }
        {
            typedef void (CapturerInterfaceAdaptor::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CapturerInterfaceAdaptor::newValidationImgDBus)) {
                *result = 1;
            }
        }
        {
            typedef void (CapturerInterfaceAdaptor::*_t)(const QString & , uint );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CapturerInterfaceAdaptor::saveImageDbus)) {
                *result = 2;
            }
        }
        {
            typedef void (CapturerInterfaceAdaptor::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CapturerInterfaceAdaptor::signalTest)) {
                *result = 3;
            }
        }
        {
            typedef void (CapturerInterfaceAdaptor::*_t)(int , int , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CapturerInterfaceAdaptor::statusChangedDBus)) {
                *result = 4;
            }
        }
        {
            typedef void (CapturerInterfaceAdaptor::*_t)(int , int , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CapturerInterfaceAdaptor::updateImageDBus)) {
                *result = 5;
            }
        }
    }
}

const QMetaObject CapturerInterfaceAdaptor::staticMetaObject = {
    { &QDBusAbstractAdaptor::staticMetaObject, qt_meta_stringdata_CapturerInterfaceAdaptor.data,
      qt_meta_data_CapturerInterfaceAdaptor,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CapturerInterfaceAdaptor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CapturerInterfaceAdaptor::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CapturerInterfaceAdaptor.stringdata0))
        return static_cast<void*>(const_cast< CapturerInterfaceAdaptor*>(this));
    return QDBusAbstractAdaptor::qt_metacast(_clname);
}

int CapturerInterfaceAdaptor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDBusAbstractAdaptor::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void CapturerInterfaceAdaptor::newControlAddedDBus(const QString & _t1, int _t2, int _t3, int _t4, int _t5)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CapturerInterfaceAdaptor::newValidationImgDBus(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CapturerInterfaceAdaptor::saveImageDbus(const QString & _t1, uint _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CapturerInterfaceAdaptor::signalTest()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void CapturerInterfaceAdaptor::statusChangedDBus(int _t1, int _t2, int _t3, int _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void CapturerInterfaceAdaptor::updateImageDBus(int _t1, int _t2, int _t3, int _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
struct qt_meta_stringdata_DetectorInterfaceAdaptor_t {
    QByteArrayData data[16];
    char stringdata0[807];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DetectorInterfaceAdaptor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DetectorInterfaceAdaptor_t qt_meta_stringdata_DetectorInterfaceAdaptor = {
    {
QT_MOC_LITERAL(0, 0, 24), // "DetectorInterfaceAdaptor"
QT_MOC_LITERAL(1, 25, 15), // "D-Bus Interface"
QT_MOC_LITERAL(2, 41, 22), // "aura.DetectorInterface"
QT_MOC_LITERAL(3, 64, 19), // "D-Bus Introspection"
QT_MOC_LITERAL(4, 84, 647), // "  <interface name=\"aura.Dete..."
QT_MOC_LITERAL(5, 664, 11), // "loadingDBus"
QT_MOC_LITERAL(6, 676, 0), // ""
QT_MOC_LITERAL(7, 677, 7), // "percent"
QT_MOC_LITERAL(8, 685, 12), // "progressDBus"
QT_MOC_LITERAL(9, 698, 12), // "totalPercent"
QT_MOC_LITERAL(10, 711, 11), // "pupilAtDBus"
QT_MOC_LITERAL(11, 723, 1), // "x"
QT_MOC_LITERAL(12, 725, 1), // "y"
QT_MOC_LITERAL(13, 727, 2), // "sx"
QT_MOC_LITERAL(14, 730, 2), // "sy"
QT_MOC_LITERAL(15, 733, 5) // "ready"

    },
    "DetectorInterfaceAdaptor\0D-Bus Interface\0"
    "aura.DetectorInterface\0D-Bus Introspection\0"
    "  <interface name=\"aura.DetectorInterface\">\n    <signal name=\"prog"
    "ressDBus\">\n      <arg direction=\"out\" type=\"d\" name=\"percent\"/"
    ">\n      <arg direction=\"out\" type=\"d\" name=\"totalPercent\"/>\n  "
    "  </signal>\n    <signal name=\"loadingDBus\">\n      <arg direction=\""
    "out\" type=\"d\" name=\"percent\"/>\n    </signal>\n    <signal name=\""
    "ready\"/>\n    <signal name=\"pupilAtDBus\">\n      <arg direction=\"o"
    "ut\" type=\"d\" name=\"x\"/>\n      <arg direction=\"out\" type=\"d\" "
    "name=\"y\"/>\n      <arg direction=\"out\" type=\"d\" name=\"sx\"/>\n "
    "     <arg direction=\"out\" type=\"d\" name=\"sy\"/>\n    </signal>\n "
    " </interface>\n\0"
    "loadingDBus\0\0percent\0progressDBus\0"
    "totalPercent\0pupilAtDBus\0x\0y\0sx\0sy\0"
    "ready"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DetectorInterfaceAdaptor[] = {

 // content:
       7,       // revision
       0,       // classname
       2,   14, // classinfo
       4,   18, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // classinfo: key, value
       1,    2,
       3,    4,

 // signals: name, argc, parameters, tag, flags
       5,    1,   38,    6, 0x06 /* Public */,
       8,    2,   41,    6, 0x06 /* Public */,
      10,    4,   46,    6, 0x06 /* Public */,
      15,    0,   55,    6, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double,    7,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    7,    9,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double,   11,   12,   13,   14,
    QMetaType::Void,

       0        // eod
};

void DetectorInterfaceAdaptor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DetectorInterfaceAdaptor *_t = static_cast<DetectorInterfaceAdaptor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->loadingDBus((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->progressDBus((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 2: _t->pupilAtDBus((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 3: _t->ready(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DetectorInterfaceAdaptor::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DetectorInterfaceAdaptor::loadingDBus)) {
                *result = 0;
            }
        }
        {
            typedef void (DetectorInterfaceAdaptor::*_t)(double , double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DetectorInterfaceAdaptor::progressDBus)) {
                *result = 1;
            }
        }
        {
            typedef void (DetectorInterfaceAdaptor::*_t)(double , double , double , double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DetectorInterfaceAdaptor::pupilAtDBus)) {
                *result = 2;
            }
        }
        {
            typedef void (DetectorInterfaceAdaptor::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DetectorInterfaceAdaptor::ready)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject DetectorInterfaceAdaptor::staticMetaObject = {
    { &QDBusAbstractAdaptor::staticMetaObject, qt_meta_stringdata_DetectorInterfaceAdaptor.data,
      qt_meta_data_DetectorInterfaceAdaptor,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DetectorInterfaceAdaptor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DetectorInterfaceAdaptor::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DetectorInterfaceAdaptor.stringdata0))
        return static_cast<void*>(const_cast< DetectorInterfaceAdaptor*>(this));
    return QDBusAbstractAdaptor::qt_metacast(_clname);
}

int DetectorInterfaceAdaptor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDBusAbstractAdaptor::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void DetectorInterfaceAdaptor::loadingDBus(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DetectorInterfaceAdaptor::progressDBus(double _t1, double _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DetectorInterfaceAdaptor::pupilAtDBus(double _t1, double _t2, double _t3, double _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DetectorInterfaceAdaptor::ready()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}
struct qt_meta_stringdata_DisplayCTInterfaceAdaptor_t {
    QByteArrayData data[22];
    char stringdata0[1216];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DisplayCTInterfaceAdaptor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DisplayCTInterfaceAdaptor_t qt_meta_stringdata_DisplayCTInterfaceAdaptor = {
    {
QT_MOC_LITERAL(0, 0, 25), // "DisplayCTInterfaceAdaptor"
QT_MOC_LITERAL(1, 26, 15), // "D-Bus Interface"
QT_MOC_LITERAL(2, 42, 23), // "aura.DisplayCTInterface"
QT_MOC_LITERAL(3, 66, 19), // "D-Bus Introspection"
QT_MOC_LITERAL(4, 86, 943), // "  <interface name=\"aura.Disp..."
QT_MOC_LITERAL(5, 941, 14), // "closeVideoDbus"
QT_MOC_LITERAL(6, 956, 0), // ""
QT_MOC_LITERAL(7, 957, 15), // "deleteFilesDbus"
QT_MOC_LITERAL(8, 973, 14), // "finishDemoDbus"
QT_MOC_LITERAL(9, 988, 17), // "onCalibrationDBus"
QT_MOC_LITERAL(10, 1006, 5), // "value"
QT_MOC_LITERAL(11, 1012, 14), // "saveImagesDbus"
QT_MOC_LITERAL(12, 1027, 11), // "scatterDBus"
QT_MOC_LITERAL(13, 1039, 5), // "index"
QT_MOC_LITERAL(14, 1045, 19), // "stimuliOnViewerDBus"
QT_MOC_LITERAL(15, 1065, 4), // "flag"
QT_MOC_LITERAL(16, 1070, 17), // "stimulus2SaveDbus"
QT_MOC_LITERAL(17, 1088, 1), // "x"
QT_MOC_LITERAL(18, 1090, 1), // "y"
QT_MOC_LITERAL(19, 1092, 16), // "testDurationDBus"
QT_MOC_LITERAL(20, 1109, 4), // "time"
QT_MOC_LITERAL(21, 1114, 12) // "validateDBus"

    },
    "DisplayCTInterfaceAdaptor\0D-Bus Interface\0"
    "aura.DisplayCTInterface\0D-Bus Introspection\0"
    "  <interface name=\"aura.DisplayCTInterface\">\n    <signal name=\"tes"
    "tDurationDBus\">\n      <arg direction=\"out\" type=\"u\" name=\"time\""
    "/>\n    </signal>\n    <signal name=\"stimuliOnViewerDBus\">\n      <a"
    "rg direction=\"out\" type=\"b\" name=\"flag\"/>\n    </signal>\n    <s"
    "ignal name=\"finishDemoDbus\"/>\n    <signal name=\"saveImagesDbus\">\n"
    "      <arg direction=\"out\" type=\"b\" name=\"value\"/>\n    </signal"
    ">\n    <signal name=\"scatterDBus\">\n      <arg direction=\"out\" typ"
    "e=\"u\" name=\"index\"/>\n    </signal>\n    <signal name=\"validateDB"
    "us\"/>\n    <signal name=\"stimulus2SaveDbus\">\n      <arg direction="
    "\"out\" type=\"i\" name=\"x\"/>\n      <arg direction=\"out\" type=\"i"
    "\" name=\"y\"/>\n    </signal>\n    <signal name=\"closeVideoDbus\"/>\n"
    "    <signal name=\"deleteFilesDbus\"/>\n    <signal name=\"onCalibrati"
    "onDBus\">\n      <arg direction=\"out\" type=\"b\" name=\"value\"/>\n "
    "   </signal>\n  </interface>\n\0"
    "closeVideoDbus\0\0deleteFilesDbus\0"
    "finishDemoDbus\0onCalibrationDBus\0value\0"
    "saveImagesDbus\0scatterDBus\0index\0"
    "stimuliOnViewerDBus\0flag\0stimulus2SaveDbus\0"
    "x\0y\0testDurationDBus\0time\0validateDBus"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DisplayCTInterfaceAdaptor[] = {

 // content:
       7,       // revision
       0,       // classname
       2,   14, // classinfo
      10,   18, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // classinfo: key, value
       1,    2,
       3,    4,

 // signals: name, argc, parameters, tag, flags
       5,    0,   68,    6, 0x06 /* Public */,
       7,    0,   69,    6, 0x06 /* Public */,
       8,    0,   70,    6, 0x06 /* Public */,
       9,    1,   71,    6, 0x06 /* Public */,
      11,    1,   74,    6, 0x06 /* Public */,
      12,    1,   77,    6, 0x06 /* Public */,
      14,    1,   80,    6, 0x06 /* Public */,
      16,    2,   83,    6, 0x06 /* Public */,
      19,    1,   88,    6, 0x06 /* Public */,
      21,    0,   91,    6, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::UInt,   13,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   17,   18,
    QMetaType::Void, QMetaType::UInt,   20,
    QMetaType::Void,

       0        // eod
};

void DisplayCTInterfaceAdaptor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DisplayCTInterfaceAdaptor *_t = static_cast<DisplayCTInterfaceAdaptor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->closeVideoDbus(); break;
        case 1: _t->deleteFilesDbus(); break;
        case 2: _t->finishDemoDbus(); break;
        case 3: _t->onCalibrationDBus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->saveImagesDbus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->scatterDBus((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 6: _t->stimuliOnViewerDBus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->stimulus2SaveDbus((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->testDurationDBus((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 9: _t->validateDBus(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DisplayCTInterfaceAdaptor::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DisplayCTInterfaceAdaptor::closeVideoDbus)) {
                *result = 0;
            }
        }
        {
            typedef void (DisplayCTInterfaceAdaptor::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DisplayCTInterfaceAdaptor::deleteFilesDbus)) {
                *result = 1;
            }
        }
        {
            typedef void (DisplayCTInterfaceAdaptor::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DisplayCTInterfaceAdaptor::finishDemoDbus)) {
                *result = 2;
            }
        }
        {
            typedef void (DisplayCTInterfaceAdaptor::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DisplayCTInterfaceAdaptor::onCalibrationDBus)) {
                *result = 3;
            }
        }
        {
            typedef void (DisplayCTInterfaceAdaptor::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DisplayCTInterfaceAdaptor::saveImagesDbus)) {
                *result = 4;
            }
        }
        {
            typedef void (DisplayCTInterfaceAdaptor::*_t)(uint );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DisplayCTInterfaceAdaptor::scatterDBus)) {
                *result = 5;
            }
        }
        {
            typedef void (DisplayCTInterfaceAdaptor::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DisplayCTInterfaceAdaptor::stimuliOnViewerDBus)) {
                *result = 6;
            }
        }
        {
            typedef void (DisplayCTInterfaceAdaptor::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DisplayCTInterfaceAdaptor::stimulus2SaveDbus)) {
                *result = 7;
            }
        }
        {
            typedef void (DisplayCTInterfaceAdaptor::*_t)(uint );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DisplayCTInterfaceAdaptor::testDurationDBus)) {
                *result = 8;
            }
        }
        {
            typedef void (DisplayCTInterfaceAdaptor::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DisplayCTInterfaceAdaptor::validateDBus)) {
                *result = 9;
            }
        }
    }
}

const QMetaObject DisplayCTInterfaceAdaptor::staticMetaObject = {
    { &QDBusAbstractAdaptor::staticMetaObject, qt_meta_stringdata_DisplayCTInterfaceAdaptor.data,
      qt_meta_data_DisplayCTInterfaceAdaptor,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DisplayCTInterfaceAdaptor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DisplayCTInterfaceAdaptor::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DisplayCTInterfaceAdaptor.stringdata0))
        return static_cast<void*>(const_cast< DisplayCTInterfaceAdaptor*>(this));
    return QDBusAbstractAdaptor::qt_metacast(_clname);
}

int DisplayCTInterfaceAdaptor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDBusAbstractAdaptor::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void DisplayCTInterfaceAdaptor::closeVideoDbus()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void DisplayCTInterfaceAdaptor::deleteFilesDbus()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void DisplayCTInterfaceAdaptor::finishDemoDbus()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void DisplayCTInterfaceAdaptor::onCalibrationDBus(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void DisplayCTInterfaceAdaptor::saveImagesDbus(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void DisplayCTInterfaceAdaptor::scatterDBus(uint _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void DisplayCTInterfaceAdaptor::stimuliOnViewerDBus(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void DisplayCTInterfaceAdaptor::stimulus2SaveDbus(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void DisplayCTInterfaceAdaptor::testDurationDBus(uint _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void DisplayCTInterfaceAdaptor::validateDBus()
{
    QMetaObject::activate(this, &staticMetaObject, 9, Q_NULLPTR);
}
struct qt_meta_stringdata_GUIInterfaceAdaptor_t {
    QByteArrayData data[56];
    char stringdata0[3788];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GUIInterfaceAdaptor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GUIInterfaceAdaptor_t qt_meta_stringdata_GUIInterfaceAdaptor = {
    {
QT_MOC_LITERAL(0, 0, 19), // "GUIInterfaceAdaptor"
QT_MOC_LITERAL(1, 20, 15), // "D-Bus Interface"
QT_MOC_LITERAL(2, 36, 17), // "aura.GUIInterface"
QT_MOC_LITERAL(3, 54, 19), // "D-Bus Introspection"
QT_MOC_LITERAL(4, 74, 3216), // "  <interface name=\"aura.GUII..."
QT_MOC_LITERAL(5, 2948, 6), // "config"
QT_MOC_LITERAL(6, 2955, 0), // ""
QT_MOC_LITERAL(7, 2956, 4), // "rmin"
QT_MOC_LITERAL(8, 2961, 4), // "rmax"
QT_MOC_LITERAL(9, 2966, 9), // "cannyBlur"
QT_MOC_LITERAL(10, 2976, 10), // "cannyThld1"
QT_MOC_LITERAL(11, 2987, 10), // "cannyThld2"
QT_MOC_LITERAL(12, 2998, 15), // "StarburstPoints"
QT_MOC_LITERAL(13, 3014, 6), // "online"
QT_MOC_LITERAL(14, 3021, 10), // "configDbus"
QT_MOC_LITERAL(15, 3032, 4), // "task"
QT_MOC_LITERAL(16, 3037, 14), // "numberOfPoints"
QT_MOC_LITERAL(17, 3052, 5), // "sDist"
QT_MOC_LITERAL(18, 3058, 6), // "sWidth"
QT_MOC_LITERAL(19, 3065, 11), // "resolutionX"
QT_MOC_LITERAL(20, 3077, 11), // "resolutionY"
QT_MOC_LITERAL(21, 3089, 12), // "stimulusSize"
QT_MOC_LITERAL(22, 3102, 3), // "clb"
QT_MOC_LITERAL(23, 3106, 3), // "tst"
QT_MOC_LITERAL(24, 3110, 7), // "variant"
QT_MOC_LITERAL(25, 3118, 4), // "time"
QT_MOC_LITERAL(26, 3123, 4), // "laps"
QT_MOC_LITERAL(27, 3128, 9), // "frequency"
QT_MOC_LITERAL(28, 3138, 7), // "imgName"
QT_MOC_LITERAL(29, 3146, 13), // "directoryName"
QT_MOC_LITERAL(30, 3160, 7), // "fromRun"
QT_MOC_LITERAL(31, 3168, 17), // "configTrackerDBus"
QT_MOC_LITERAL(32, 3186, 5), // "width"
QT_MOC_LITERAL(33, 3192, 6), // "height"
QT_MOC_LITERAL(34, 3199, 13), // "frequencyDbus"
QT_MOC_LITERAL(35, 3213, 5), // "value"
QT_MOC_LITERAL(36, 3219, 14), // "keyPressedDbus"
QT_MOC_LITERAL(37, 3234, 3), // "key"
QT_MOC_LITERAL(38, 3238, 8), // "lapsDbus"
QT_MOC_LITERAL(39, 3247, 13), // "newD1FileDBus"
QT_MOC_LITERAL(40, 3261, 8), // "dataFile"
QT_MOC_LITERAL(41, 3270, 15), // "newSettingsDBus"
QT_MOC_LITERAL(42, 3286, 9), // "directory"
QT_MOC_LITERAL(43, 3296, 5), // "isTst"
QT_MOC_LITERAL(44, 3302, 5), // "codec"
QT_MOC_LITERAL(45, 3308, 15), // "normalStateDbus"
QT_MOC_LITERAL(46, 3324, 11), // "processDBus"
QT_MOC_LITERAL(47, 3336, 4), // "freq"
QT_MOC_LITERAL(48, 3341, 20), // "totalFramesToProcess"
QT_MOC_LITERAL(49, 3362, 14), // "saveImagesDbus"
QT_MOC_LITERAL(50, 3377, 16), // "sharedMemoryDbus"
QT_MOC_LITERAL(51, 3394, 12), // "showStimulus"
QT_MOC_LITERAL(52, 3407, 12), // "shutdownDBus"
QT_MOC_LITERAL(53, 3420, 4), // "type"
QT_MOC_LITERAL(54, 3425, 8), // "stopDBus"
QT_MOC_LITERAL(55, 3434, 10) // "methodName"

    },
    "GUIInterfaceAdaptor\0D-Bus Interface\0"
    "aura.GUIInterface\0D-Bus Introspection\0"
    "  <interface name=\"aura.GUIInterface\">\n    <signal name=\"normalSta"
    "teDbus\"/>\n    <signal name=\"saveImagesDbus\">\n      <arg direction"
    "=\"out\" type=\"b\" name=\"value\"/>\n    </signal>\n    <signal name="
    "\"frequencyDbus\">\n      <arg direction=\"out\" type=\"i\" name=\"val"
    "ue\"/>\n    </signal>\n    <signal name=\"lapsDbus\">\n      <arg dire"
    "ction=\"out\" type=\"i\" name=\"value\"/>\n    </signal>\n    <signal "
    "name=\"keyPressedDbus\">\n      <arg direction=\"out\" type=\"i\" name"
    "=\"key\"/>\n    </signal>\n    <signal name=\"configDbus\">\n      <ar"
    "g direction=\"out\" type=\"i\" name=\"task\"/>\n      <arg direction=\""
    "out\" type=\"i\" name=\"numberOfPoints\"/>\n      <arg direction=\"out"
    "\" type=\"d\" name=\"sDist\"/>\n      <arg direction=\"out\" type=\"d\""
    " name=\"sWidth\"/>\n      <arg direction=\"out\" type=\"i\" name=\"res"
    "olutionX\"/>\n      <arg direction=\"out\" type=\"i\" name=\"resolutio"
    "nY\"/>\n      <arg direction=\"out\" type=\"i\" name=\"stimulusSize\"/"
    ">\n      <arg direction=\"out\" type=\"i\" name=\"clb\"/>\n      <arg "
    "direction=\"out\" type=\"i\" name=\"tst\"/>\n      <arg direction=\"ou"
    "t\" type=\"i\" name=\"variant\"/>\n      <arg direction=\"out\" type=\""
    "i\" name=\"time\"/>\n      <arg direction=\"out\" type=\"i\" name=\"la"
    "ps\"/>\n      <arg direction=\"out\" type=\"i\" name=\"frequency\"/>\n"
    "      <arg direction=\"out\" type=\"s\" name=\"imgName\"/>\n      <arg"
    " direction=\"out\" type=\"s\" name=\"directoryName\"/>\n      <arg dir"
    "ection=\"out\" type=\"b\" name=\"fromRun\"/>\n    </signal>\n    <meth"
    "od name=\"methodName\"/>\n    <signal name=\"shutdownDBus\">\n      <a"
    "rg direction=\"out\" type=\"u\" name=\"type\"/>\n    </signal>\n    <s"
    "ignal name=\"newD1FileDBus\">\n      <arg direction=\"out\" type=\"s\""
    " name=\"dataFile\"/>\n    </signal>\n    <signal name=\"newSettingsDBu"
    "s\">\n      <arg direction=\"out\" type=\"s\" name=\"directory\"/>\n  "
    "    <arg direction=\"out\" type=\"s\" name=\"dataFile\"/>\n      <arg "
    "direction=\"out\" type=\"b\" name=\"isTst\"/>\n      <arg direction=\""
    "out\" type=\"s\" name=\"codec\"/>\n    </signal>\n    <signal name=\"c"
    "onfigTrackerDBus\">\n      <arg direction=\"out\" type=\"i\" name=\"wi"
    "dth\"/>\n      <arg direction=\"out\" type=\"i\" name=\"height\"/>\n  "
    "  </signal>\n    <signal name=\"sharedMemoryDbus\"/>\n    <signal name"
    "=\"config\">\n      <arg direction=\"out\" type=\"i\" name=\"rmin\"/>\n"
    "      <arg direction=\"out\" type=\"i\" name=\"rmax\"/>\n      <arg di"
    "rection=\"out\" type=\"d\" name=\"cannyBlur\"/>\n      <arg direction="
    "\"out\" type=\"d\" name=\"cannyThld1\"/>\n      <arg direction=\"out\""
    " type=\"d\" name=\"cannyThld2\"/>\n      <arg direction=\"out\" type=\""
    "i\" name=\"StarburstPoints\"/>\n      <arg direction=\"out\" type=\"b\""
    " name=\"online\"/>\n    </signal>\n    <signal name=\"processDBus\">\n"
    "      <arg direction=\"out\" type=\"s\" name=\"directory\"/>\n      <a"
    "rg direction=\"out\" type=\"i\" name=\"freq\"/>\n      <arg direction="
    "\"out\" type=\"i\" name=\"width\"/>\n      <arg direction=\"out\" type"
    "=\"i\" name=\"height\"/>\n      <arg direction=\"out\" type=\"u\" name"
    "=\"totalFramesToProcess\"/>\n    </signal>\n    <signal name=\"stopDBu"
    "s\"/>\n    <signal name=\"showStimulus\"/>\n  </interface>\n\0"
    "config\0\0rmin\0rmax\0cannyBlur\0cannyThld1\0"
    "cannyThld2\0StarburstPoints\0online\0"
    "configDbus\0task\0numberOfPoints\0sDist\0"
    "sWidth\0resolutionX\0resolutionY\0"
    "stimulusSize\0clb\0tst\0variant\0time\0"
    "laps\0frequency\0imgName\0directoryName\0"
    "fromRun\0configTrackerDBus\0width\0height\0"
    "frequencyDbus\0value\0keyPressedDbus\0"
    "key\0lapsDbus\0newD1FileDBus\0dataFile\0"
    "newSettingsDBus\0directory\0isTst\0codec\0"
    "normalStateDbus\0processDBus\0freq\0"
    "totalFramesToProcess\0saveImagesDbus\0"
    "sharedMemoryDbus\0showStimulus\0"
    "shutdownDBus\0type\0stopDBus\0methodName"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GUIInterfaceAdaptor[] = {

 // content:
       7,       // revision
       0,       // classname
       2,   14, // classinfo
      16,   18, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      15,       // signalCount

 // classinfo: key, value
       1,    2,
       3,    4,

 // signals: name, argc, parameters, tag, flags
       5,    7,   98,    6, 0x06 /* Public */,
      14,   16,  113,    6, 0x06 /* Public */,
      31,    2,  146,    6, 0x06 /* Public */,
      34,    1,  151,    6, 0x06 /* Public */,
      36,    1,  154,    6, 0x06 /* Public */,
      38,    1,  157,    6, 0x06 /* Public */,
      39,    1,  160,    6, 0x06 /* Public */,
      41,    4,  163,    6, 0x06 /* Public */,
      45,    0,  172,    6, 0x06 /* Public */,
      46,    5,  173,    6, 0x06 /* Public */,
      49,    1,  184,    6, 0x06 /* Public */,
      50,    0,  187,    6, 0x06 /* Public */,
      51,    0,  188,    6, 0x06 /* Public */,
      52,    1,  189,    6, 0x06 /* Public */,
      54,    0,  192,    6, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      55,    0,  193,    6, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Int, QMetaType::Bool,    7,    8,    9,   10,   11,   12,   13,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Double, QMetaType::Double, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::Bool,   15,   16,   17,   18,   19,   20,   21,   22,   23,   24,   25,   26,   27,   28,   29,   30,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   32,   33,
    QMetaType::Void, QMetaType::Int,   35,
    QMetaType::Void, QMetaType::Int,   37,
    QMetaType::Void, QMetaType::Int,   35,
    QMetaType::Void, QMetaType::QString,   40,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Bool, QMetaType::QString,   42,   40,   43,   44,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::UInt,   42,   47,   32,   33,   48,
    QMetaType::Void, QMetaType::Bool,   35,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UInt,   53,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void GUIInterfaceAdaptor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GUIInterfaceAdaptor *_t = static_cast<GUIInterfaceAdaptor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->config((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< bool(*)>(_a[7]))); break;
        case 1: _t->configDbus((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< int(*)>(_a[7])),(*reinterpret_cast< int(*)>(_a[8])),(*reinterpret_cast< int(*)>(_a[9])),(*reinterpret_cast< int(*)>(_a[10])),(*reinterpret_cast< int(*)>(_a[11])),(*reinterpret_cast< int(*)>(_a[12])),(*reinterpret_cast< int(*)>(_a[13])),(*reinterpret_cast< const QString(*)>(_a[14])),(*reinterpret_cast< const QString(*)>(_a[15])),(*reinterpret_cast< bool(*)>(_a[16]))); break;
        case 2: _t->configTrackerDBus((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->frequencyDbus((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->keyPressedDbus((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->lapsDbus((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->newD1FileDBus((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->newSettingsDBus((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        case 8: _t->normalStateDbus(); break;
        case 9: _t->processDBus((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< uint(*)>(_a[5]))); break;
        case 10: _t->saveImagesDbus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->sharedMemoryDbus(); break;
        case 12: _t->showStimulus(); break;
        case 13: _t->shutdownDBus((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 14: _t->stopDBus(); break;
        case 15: _t->methodName(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GUIInterfaceAdaptor::*_t)(int , int , double , double , double , int , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GUIInterfaceAdaptor::config)) {
                *result = 0;
            }
        }
        {
            typedef void (GUIInterfaceAdaptor::*_t)(int , int , double , double , int , int , int , int , int , int , int , int , int , const QString & , const QString & , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GUIInterfaceAdaptor::configDbus)) {
                *result = 1;
            }
        }
        {
            typedef void (GUIInterfaceAdaptor::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GUIInterfaceAdaptor::configTrackerDBus)) {
                *result = 2;
            }
        }
        {
            typedef void (GUIInterfaceAdaptor::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GUIInterfaceAdaptor::frequencyDbus)) {
                *result = 3;
            }
        }
        {
            typedef void (GUIInterfaceAdaptor::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GUIInterfaceAdaptor::keyPressedDbus)) {
                *result = 4;
            }
        }
        {
            typedef void (GUIInterfaceAdaptor::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GUIInterfaceAdaptor::lapsDbus)) {
                *result = 5;
            }
        }
        {
            typedef void (GUIInterfaceAdaptor::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GUIInterfaceAdaptor::newD1FileDBus)) {
                *result = 6;
            }
        }
        {
            typedef void (GUIInterfaceAdaptor::*_t)(const QString & , const QString & , bool , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GUIInterfaceAdaptor::newSettingsDBus)) {
                *result = 7;
            }
        }
        {
            typedef void (GUIInterfaceAdaptor::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GUIInterfaceAdaptor::normalStateDbus)) {
                *result = 8;
            }
        }
        {
            typedef void (GUIInterfaceAdaptor::*_t)(const QString & , int , int , int , uint );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GUIInterfaceAdaptor::processDBus)) {
                *result = 9;
            }
        }
        {
            typedef void (GUIInterfaceAdaptor::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GUIInterfaceAdaptor::saveImagesDbus)) {
                *result = 10;
            }
        }
        {
            typedef void (GUIInterfaceAdaptor::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GUIInterfaceAdaptor::sharedMemoryDbus)) {
                *result = 11;
            }
        }
        {
            typedef void (GUIInterfaceAdaptor::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GUIInterfaceAdaptor::showStimulus)) {
                *result = 12;
            }
        }
        {
            typedef void (GUIInterfaceAdaptor::*_t)(uint );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GUIInterfaceAdaptor::shutdownDBus)) {
                *result = 13;
            }
        }
        {
            typedef void (GUIInterfaceAdaptor::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GUIInterfaceAdaptor::stopDBus)) {
                *result = 14;
            }
        }
    }
}

const QMetaObject GUIInterfaceAdaptor::staticMetaObject = {
    { &QDBusAbstractAdaptor::staticMetaObject, qt_meta_stringdata_GUIInterfaceAdaptor.data,
      qt_meta_data_GUIInterfaceAdaptor,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GUIInterfaceAdaptor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GUIInterfaceAdaptor::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GUIInterfaceAdaptor.stringdata0))
        return static_cast<void*>(const_cast< GUIInterfaceAdaptor*>(this));
    return QDBusAbstractAdaptor::qt_metacast(_clname);
}

int GUIInterfaceAdaptor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDBusAbstractAdaptor::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void GUIInterfaceAdaptor::config(int _t1, int _t2, double _t3, double _t4, double _t5, int _t6, bool _t7)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)), const_cast<void*>(reinterpret_cast<const void*>(&_t7)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GUIInterfaceAdaptor::configDbus(int _t1, int _t2, double _t3, double _t4, int _t5, int _t6, int _t7, int _t8, int _t9, int _t10, int _t11, int _t12, int _t13, const QString & _t14, const QString & _t15, bool _t16)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)), const_cast<void*>(reinterpret_cast<const void*>(&_t7)), const_cast<void*>(reinterpret_cast<const void*>(&_t8)), const_cast<void*>(reinterpret_cast<const void*>(&_t9)), const_cast<void*>(reinterpret_cast<const void*>(&_t10)), const_cast<void*>(reinterpret_cast<const void*>(&_t11)), const_cast<void*>(reinterpret_cast<const void*>(&_t12)), const_cast<void*>(reinterpret_cast<const void*>(&_t13)), const_cast<void*>(reinterpret_cast<const void*>(&_t14)), const_cast<void*>(reinterpret_cast<const void*>(&_t15)), const_cast<void*>(reinterpret_cast<const void*>(&_t16)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GUIInterfaceAdaptor::configTrackerDBus(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void GUIInterfaceAdaptor::frequencyDbus(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void GUIInterfaceAdaptor::keyPressedDbus(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void GUIInterfaceAdaptor::lapsDbus(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void GUIInterfaceAdaptor::newD1FileDBus(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void GUIInterfaceAdaptor::newSettingsDBus(const QString & _t1, const QString & _t2, bool _t3, const QString & _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void GUIInterfaceAdaptor::normalStateDbus()
{
    QMetaObject::activate(this, &staticMetaObject, 8, Q_NULLPTR);
}

// SIGNAL 9
void GUIInterfaceAdaptor::processDBus(const QString & _t1, int _t2, int _t3, int _t4, uint _t5)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void GUIInterfaceAdaptor::saveImagesDbus(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void GUIInterfaceAdaptor::sharedMemoryDbus()
{
    QMetaObject::activate(this, &staticMetaObject, 11, Q_NULLPTR);
}

// SIGNAL 12
void GUIInterfaceAdaptor::showStimulus()
{
    QMetaObject::activate(this, &staticMetaObject, 12, Q_NULLPTR);
}

// SIGNAL 13
void GUIInterfaceAdaptor::shutdownDBus(uint _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void GUIInterfaceAdaptor::stopDBus()
{
    QMetaObject::activate(this, &staticMetaObject, 14, Q_NULLPTR);
}
struct qt_meta_stringdata_WriterInterfaceAdaptor_t {
    QByteArrayData data[7];
    char stringdata0[193];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WriterInterfaceAdaptor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WriterInterfaceAdaptor_t qt_meta_stringdata_WriterInterfaceAdaptor = {
    {
QT_MOC_LITERAL(0, 0, 22), // "WriterInterfaceAdaptor"
QT_MOC_LITERAL(1, 23, 15), // "D-Bus Interface"
QT_MOC_LITERAL(2, 39, 20), // "aura.WriterInterface"
QT_MOC_LITERAL(3, 60, 19), // "D-Bus Introspection"
QT_MOC_LITERAL(4, 80, 98), // "  <interface name=\"aura.Writ..."
QT_MOC_LITERAL(5, 172, 12), // "nextTestDbus"
QT_MOC_LITERAL(6, 185, 0) // ""

    },
    "WriterInterfaceAdaptor\0D-Bus Interface\0"
    "aura.WriterInterface\0D-Bus Introspection\0"
    "  <interface name=\"aura.WriterInterface\">\n    <signal name=\"nextTe"
    "stDbus\"/>\n  </interface>\n\0"
    "nextTestDbus\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WriterInterfaceAdaptor[] = {

 // content:
       7,       // revision
       0,       // classname
       2,   14, // classinfo
       1,   18, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // classinfo: key, value
       1,    2,
       3,    4,

 // signals: name, argc, parameters, tag, flags
       5,    0,   23,    6, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,

       0        // eod
};

void WriterInterfaceAdaptor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WriterInterfaceAdaptor *_t = static_cast<WriterInterfaceAdaptor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->nextTestDbus(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (WriterInterfaceAdaptor::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WriterInterfaceAdaptor::nextTestDbus)) {
                *result = 0;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject WriterInterfaceAdaptor::staticMetaObject = {
    { &QDBusAbstractAdaptor::staticMetaObject, qt_meta_stringdata_WriterInterfaceAdaptor.data,
      qt_meta_data_WriterInterfaceAdaptor,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *WriterInterfaceAdaptor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WriterInterfaceAdaptor::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_WriterInterfaceAdaptor.stringdata0))
        return static_cast<void*>(const_cast< WriterInterfaceAdaptor*>(this));
    return QDBusAbstractAdaptor::qt_metacast(_clname);
}

int WriterInterfaceAdaptor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDBusAbstractAdaptor::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void WriterInterfaceAdaptor::nextTestDbus()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
