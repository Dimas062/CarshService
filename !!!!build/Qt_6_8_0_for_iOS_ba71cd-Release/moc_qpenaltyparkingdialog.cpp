/****************************************************************************
** Meta object code from reading C++ file 'qpenaltyparkingdialog.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../tasks/qpenaltyparkingdialog.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qpenaltyparkingdialog.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSQPenaltyParkingDialogENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSQPenaltyParkingDialogENDCLASS = QtMocHelpers::stringData(
    "QPenaltyParkingDialog",
    "OnPayButtonPressed",
    "",
    "OnApplyPressedSlot",
    "OnGibddButtonPressed",
    "OnReasonButtonPressed",
    "OnParkingButtonPressed",
    "OnRemovePressedSlot",
    "OnReturnToZoneButtonPressed",
    "OnLoadAutoFotoButtonPressed",
    "OnCarshChanged",
    "OnProviderChanged"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSQPenaltyParkingDialogENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   74,    2, 0x0a,    1 /* Public */,
       3,    0,   75,    2, 0x0a,    2 /* Public */,
       4,    0,   76,    2, 0x0a,    3 /* Public */,
       5,    0,   77,    2, 0x0a,    4 /* Public */,
       6,    0,   78,    2, 0x0a,    5 /* Public */,
       7,    0,   79,    2, 0x0a,    6 /* Public */,
       8,    0,   80,    2, 0x0a,    7 /* Public */,
       9,    0,   81,    2, 0x0a,    8 /* Public */,
      10,    0,   82,    2, 0x0a,    9 /* Public */,
      11,    0,   83,    2, 0x0a,   10 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
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

Q_CONSTINIT const QMetaObject QPenaltyParkingDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QCSBaseDialog::staticMetaObject>(),
    qt_meta_stringdata_CLASSQPenaltyParkingDialogENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSQPenaltyParkingDialogENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSQPenaltyParkingDialogENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QPenaltyParkingDialog, std::true_type>,
        // method 'OnPayButtonPressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'OnApplyPressedSlot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'OnGibddButtonPressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'OnReasonButtonPressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'OnParkingButtonPressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'OnRemovePressedSlot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'OnReturnToZoneButtonPressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'OnLoadAutoFotoButtonPressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'OnCarshChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'OnProviderChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void QPenaltyParkingDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QPenaltyParkingDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->OnPayButtonPressed(); break;
        case 1: _t->OnApplyPressedSlot(); break;
        case 2: _t->OnGibddButtonPressed(); break;
        case 3: _t->OnReasonButtonPressed(); break;
        case 4: _t->OnParkingButtonPressed(); break;
        case 5: _t->OnRemovePressedSlot(); break;
        case 6: _t->OnReturnToZoneButtonPressed(); break;
        case 7: _t->OnLoadAutoFotoButtonPressed(); break;
        case 8: _t->OnCarshChanged(); break;
        case 9: _t->OnProviderChanged(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *QPenaltyParkingDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QPenaltyParkingDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSQPenaltyParkingDialogENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QCSBaseDialog::qt_metacast(_clname);
}

int QPenaltyParkingDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCSBaseDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
