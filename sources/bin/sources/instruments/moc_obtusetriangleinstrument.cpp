/****************************************************************************
** Meta object code from reading C++ file 'obtusetriangleinstrument.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../instruments/obtusetriangleinstrument.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'obtusetriangleinstrument.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ObtuseTriangleInstrument_t {
    QByteArrayData data[6];
    char stringdata0[80];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ObtuseTriangleInstrument_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ObtuseTriangleInstrument_t qt_meta_stringdata_ObtuseTriangleInstrument = {
    {
QT_MOC_LITERAL(0, 0, 24), // "ObtuseTriangleInstrument"
QT_MOC_LITERAL(1, 25, 19), // "sendCloseTextDialog"
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 10), // "updateText"
QT_MOC_LITERAL(4, 57, 10), // "ImageArea*"
QT_MOC_LITERAL(5, 68, 11) // "updateAngle"

    },
    "ObtuseTriangleInstrument\0sendCloseTextDialog\0"
    "\0updateText\0ImageArea*\0updateAngle"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ObtuseTriangleInstrument[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    2,   30,    2, 0x08 /* Private */,
       5,    2,   35,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4, QMetaType::QString,    2,    2,
    QMetaType::Void, 0x80000000 | 4, QMetaType::Int,    2,    2,

       0        // eod
};

void ObtuseTriangleInstrument::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ObtuseTriangleInstrument *_t = static_cast<ObtuseTriangleInstrument *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendCloseTextDialog(); break;
        case 1: _t->updateText((*reinterpret_cast< ImageArea*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->updateAngle((*reinterpret_cast< ImageArea*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ObtuseTriangleInstrument::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ObtuseTriangleInstrument::sendCloseTextDialog)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject ObtuseTriangleInstrument::staticMetaObject = {
    { &AbstractInstrument::staticMetaObject, qt_meta_stringdata_ObtuseTriangleInstrument.data,
      qt_meta_data_ObtuseTriangleInstrument,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ObtuseTriangleInstrument::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ObtuseTriangleInstrument::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ObtuseTriangleInstrument.stringdata0))
        return static_cast<void*>(const_cast< ObtuseTriangleInstrument*>(this));
    return AbstractInstrument::qt_metacast(_clname);
}

int ObtuseTriangleInstrument::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractInstrument::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void ObtuseTriangleInstrument::sendCloseTextDialog()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
