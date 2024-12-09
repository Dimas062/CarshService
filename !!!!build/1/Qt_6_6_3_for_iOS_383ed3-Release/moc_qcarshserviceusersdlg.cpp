/****************************************************************************
** Meta object code from reading C++ file 'qcarshserviceusersdlg.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../carsh_service_widgets/qcarshserviceusersdlg.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qcarshserviceusersdlg.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSQCarshServiceUsersDlgENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSQCarshServiceUsersDlgENDCLASS = QtMocHelpers::stringData(
    "QCarshServiceUsersDlg",
    "OnTapHoldGesture",
    "",
    "OnTapGesture"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSQCarshServiceUsersDlgENDCLASS_t {
    uint offsetsAndSizes[8];
    char stringdata0[22];
    char stringdata1[17];
    char stringdata2[1];
    char stringdata3[13];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSQCarshServiceUsersDlgENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSQCarshServiceUsersDlgENDCLASS_t qt_meta_stringdata_CLASSQCarshServiceUsersDlgENDCLASS = {
    {
        QT_MOC_LITERAL(0, 21),  // "QCarshServiceUsersDlg"
        QT_MOC_LITERAL(22, 16),  // "OnTapHoldGesture"
        QT_MOC_LITERAL(39, 0),  // ""
        QT_MOC_LITERAL(40, 12)   // "OnTapGesture"
    },
    "QCarshServiceUsersDlg",
    "OnTapHoldGesture",
    "",
    "OnTapGesture"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSQCarshServiceUsersDlgENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   26,    2, 0x0a,    1 /* Public */,
       3,    0,   27,    2, 0x0a,    2 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject QCarshServiceUsersDlg::staticMetaObject = { {
    QMetaObject::SuperData::link<QCSBaseDialog::staticMetaObject>(),
    qt_meta_stringdata_CLASSQCarshServiceUsersDlgENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSQCarshServiceUsersDlgENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSQCarshServiceUsersDlgENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCarshServiceUsersDlg, std::true_type>,
        // method 'OnTapHoldGesture'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'OnTapGesture'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void QCarshServiceUsersDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QCarshServiceUsersDlg *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->OnTapHoldGesture(); break;
        case 1: _t->OnTapGesture(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *QCarshServiceUsersDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCarshServiceUsersDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSQCarshServiceUsersDlgENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QCSBaseDialog::qt_metacast(_clname);
}

int QCarshServiceUsersDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCSBaseDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
