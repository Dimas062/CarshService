/****************************************************************************
** Meta object code from reading C++ file 'qplatetaskdialog.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../tasks/qplatetaskdialog.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qplatetaskdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSQPlateTaskDialogENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSQPlateTaskDialogENDCLASS = QtMocHelpers::stringData(
    "QPlateTaskDialog",
    "OnOnePlatePressedSlot",
    "",
    "OnTwoPlatePressedSlot",
    "OnZeroPlatePressedSlot",
    "OnApplyPressedSlot",
    "OnRemovePressedSlot",
    "OnCarshChanged",
    "OnProviderChanged",
    "OnLoadAutoFotoButtonPressed"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSQPlateTaskDialogENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   62,    2, 0x0a,    1 /* Public */,
       3,    0,   63,    2, 0x0a,    2 /* Public */,
       4,    0,   64,    2, 0x0a,    3 /* Public */,
       5,    0,   65,    2, 0x0a,    4 /* Public */,
       6,    0,   66,    2, 0x0a,    5 /* Public */,
       7,    0,   67,    2, 0x0a,    6 /* Public */,
       8,    0,   68,    2, 0x0a,    7 /* Public */,
       9,    0,   69,    2, 0x0a,    8 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject QPlateTaskDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QCSBaseDialog::staticMetaObject>(),
    qt_meta_stringdata_CLASSQPlateTaskDialogENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSQPlateTaskDialogENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSQPlateTaskDialogENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QPlateTaskDialog, std::true_type>,
        // method 'OnOnePlatePressedSlot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'OnTwoPlatePressedSlot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'OnZeroPlatePressedSlot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'OnApplyPressedSlot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'OnRemovePressedSlot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'OnCarshChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'OnProviderChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'OnLoadAutoFotoButtonPressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void QPlateTaskDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QPlateTaskDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->OnOnePlatePressedSlot(); break;
        case 1: _t->OnTwoPlatePressedSlot(); break;
        case 2: _t->OnZeroPlatePressedSlot(); break;
        case 3: _t->OnApplyPressedSlot(); break;
        case 4: _t->OnRemovePressedSlot(); break;
        case 5: _t->OnCarshChanged(); break;
        case 6: _t->OnProviderChanged(); break;
        case 7: _t->OnLoadAutoFotoButtonPressed(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *QPlateTaskDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QPlateTaskDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSQPlateTaskDialogENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QCSBaseDialog::qt_metacast(_clname);
}

int QPlateTaskDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCSBaseDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
