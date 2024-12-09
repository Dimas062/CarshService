/****************************************************************************
** Meta object code from reading C++ file 'qparkingtaskdialog.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../tasks/qparkingtaskdialog.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qparkingtaskdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.3. It"
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
struct qt_meta_stringdata_CLASSQParkingTaskDialogENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSQParkingTaskDialogENDCLASS = QtMocHelpers::stringData(
    "QParkingTaskDialog",
    "OnFotoGetet",
    "",
    "OnPayButtonPressed",
    "OnApplyPressedSlot",
    "OnRemovePressedSlot",
    "OnCarshChanged",
    "OnProviderChanged",
    "OnLoadAutoFotoButtonPressed"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSQParkingTaskDialogENDCLASS_t {
    uint offsetsAndSizes[18];
    char stringdata0[19];
    char stringdata1[12];
    char stringdata2[1];
    char stringdata3[19];
    char stringdata4[19];
    char stringdata5[20];
    char stringdata6[15];
    char stringdata7[18];
    char stringdata8[28];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSQParkingTaskDialogENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSQParkingTaskDialogENDCLASS_t qt_meta_stringdata_CLASSQParkingTaskDialogENDCLASS = {
    {
        QT_MOC_LITERAL(0, 18),  // "QParkingTaskDialog"
        QT_MOC_LITERAL(19, 11),  // "OnFotoGetet"
        QT_MOC_LITERAL(31, 0),  // ""
        QT_MOC_LITERAL(32, 18),  // "OnPayButtonPressed"
        QT_MOC_LITERAL(51, 18),  // "OnApplyPressedSlot"
        QT_MOC_LITERAL(70, 19),  // "OnRemovePressedSlot"
        QT_MOC_LITERAL(90, 14),  // "OnCarshChanged"
        QT_MOC_LITERAL(105, 17),  // "OnProviderChanged"
        QT_MOC_LITERAL(123, 27)   // "OnLoadAutoFotoButtonPressed"
    },
    "QParkingTaskDialog",
    "OnFotoGetet",
    "",
    "OnPayButtonPressed",
    "OnApplyPressedSlot",
    "OnRemovePressedSlot",
    "OnCarshChanged",
    "OnProviderChanged",
    "OnLoadAutoFotoButtonPressed"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSQParkingTaskDialogENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   56,    2, 0x0a,    1 /* Public */,
       3,    0,   59,    2, 0x0a,    3 /* Public */,
       4,    0,   60,    2, 0x0a,    4 /* Public */,
       5,    0,   61,    2, 0x0a,    5 /* Public */,
       6,    0,   62,    2, 0x0a,    6 /* Public */,
       7,    0,   63,    2, 0x0a,    7 /* Public */,
       8,    0,   64,    2, 0x0a,    8 /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject QParkingTaskDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QCSBaseDialog::staticMetaObject>(),
    qt_meta_stringdata_CLASSQParkingTaskDialogENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSQParkingTaskDialogENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSQParkingTaskDialogENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QParkingTaskDialog, std::true_type>,
        // method 'OnFotoGetet'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'OnPayButtonPressed'
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

void QParkingTaskDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QParkingTaskDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->OnFotoGetet((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->OnPayButtonPressed(); break;
        case 2: _t->OnApplyPressedSlot(); break;
        case 3: _t->OnRemovePressedSlot(); break;
        case 4: _t->OnCarshChanged(); break;
        case 5: _t->OnProviderChanged(); break;
        case 6: _t->OnLoadAutoFotoButtonPressed(); break;
        default: ;
        }
    }
}

const QMetaObject *QParkingTaskDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QParkingTaskDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSQParkingTaskDialogENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QCSBaseDialog::qt_metacast(_clname);
}

int QParkingTaskDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCSBaseDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
