/****************************************************************************
** Meta object code from reading C++ file 'oscann_interface.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "oscann_interface.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'oscann_interface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AuraCVInterfaceInterface_t {
    QByteArrayData data[6];
    char stringdata0[72];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AuraCVInterfaceInterface_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AuraCVInterfaceInterface_t qt_meta_stringdata_AuraCVInterfaceInterface = {
    {
QT_MOC_LITERAL(0, 0, 24), // "AuraCVInterfaceInterface"
QT_MOC_LITERAL(1, 25, 18), // "changeSettingsDBus"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 5), // "value"
QT_MOC_LITERAL(4, 51, 2), // "id"
QT_MOC_LITERAL(5, 54, 17) // "displayImagesDbus"

    },
    "AuraCVInterfaceInterface\0changeSettingsDBus\0"
    "\0value\0id\0displayImagesDbus"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AuraCVInterfaceInterface[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x06 /* Public */,
       5,    1,   29,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Bool,    3,

       0        // eod
};

void AuraCVInterfaceInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AuraCVInterfaceInterface *_t = static_cast<AuraCVInterfaceInterface *>(_o);
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
            typedef void (AuraCVInterfaceInterface::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AuraCVInterfaceInterface::changeSettingsDBus)) {
                *result = 0;
            }
        }
        {
            typedef void (AuraCVInterfaceInterface::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AuraCVInterfaceInterface::displayImagesDbus)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject AuraCVInterfaceInterface::staticMetaObject = {
    { &QDBusAbstractInterface::staticMetaObject, qt_meta_stringdata_AuraCVInterfaceInterface.data,
      qt_meta_data_AuraCVInterfaceInterface,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *AuraCVInterfaceInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AuraCVInterfaceInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_AuraCVInterfaceInterface.stringdata0))
        return static_cast<void*>(const_cast< AuraCVInterfaceInterface*>(this));
    return QDBusAbstractInterface::qt_metacast(_clname);
}

int AuraCVInterfaceInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDBusAbstractInterface::qt_metacall(_c, _id, _a);
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
void AuraCVInterfaceInterface::changeSettingsDBus(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AuraCVInterfaceInterface::displayImagesDbus(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_AuraCapturerInterfaceInterface_t {
    QByteArrayData data[22];
    char stringdata0[237];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AuraCapturerInterfaceInterface_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AuraCapturerInterfaceInterface_t qt_meta_stringdata_AuraCapturerInterfaceInterface = {
    {
QT_MOC_LITERAL(0, 0, 30), // "AuraCapturerInterfaceInterface"
QT_MOC_LITERAL(1, 31, 19), // "newControlAddedDBus"
QT_MOC_LITERAL(2, 51, 0), // ""
QT_MOC_LITERAL(3, 52, 8), // "ctrlName"
QT_MOC_LITERAL(4, 61, 6), // "ctrlID"
QT_MOC_LITERAL(5, 68, 12), // "ctrlMinValue"
QT_MOC_LITERAL(6, 81, 12), // "ctrlMaxValue"
QT_MOC_LITERAL(7, 94, 9), // "ctrlValue"
QT_MOC_LITERAL(8, 104, 20), // "newValidationImgDBus"
QT_MOC_LITERAL(9, 125, 4), // "logo"
QT_MOC_LITERAL(10, 130, 13), // "saveImageDbus"
QT_MOC_LITERAL(11, 144, 9), // "timestamp"
QT_MOC_LITERAL(12, 154, 5), // "msgTo"
QT_MOC_LITERAL(13, 160, 10), // "signalTest"
QT_MOC_LITERAL(14, 171, 17), // "statusChangedDBus"
QT_MOC_LITERAL(15, 189, 10), // "cameraType"
QT_MOC_LITERAL(16, 200, 5), // "width"
QT_MOC_LITERAL(17, 206, 6), // "height"
QT_MOC_LITERAL(18, 213, 3), // "fps"
QT_MOC_LITERAL(19, 217, 15), // "updateImageDBus"
QT_MOC_LITERAL(20, 233, 1), // "x"
QT_MOC_LITERAL(21, 235, 1) // "y"

    },
    "AuraCapturerInterfaceInterface\0"
    "newControlAddedDBus\0\0ctrlName\0ctrlID\0"
    "ctrlMinValue\0ctrlMaxValue\0ctrlValue\0"
    "newValidationImgDBus\0logo\0saveImageDbus\0"
    "timestamp\0msgTo\0signalTest\0statusChangedDBus\0"
    "cameraType\0width\0height\0fps\0updateImageDBus\0"
    "x\0y"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AuraCapturerInterfaceInterface[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    5,   44,    2, 0x06 /* Public */,
       8,    1,   55,    2, 0x06 /* Public */,
      10,    2,   58,    2, 0x06 /* Public */,
      13,    0,   63,    2, 0x06 /* Public */,
      14,    4,   64,    2, 0x06 /* Public */,
      19,    4,   73,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    3,    4,    5,    6,    7,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, QMetaType::QString, QMetaType::UInt,   11,   12,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   15,   16,   17,   18,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   20,   21,   16,   17,

       0        // eod
};

void AuraCapturerInterfaceInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AuraCapturerInterfaceInterface *_t = static_cast<AuraCapturerInterfaceInterface *>(_o);
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
            typedef void (AuraCapturerInterfaceInterface::*_t)(const QString & , int , int , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AuraCapturerInterfaceInterface::newControlAddedDBus)) {
                *result = 0;
            }
        }
        {
            typedef void (AuraCapturerInterfaceInterface::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AuraCapturerInterfaceInterface::newValidationImgDBus)) {
                *result = 1;
            }
        }
        {
            typedef void (AuraCapturerInterfaceInterface::*_t)(const QString & , uint );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AuraCapturerInterfaceInterface::saveImageDbus)) {
                *result = 2;
            }
        }
        {
            typedef void (AuraCapturerInterfaceInterface::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AuraCapturerInterfaceInterface::signalTest)) {
                *result = 3;
            }
        }
        {
            typedef void (AuraCapturerInterfaceInterface::*_t)(int , int , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AuraCapturerInterfaceInterface::statusChangedDBus)) {
                *result = 4;
            }
        }
        {
            typedef void (AuraCapturerInterfaceInterface::*_t)(int , int , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AuraCapturerInterfaceInterface::updateImageDBus)) {
                *result = 5;
            }
        }
    }
}

const QMetaObject AuraCapturerInterfaceInterface::staticMetaObject = {
    { &QDBusAbstractInterface::staticMetaObject, qt_meta_stringdata_AuraCapturerInterfaceInterface.data,
      qt_meta_data_AuraCapturerInterfaceInterface,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *AuraCapturerInterfaceInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AuraCapturerInterfaceInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_AuraCapturerInterfaceInterface.stringdata0))
        return static_cast<void*>(const_cast< AuraCapturerInterfaceInterface*>(this));
    return QDBusAbstractInterface::qt_metacast(_clname);
}

int AuraCapturerInterfaceInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDBusAbstractInterface::qt_metacall(_c, _id, _a);
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
void AuraCapturerInterfaceInterface::newControlAddedDBus(const QString & _t1, int _t2, int _t3, int _t4, int _t5)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AuraCapturerInterfaceInterface::newValidationImgDBus(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AuraCapturerInterfaceInterface::saveImageDbus(const QString & _t1, uint _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void AuraCapturerInterfaceInterface::signalTest()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void AuraCapturerInterfaceInterface::statusChangedDBus(int _t1, int _t2, int _t3, int _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void AuraCapturerInterfaceInterface::updateImageDBus(int _t1, int _t2, int _t3, int _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
struct qt_meta_stringdata_AuraDetectorInterfaceInterface_t {
    QByteArrayData data[12];
    char stringdata0[106];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AuraDetectorInterfaceInterface_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AuraDetectorInterfaceInterface_t qt_meta_stringdata_AuraDetectorInterfaceInterface = {
    {
QT_MOC_LITERAL(0, 0, 30), // "AuraDetectorInterfaceInterface"
QT_MOC_LITERAL(1, 31, 11), // "loadingDBus"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 7), // "percent"
QT_MOC_LITERAL(4, 52, 12), // "progressDBus"
QT_MOC_LITERAL(5, 65, 12), // "totalPercent"
QT_MOC_LITERAL(6, 78, 11), // "pupilAtDBus"
QT_MOC_LITERAL(7, 90, 1), // "x"
QT_MOC_LITERAL(8, 92, 1), // "y"
QT_MOC_LITERAL(9, 94, 2), // "sx"
QT_MOC_LITERAL(10, 97, 2), // "sy"
QT_MOC_LITERAL(11, 100, 5) // "ready"

    },
    "AuraDetectorInterfaceInterface\0"
    "loadingDBus\0\0percent\0progressDBus\0"
    "totalPercent\0pupilAtDBus\0x\0y\0sx\0sy\0"
    "ready"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AuraDetectorInterfaceInterface[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    2,   37,    2, 0x06 /* Public */,
       6,    4,   42,    2, 0x06 /* Public */,
      11,    0,   51,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    3,    5,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double,    7,    8,    9,   10,
    QMetaType::Void,

       0        // eod
};

void AuraDetectorInterfaceInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AuraDetectorInterfaceInterface *_t = static_cast<AuraDetectorInterfaceInterface *>(_o);
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
            typedef void (AuraDetectorInterfaceInterface::*_t)(double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AuraDetectorInterfaceInterface::loadingDBus)) {
                *result = 0;
            }
        }
        {
            typedef void (AuraDetectorInterfaceInterface::*_t)(double , double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AuraDetectorInterfaceInterface::progressDBus)) {
                *result = 1;
            }
        }
        {
            typedef void (AuraDetectorInterfaceInterface::*_t)(double , double , double , double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AuraDetectorInterfaceInterface::pupilAtDBus)) {
                *result = 2;
            }
        }
        {
            typedef void (AuraDetectorInterfaceInterface::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AuraDetectorInterfaceInterface::ready)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject AuraDetectorInterfaceInterface::staticMetaObject = {
    { &QDBusAbstractInterface::staticMetaObject, qt_meta_stringdata_AuraDetectorInterfaceInterface.data,
      qt_meta_data_AuraDetectorInterfaceInterface,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *AuraDetectorInterfaceInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AuraDetectorInterfaceInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_AuraDetectorInterfaceInterface.stringdata0))
        return static_cast<void*>(const_cast< AuraDetectorInterfaceInterface*>(this));
    return QDBusAbstractInterface::qt_metacast(_clname);
}

int AuraDetectorInterfaceInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDBusAbstractInterface::qt_metacall(_c, _id, _a);
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
void AuraDetectorInterfaceInterface::loadingDBus(double _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AuraDetectorInterfaceInterface::progressDBus(double _t1, double _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AuraDetectorInterfaceInterface::pupilAtDBus(double _t1, double _t2, double _t3, double _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void AuraDetectorInterfaceInterface::ready()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}
struct qt_meta_stringdata_AuraDisplayCTInterfaceInterface_t {
    QByteArrayData data[18];
    char stringdata0[218];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AuraDisplayCTInterfaceInterface_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AuraDisplayCTInterfaceInterface_t qt_meta_stringdata_AuraDisplayCTInterfaceInterface = {
    {
QT_MOC_LITERAL(0, 0, 31), // "AuraDisplayCTInterfaceInterface"
QT_MOC_LITERAL(1, 32, 14), // "closeVideoDbus"
QT_MOC_LITERAL(2, 47, 0), // ""
QT_MOC_LITERAL(3, 48, 15), // "deleteFilesDbus"
QT_MOC_LITERAL(4, 64, 14), // "finishDemoDbus"
QT_MOC_LITERAL(5, 79, 17), // "onCalibrationDBus"
QT_MOC_LITERAL(6, 97, 5), // "value"
QT_MOC_LITERAL(7, 103, 14), // "saveImagesDbus"
QT_MOC_LITERAL(8, 118, 11), // "scatterDBus"
QT_MOC_LITERAL(9, 130, 5), // "index"
QT_MOC_LITERAL(10, 136, 19), // "stimuliOnViewerDBus"
QT_MOC_LITERAL(11, 156, 4), // "flag"
QT_MOC_LITERAL(12, 161, 17), // "stimulus2SaveDbus"
QT_MOC_LITERAL(13, 179, 1), // "x"
QT_MOC_LITERAL(14, 181, 1), // "y"
QT_MOC_LITERAL(15, 183, 16), // "testDurationDBus"
QT_MOC_LITERAL(16, 200, 4), // "time"
QT_MOC_LITERAL(17, 205, 12) // "validateDBus"

    },
    "AuraDisplayCTInterfaceInterface\0"
    "closeVideoDbus\0\0deleteFilesDbus\0"
    "finishDemoDbus\0onCalibrationDBus\0value\0"
    "saveImagesDbus\0scatterDBus\0index\0"
    "stimuliOnViewerDBus\0flag\0stimulus2SaveDbus\0"
    "x\0y\0testDurationDBus\0time\0validateDBus"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AuraDisplayCTInterfaceInterface[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,
       3,    0,   65,    2, 0x06 /* Public */,
       4,    0,   66,    2, 0x06 /* Public */,
       5,    1,   67,    2, 0x06 /* Public */,
       7,    1,   70,    2, 0x06 /* Public */,
       8,    1,   73,    2, 0x06 /* Public */,
      10,    1,   76,    2, 0x06 /* Public */,
      12,    2,   79,    2, 0x06 /* Public */,
      15,    1,   84,    2, 0x06 /* Public */,
      17,    0,   87,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void, QMetaType::UInt,    9,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   13,   14,
    QMetaType::Void, QMetaType::UInt,   16,
    QMetaType::Void,

       0        // eod
};

void AuraDisplayCTInterfaceInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AuraDisplayCTInterfaceInterface *_t = static_cast<AuraDisplayCTInterfaceInterface *>(_o);
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
            typedef void (AuraDisplayCTInterfaceInterface::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AuraDisplayCTInterfaceInterface::closeVideoDbus)) {
                *result = 0;
            }
        }
        {
            typedef void (AuraDisplayCTInterfaceInterface::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AuraDisplayCTInterfaceInterface::deleteFilesDbus)) {
                *result = 1;
            }
        }
        {
            typedef void (AuraDisplayCTInterfaceInterface::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AuraDisplayCTInterfaceInterface::finishDemoDbus)) {
                *result = 2;
            }
        }
        {
            typedef void (AuraDisplayCTInterfaceInterface::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AuraDisplayCTInterfaceInterface::onCalibrationDBus)) {
                *result = 3;
            }
        }
        {
            typedef void (AuraDisplayCTInterfaceInterface::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AuraDisplayCTInterfaceInterface::saveImagesDbus)) {
                *result = 4;
            }
        }
        {
            typedef void (AuraDisplayCTInterfaceInterface::*_t)(uint );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AuraDisplayCTInterfaceInterface::scatterDBus)) {
                *result = 5;
            }
        }
        {
            typedef void (AuraDisplayCTInterfaceInterface::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AuraDisplayCTInterfaceInterface::stimuliOnViewerDBus)) {
                *result = 6;
            }
        }
        {
            typedef void (AuraDisplayCTInterfaceInterface::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AuraDisplayCTInterfaceInterface::stimulus2SaveDbus)) {
                *result = 7;
            }
        }
        {
            typedef void (AuraDisplayCTInterfaceInterface::*_t)(uint );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AuraDisplayCTInterfaceInterface::testDurationDBus)) {
                *result = 8;
            }
        }
        {
            typedef void (AuraDisplayCTInterfaceInterface::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AuraDisplayCTInterfaceInterface::validateDBus)) {
                *result = 9;
            }
        }
    }
}

const QMetaObject AuraDisplayCTInterfaceInterface::staticMetaObject = {
    { &QDBusAbstractInterface::staticMetaObject, qt_meta_stringdata_AuraDisplayCTInterfaceInterface.data,
      qt_meta_data_AuraDisplayCTInterfaceInterface,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *AuraDisplayCTInterfaceInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AuraDisplayCTInterfaceInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_AuraDisplayCTInterfaceInterface.stringdata0))
        return static_cast<void*>(const_cast< AuraDisplayCTInterfaceInterface*>(this));
    return QDBusAbstractInterface::qt_metacast(_clname);
}

int AuraDisplayCTInterfaceInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDBusAbstractInterface::qt_metacall(_c, _id, _a);
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
void AuraDisplayCTInterfaceInterface::closeVideoDbus()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void AuraDisplayCTInterfaceInterface::deleteFilesDbus()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void AuraDisplayCTInterfaceInterface::finishDemoDbus()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void AuraDisplayCTInterfaceInterface::onCalibrationDBus(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void AuraDisplayCTInterfaceInterface::saveImagesDbus(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void AuraDisplayCTInterfaceInterface::scatterDBus(uint _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void AuraDisplayCTInterfaceInterface::stimuliOnViewerDBus(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void AuraDisplayCTInterfaceInterface::stimulus2SaveDbus(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void AuraDisplayCTInterfaceInterface::testDurationDBus(uint _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void AuraDisplayCTInterfaceInterface::validateDBus()
{
    QMetaObject::activate(this, &staticMetaObject, 9, Q_NULLPTR);
}
struct qt_meta_stringdata_AuraGUIInterfaceInterface_t {
    QByteArrayData data[53];
    char stringdata0[543];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AuraGUIInterfaceInterface_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AuraGUIInterfaceInterface_t qt_meta_stringdata_AuraGUIInterfaceInterface = {
    {
QT_MOC_LITERAL(0, 0, 25), // "AuraGUIInterfaceInterface"
QT_MOC_LITERAL(1, 26, 6), // "config"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 4), // "rmin"
QT_MOC_LITERAL(4, 39, 4), // "rmax"
QT_MOC_LITERAL(5, 44, 9), // "cannyBlur"
QT_MOC_LITERAL(6, 54, 10), // "cannyThld1"
QT_MOC_LITERAL(7, 65, 10), // "cannyThld2"
QT_MOC_LITERAL(8, 76, 15), // "StarburstPoints"
QT_MOC_LITERAL(9, 92, 6), // "online"
QT_MOC_LITERAL(10, 99, 10), // "configDbus"
QT_MOC_LITERAL(11, 110, 4), // "task"
QT_MOC_LITERAL(12, 115, 14), // "numberOfPoints"
QT_MOC_LITERAL(13, 130, 5), // "sDist"
QT_MOC_LITERAL(14, 136, 6), // "sWidth"
QT_MOC_LITERAL(15, 143, 11), // "resolutionX"
QT_MOC_LITERAL(16, 155, 11), // "resolutionY"
QT_MOC_LITERAL(17, 167, 12), // "stimulusSize"
QT_MOC_LITERAL(18, 180, 3), // "clb"
QT_MOC_LITERAL(19, 184, 3), // "tst"
QT_MOC_LITERAL(20, 188, 7), // "variant"
QT_MOC_LITERAL(21, 196, 4), // "time"
QT_MOC_LITERAL(22, 201, 4), // "laps"
QT_MOC_LITERAL(23, 206, 9), // "frequency"
QT_MOC_LITERAL(24, 216, 7), // "imgName"
QT_MOC_LITERAL(25, 224, 13), // "directoryName"
QT_MOC_LITERAL(26, 238, 7), // "fromRun"
QT_MOC_LITERAL(27, 246, 17), // "configTrackerDBus"
QT_MOC_LITERAL(28, 264, 5), // "width"
QT_MOC_LITERAL(29, 270, 6), // "height"
QT_MOC_LITERAL(30, 277, 13), // "frequencyDbus"
QT_MOC_LITERAL(31, 291, 5), // "value"
QT_MOC_LITERAL(32, 297, 14), // "keyPressedDbus"
QT_MOC_LITERAL(33, 312, 3), // "key"
QT_MOC_LITERAL(34, 316, 8), // "lapsDbus"
QT_MOC_LITERAL(35, 325, 13), // "newD1FileDBus"
QT_MOC_LITERAL(36, 339, 8), // "dataFile"
QT_MOC_LITERAL(37, 348, 15), // "newSettingsDBus"
QT_MOC_LITERAL(38, 364, 9), // "directory"
QT_MOC_LITERAL(39, 374, 5), // "isTst"
QT_MOC_LITERAL(40, 380, 5), // "codec"
QT_MOC_LITERAL(41, 386, 15), // "normalStateDbus"
QT_MOC_LITERAL(42, 402, 11), // "processDBus"
QT_MOC_LITERAL(43, 414, 4), // "freq"
QT_MOC_LITERAL(44, 419, 20), // "totalFramesToProcess"
QT_MOC_LITERAL(45, 440, 14), // "saveImagesDbus"
QT_MOC_LITERAL(46, 455, 16), // "sharedMemoryDbus"
QT_MOC_LITERAL(47, 472, 12), // "showStimulus"
QT_MOC_LITERAL(48, 485, 12), // "shutdownDBus"
QT_MOC_LITERAL(49, 498, 4), // "type"
QT_MOC_LITERAL(50, 503, 8), // "stopDBus"
QT_MOC_LITERAL(51, 512, 10), // "methodName"
QT_MOC_LITERAL(52, 523, 19) // "QDBusPendingReply<>"

    },
    "AuraGUIInterfaceInterface\0config\0\0"
    "rmin\0rmax\0cannyBlur\0cannyThld1\0"
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
    "shutdownDBus\0type\0stopDBus\0methodName\0"
    "QDBusPendingReply<>"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AuraGUIInterfaceInterface[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      15,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    7,   94,    2, 0x06 /* Public */,
      10,   16,  109,    2, 0x06 /* Public */,
      27,    2,  142,    2, 0x06 /* Public */,
      30,    1,  147,    2, 0x06 /* Public */,
      32,    1,  150,    2, 0x06 /* Public */,
      34,    1,  153,    2, 0x06 /* Public */,
      35,    1,  156,    2, 0x06 /* Public */,
      37,    4,  159,    2, 0x06 /* Public */,
      41,    0,  168,    2, 0x06 /* Public */,
      42,    5,  169,    2, 0x06 /* Public */,
      45,    1,  180,    2, 0x06 /* Public */,
      46,    0,  183,    2, 0x06 /* Public */,
      47,    0,  184,    2, 0x06 /* Public */,
      48,    1,  185,    2, 0x06 /* Public */,
      50,    0,  188,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      51,    0,  189,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Int, QMetaType::Bool,    3,    4,    5,    6,    7,    8,    9,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Double, QMetaType::Double, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::Bool,   11,   12,   13,   14,   15,   16,   17,   18,   19,   20,   21,   22,   23,   24,   25,   26,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   28,   29,
    QMetaType::Void, QMetaType::Int,   31,
    QMetaType::Void, QMetaType::Int,   33,
    QMetaType::Void, QMetaType::Int,   31,
    QMetaType::Void, QMetaType::QString,   36,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Bool, QMetaType::QString,   38,   36,   39,   40,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::UInt,   38,   43,   28,   29,   44,
    QMetaType::Void, QMetaType::Bool,   31,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UInt,   49,
    QMetaType::Void,

 // slots: parameters
    0x80000000 | 52,

       0        // eod
};

void AuraGUIInterfaceInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AuraGUIInterfaceInterface *_t = static_cast<AuraGUIInterfaceInterface *>(_o);
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
        case 15: { QDBusPendingReply<> _r = _t->methodName();
            if (_a[0]) *reinterpret_cast< QDBusPendingReply<>*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (AuraGUIInterfaceInterface::*_t)(int , int , double , double , double , int , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AuraGUIInterfaceInterface::config)) {
                *result = 0;
            }
        }
        {
            typedef void (AuraGUIInterfaceInterface::*_t)(int , int , double , double , int , int , int , int , int , int , int , int , int , const QString & , const QString & , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AuraGUIInterfaceInterface::configDbus)) {
                *result = 1;
            }
        }
        {
            typedef void (AuraGUIInterfaceInterface::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AuraGUIInterfaceInterface::configTrackerDBus)) {
                *result = 2;
            }
        }
        {
            typedef void (AuraGUIInterfaceInterface::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AuraGUIInterfaceInterface::frequencyDbus)) {
                *result = 3;
            }
        }
        {
            typedef void (AuraGUIInterfaceInterface::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AuraGUIInterfaceInterface::keyPressedDbus)) {
                *result = 4;
            }
        }
        {
            typedef void (AuraGUIInterfaceInterface::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AuraGUIInterfaceInterface::lapsDbus)) {
                *result = 5;
            }
        }
        {
            typedef void (AuraGUIInterfaceInterface::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AuraGUIInterfaceInterface::newD1FileDBus)) {
                *result = 6;
            }
        }
        {
            typedef void (AuraGUIInterfaceInterface::*_t)(const QString & , const QString & , bool , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AuraGUIInterfaceInterface::newSettingsDBus)) {
                *result = 7;
            }
        }
        {
            typedef void (AuraGUIInterfaceInterface::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AuraGUIInterfaceInterface::normalStateDbus)) {
                *result = 8;
            }
        }
        {
            typedef void (AuraGUIInterfaceInterface::*_t)(const QString & , int , int , int , uint );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AuraGUIInterfaceInterface::processDBus)) {
                *result = 9;
            }
        }
        {
            typedef void (AuraGUIInterfaceInterface::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AuraGUIInterfaceInterface::saveImagesDbus)) {
                *result = 10;
            }
        }
        {
            typedef void (AuraGUIInterfaceInterface::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AuraGUIInterfaceInterface::sharedMemoryDbus)) {
                *result = 11;
            }
        }
        {
            typedef void (AuraGUIInterfaceInterface::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AuraGUIInterfaceInterface::showStimulus)) {
                *result = 12;
            }
        }
        {
            typedef void (AuraGUIInterfaceInterface::*_t)(uint );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AuraGUIInterfaceInterface::shutdownDBus)) {
                *result = 13;
            }
        }
        {
            typedef void (AuraGUIInterfaceInterface::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AuraGUIInterfaceInterface::stopDBus)) {
                *result = 14;
            }
        }
    }
}

const QMetaObject AuraGUIInterfaceInterface::staticMetaObject = {
    { &QDBusAbstractInterface::staticMetaObject, qt_meta_stringdata_AuraGUIInterfaceInterface.data,
      qt_meta_data_AuraGUIInterfaceInterface,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *AuraGUIInterfaceInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AuraGUIInterfaceInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_AuraGUIInterfaceInterface.stringdata0))
        return static_cast<void*>(const_cast< AuraGUIInterfaceInterface*>(this));
    return QDBusAbstractInterface::qt_metacast(_clname);
}

int AuraGUIInterfaceInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDBusAbstractInterface::qt_metacall(_c, _id, _a);
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
void AuraGUIInterfaceInterface::config(int _t1, int _t2, double _t3, double _t4, double _t5, int _t6, bool _t7)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)), const_cast<void*>(reinterpret_cast<const void*>(&_t7)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AuraGUIInterfaceInterface::configDbus(int _t1, int _t2, double _t3, double _t4, int _t5, int _t6, int _t7, int _t8, int _t9, int _t10, int _t11, int _t12, int _t13, const QString & _t14, const QString & _t15, bool _t16)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)), const_cast<void*>(reinterpret_cast<const void*>(&_t7)), const_cast<void*>(reinterpret_cast<const void*>(&_t8)), const_cast<void*>(reinterpret_cast<const void*>(&_t9)), const_cast<void*>(reinterpret_cast<const void*>(&_t10)), const_cast<void*>(reinterpret_cast<const void*>(&_t11)), const_cast<void*>(reinterpret_cast<const void*>(&_t12)), const_cast<void*>(reinterpret_cast<const void*>(&_t13)), const_cast<void*>(reinterpret_cast<const void*>(&_t14)), const_cast<void*>(reinterpret_cast<const void*>(&_t15)), const_cast<void*>(reinterpret_cast<const void*>(&_t16)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AuraGUIInterfaceInterface::configTrackerDBus(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void AuraGUIInterfaceInterface::frequencyDbus(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void AuraGUIInterfaceInterface::keyPressedDbus(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void AuraGUIInterfaceInterface::lapsDbus(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void AuraGUIInterfaceInterface::newD1FileDBus(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void AuraGUIInterfaceInterface::newSettingsDBus(const QString & _t1, const QString & _t2, bool _t3, const QString & _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void AuraGUIInterfaceInterface::normalStateDbus()
{
    QMetaObject::activate(this, &staticMetaObject, 8, Q_NULLPTR);
}

// SIGNAL 9
void AuraGUIInterfaceInterface::processDBus(const QString & _t1, int _t2, int _t3, int _t4, uint _t5)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void AuraGUIInterfaceInterface::saveImagesDbus(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void AuraGUIInterfaceInterface::sharedMemoryDbus()
{
    QMetaObject::activate(this, &staticMetaObject, 11, Q_NULLPTR);
}

// SIGNAL 12
void AuraGUIInterfaceInterface::showStimulus()
{
    QMetaObject::activate(this, &staticMetaObject, 12, Q_NULLPTR);
}

// SIGNAL 13
void AuraGUIInterfaceInterface::shutdownDBus(uint _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void AuraGUIInterfaceInterface::stopDBus()
{
    QMetaObject::activate(this, &staticMetaObject, 14, Q_NULLPTR);
}
struct qt_meta_stringdata_AuraWriterInterfaceInterface_t {
    QByteArrayData data[3];
    char stringdata0[43];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AuraWriterInterfaceInterface_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AuraWriterInterfaceInterface_t qt_meta_stringdata_AuraWriterInterfaceInterface = {
    {
QT_MOC_LITERAL(0, 0, 28), // "AuraWriterInterfaceInterface"
QT_MOC_LITERAL(1, 29, 12), // "nextTestDbus"
QT_MOC_LITERAL(2, 42, 0) // ""

    },
    "AuraWriterInterfaceInterface\0nextTestDbus\0"
    ""
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AuraWriterInterfaceInterface[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,

       0        // eod
};

void AuraWriterInterfaceInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AuraWriterInterfaceInterface *_t = static_cast<AuraWriterInterfaceInterface *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->nextTestDbus(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (AuraWriterInterfaceInterface::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AuraWriterInterfaceInterface::nextTestDbus)) {
                *result = 0;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject AuraWriterInterfaceInterface::staticMetaObject = {
    { &QDBusAbstractInterface::staticMetaObject, qt_meta_stringdata_AuraWriterInterfaceInterface.data,
      qt_meta_data_AuraWriterInterfaceInterface,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *AuraWriterInterfaceInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AuraWriterInterfaceInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_AuraWriterInterfaceInterface.stringdata0))
        return static_cast<void*>(const_cast< AuraWriterInterfaceInterface*>(this));
    return QDBusAbstractInterface::qt_metacast(_clname);
}

int AuraWriterInterfaceInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDBusAbstractInterface::qt_metacall(_c, _id, _a);
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
void AuraWriterInterfaceInterface::nextTestDbus()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
