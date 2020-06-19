/****************************************************************************
** Meta object code from reading C++ file 'convexpentagonselectioninstrument.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../instruments/convexpentagonselectioninstrument.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'convexpentagonselectioninstrument.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ConvexPentagonSelectionInstrument_t {
    QByteArrayData data[5];
    char stringdata0[97];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConvexPentagonSelectionInstrument_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConvexPentagonSelectionInstrument_t qt_meta_stringdata_ConvexPentagonSelectionInstrument = {
    {
QT_MOC_LITERAL(0, 0, 33), // "ConvexPentagonSelectionInstru..."
QT_MOC_LITERAL(1, 34, 24), // "sendEnableCopyCutActions"
QT_MOC_LITERAL(2, 59, 0), // ""
QT_MOC_LITERAL(3, 60, 6), // "enable"
QT_MOC_LITERAL(4, 67, 29) // "sendEnableSelectionInstrument"

    },
    "ConvexPentagonSelectionInstrument\0"
    "sendEnableCopyCutActions\0\0enable\0"
    "sendEnableSelectionInstrument"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConvexPentagonSelectionInstrument[] = {

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
       1,    1,   24,    2, 0x06 /* Public */,
       4,    1,   27,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,

       0        // eod
};

void ConvexPentagonSelectionInstrument::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ConvexPentagonSelectionInstrument *_t = static_cast<ConvexPentagonSelectionInstrument *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendEnableCopyCutActions((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->sendEnableSelectionInstrument((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ConvexPentagonSelectionInstrument::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ConvexPentagonSelectionInstrument::sendEnableCopyCutActions)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ConvexPentagonSelectionInstrument::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ConvexPentagonSelectionInstrument::sendEnableSelectionInstrument)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject ConvexPentagonSelectionInstrument::staticMetaObject = {
    { &AbstractSelection::staticMetaObject, qt_meta_stringdata_ConvexPentagonSelectionInstrument.data,
      qt_meta_data_ConvexPentagonSelectionInstrument,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ConvexPentagonSelectionInstrument::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConvexPentagonSelectionInstrument::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ConvexPentagonSelectionInstrument.stringdata0))
        return static_cast<void*>(const_cast< ConvexPentagonSelectionInstrument*>(this));
    return AbstractSelection::qt_metacast(_clname);
}

int ConvexPentagonSelectionInstrument::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractSelection::qt_metacall(_c, _id, _a);
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
void ConvexPentagonSelectionInstrument::sendEnableCopyCutActions(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ConvexPentagonSelectionInstrument::sendEnableSelectionInstrument(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
