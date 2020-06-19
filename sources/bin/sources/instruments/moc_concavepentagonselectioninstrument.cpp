/****************************************************************************
** Meta object code from reading C++ file 'concavepentagonselectioninstrument.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../instruments/concavepentagonselectioninstrument.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'concavepentagonselectioninstrument.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ConcavePentagonSelectionInstrument_t {
    QByteArrayData data[5];
    char stringdata0[98];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConcavePentagonSelectionInstrument_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConcavePentagonSelectionInstrument_t qt_meta_stringdata_ConcavePentagonSelectionInstrument = {
    {
QT_MOC_LITERAL(0, 0, 34), // "ConcavePentagonSelectionInstr..."
QT_MOC_LITERAL(1, 35, 24), // "sendEnableCopyCutActions"
QT_MOC_LITERAL(2, 60, 0), // ""
QT_MOC_LITERAL(3, 61, 6), // "enable"
QT_MOC_LITERAL(4, 68, 29) // "sendEnableSelectionInstrument"

    },
    "ConcavePentagonSelectionInstrument\0"
    "sendEnableCopyCutActions\0\0enable\0"
    "sendEnableSelectionInstrument"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConcavePentagonSelectionInstrument[] = {

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

void ConcavePentagonSelectionInstrument::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ConcavePentagonSelectionInstrument *_t = static_cast<ConcavePentagonSelectionInstrument *>(_o);
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
            typedef void (ConcavePentagonSelectionInstrument::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ConcavePentagonSelectionInstrument::sendEnableCopyCutActions)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ConcavePentagonSelectionInstrument::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ConcavePentagonSelectionInstrument::sendEnableSelectionInstrument)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject ConcavePentagonSelectionInstrument::staticMetaObject = {
    { &AbstractSelection::staticMetaObject, qt_meta_stringdata_ConcavePentagonSelectionInstrument.data,
      qt_meta_data_ConcavePentagonSelectionInstrument,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ConcavePentagonSelectionInstrument::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConcavePentagonSelectionInstrument::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ConcavePentagonSelectionInstrument.stringdata0))
        return static_cast<void*>(const_cast< ConcavePentagonSelectionInstrument*>(this));
    return AbstractSelection::qt_metacast(_clname);
}

int ConcavePentagonSelectionInstrument::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void ConcavePentagonSelectionInstrument::sendEnableCopyCutActions(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ConcavePentagonSelectionInstrument::sendEnableSelectionInstrument(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
