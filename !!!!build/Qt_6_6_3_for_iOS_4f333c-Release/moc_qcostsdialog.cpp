/****************************************************************************
** Meta object code from reading C++ file 'qcostsdialog.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../tasks/qcostsdialog.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qcostsdialog.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSQCostsDialogENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSQCostsDialogENDCLASS = QtMocHelpers::stringData(
    "QCostsDialog",
    "OnPayButtonPressed",
    "",
    "OnArticleButtonPressed",
    "OnItemButtonPressed",
    "OnApplyPressedSlot",
    "OnRemovePressedSlot"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSQCostsDialogENDCLASS_t {
    uint offsetsAndSizes[14];
    char stringdata0[13];
    char stringdata1[19];
    char stringdata2[1];
    char stringdata3[23];
    char stringdata4[20];
    char stringdata5[19];
    char stringdata6[20];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSQCostsDialogENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSQCostsDialogENDCLASS_t qt_meta_stringdata_CLASSQCostsDialogENDCLASS = {
    {
        QT_MOC_LITERAL(0, 12),  // "QCostsDialog"
        QT_MOC_LITERAL(13, 18),  // "OnPayButtonPressed"
        QT_MOC_LITERAL(32, 0),  // ""
        QT_MOC_LITERAL(33, 22),  // "OnArticleButtonPressed"
        QT_MOC_LITERAL(56, 19),  // "OnItemButtonPressed"
        QT_MOC_LITERAL(76, 18),  // "OnApplyPressedSlot"
        QT_MOC_LITERAL(95, 19)   // "OnRemovePressedSlot"
    },
    "QCostsDialog",
    "OnPayButtonPressed",
    "",
    "OnArticleButtonPressed",
    "OnItemButtonPressed",
    "OnApplyPressedSlot",
    "OnRemovePressedSlot"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSQCostsDialogENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   44,    2, 0x0a,    1 /* Public */,
       3,    0,   45,    2, 0x0a,    2 /* Public */,
       4,    0,   46,    2, 0x0a,    3 /* Public */,
       5,    0,   47,    2, 0x0a,    4 /* Public */,
       6,    0,   48,    2, 0x0a,    5 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject QCostsDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QCSBaseDialog::staticMetaObject>(),
    qt_meta_stringdata_CLASSQCostsDialogENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSQCostsDialogENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSQCostsDialogENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCostsDialog, std::true_type>,
        // method 'OnPayButtonPressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'OnArticleButtonPressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'OnItemButtonPressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'OnApplyPressedSlot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'OnRemovePressedSlot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void QCostsDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QCostsDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->OnPayButtonPressed(); break;
        case 1: _t->OnArticleButtonPressed(); break;
        case 2: _t->OnItemButtonPressed(); break;
        case 3: _t->OnApplyPressedSlot(); break;
        case 4: _t->OnRemovePressedSlot(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *QCostsDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCostsDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSQCostsDialogENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QCSBaseDialog::qt_metacast(_clname);
}

int QCostsDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCSBaseDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
