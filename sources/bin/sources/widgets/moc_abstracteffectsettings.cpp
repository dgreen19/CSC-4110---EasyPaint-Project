/****************************************************************************
** Meta object code from reading C++ file 'abstracteffectsettings.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../widgets/abstracteffectsettings.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'abstracteffectsettings.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AbstractEffectSettings_t {
    QByteArrayData data[3];
    char stringdata0[38];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AbstractEffectSettings_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AbstractEffectSettings_t qt_meta_stringdata_AbstractEffectSettings = {
    {
QT_MOC_LITERAL(0, 0, 22), // "AbstractEffectSettings"
QT_MOC_LITERAL(1, 23, 13), // "matrixChanged"
QT_MOC_LITERAL(2, 37, 0) // ""

    },
    "AbstractEffectSettings\0matrixChanged\0"
    ""
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AbstractEffectSettings[] = {

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

void AbstractEffectSettings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AbstractEffectSettings *_t = static_cast<AbstractEffectSettings *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->matrixChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (AbstractEffectSettings::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AbstractEffectSettings::matrixChanged)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject AbstractEffectSettings::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_AbstractEffectSettings.data,
      qt_meta_data_AbstractEffectSettings,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *AbstractEffectSettings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AbstractEffectSettings::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AbstractEffectSettings.stringdata0))
        return static_cast<void*>(const_cast< AbstractEffectSettings*>(this));
    return QWidget::qt_metacast(_clname);
}

int AbstractEffectSettings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void AbstractEffectSettings::matrixChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
