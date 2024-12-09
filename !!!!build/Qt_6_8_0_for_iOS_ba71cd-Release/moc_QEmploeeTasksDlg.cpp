/****************************************************************************
** Meta object code from reading C++ file 'QEmploeeTasksDlg.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../emploee_widgets/QEmploeeTasksDlg.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QEmploeeTasksDlg.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSQEmploeeTasksDlgENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSQEmploeeTasksDlgENDCLASS = QtMocHelpers::stringData(
    "QEmploeeTasksDlg",
    "OnTapHoldGesture",
    "",
    "OnTapGesture",
    "OnReadyButtonTogled",
    "OnNotReadyButtonTogled",
    "OnToCalendatButtonTogled",
    "FioClicked"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSQEmploeeTasksDlgENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x0a,    1 /* Public */,
       3,    0,   51,    2, 0x0a,    2 /* Public */,
       4,    1,   52,    2, 0x0a,    3 /* Public */,
       5,    1,   55,    2, 0x0a,    5 /* Public */,
       6,    1,   58,    2, 0x0a,    7 /* Public */,
       7,    0,   61,    2, 0x0a,    9 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject QEmploeeTasksDlg::staticMetaObject = { {
    QMetaObject::SuperData::link<QCSBaseDialog::staticMetaObject>(),
    qt_meta_stringdata_CLASSQEmploeeTasksDlgENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSQEmploeeTasksDlgENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSQEmploeeTasksDlgENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QEmploeeTasksDlg, std::true_type>,
        // method 'OnTapHoldGesture'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'OnTapGesture'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'OnReadyButtonTogled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'OnNotReadyButtonTogled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'OnToCalendatButtonTogled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'FioClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void QEmploeeTasksDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QEmploeeTasksDlg *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->OnTapHoldGesture(); break;
        case 1: _t->OnTapGesture(); break;
        case 2: _t->OnReadyButtonTogled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 3: _t->OnNotReadyButtonTogled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 4: _t->OnToCalendatButtonTogled((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 5: _t->FioClicked(); break;
        default: ;
        }
    }
}

const QMetaObject *QEmploeeTasksDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QEmploeeTasksDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSQEmploeeTasksDlgENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QCSBaseDialog::qt_metacast(_clname);
}

int QEmploeeTasksDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCSBaseDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
