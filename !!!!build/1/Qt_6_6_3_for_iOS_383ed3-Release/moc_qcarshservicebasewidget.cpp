/****************************************************************************
** Meta object code from reading C++ file 'qcarshservicebasewidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qcarshservicebasewidget.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qcarshservicebasewidget.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSQCarshServiceBaseWidgetENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSQCarshServiceBaseWidgetENDCLASS = QtMocHelpers::stringData(
    "QCarshServiceBaseWidget",
    "OnMouseButtonPressedSignal",
    "",
    "OnMouseButtonPressedSlot",
    "OnSettingsModePressed",
    "OnLoginPressed",
    "OnRegisterPressed"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSQCarshServiceBaseWidgetENDCLASS_t {
    uint offsetsAndSizes[14];
    char stringdata0[24];
    char stringdata1[27];
    char stringdata2[1];
    char stringdata3[25];
    char stringdata4[22];
    char stringdata5[15];
    char stringdata6[18];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSQCarshServiceBaseWidgetENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSQCarshServiceBaseWidgetENDCLASS_t qt_meta_stringdata_CLASSQCarshServiceBaseWidgetENDCLASS = {
    {
        QT_MOC_LITERAL(0, 23),  // "QCarshServiceBaseWidget"
        QT_MOC_LITERAL(24, 26),  // "OnMouseButtonPressedSignal"
        QT_MOC_LITERAL(51, 0),  // ""
        QT_MOC_LITERAL(52, 24),  // "OnMouseButtonPressedSlot"
        QT_MOC_LITERAL(77, 21),  // "OnSettingsModePressed"
        QT_MOC_LITERAL(99, 14),  // "OnLoginPressed"
        QT_MOC_LITERAL(114, 17)   // "OnRegisterPressed"
    },
    "QCarshServiceBaseWidget",
    "OnMouseButtonPressedSignal",
    "",
    "OnMouseButtonPressedSlot",
    "OnSettingsModePressed",
    "OnLoginPressed",
    "OnRegisterPressed"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSQCarshServiceBaseWidgetENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   44,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       3,    0,   45,    2, 0x0a,    2 /* Public */,
       4,    0,   46,    2, 0x0a,    3 /* Public */,
       5,    0,   47,    2, 0x0a,    4 /* Public */,
       6,    0,   48,    2, 0x0a,    5 /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject QCarshServiceBaseWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSQCarshServiceBaseWidgetENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSQCarshServiceBaseWidgetENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSQCarshServiceBaseWidgetENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCarshServiceBaseWidget, std::true_type>,
        // method 'OnMouseButtonPressedSignal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'OnMouseButtonPressedSlot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'OnSettingsModePressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'OnLoginPressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'OnRegisterPressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void QCarshServiceBaseWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QCarshServiceBaseWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->OnMouseButtonPressedSignal(); break;
        case 1: _t->OnMouseButtonPressedSlot(); break;
        case 2: _t->OnSettingsModePressed(); break;
        case 3: _t->OnLoginPressed(); break;
        case 4: _t->OnRegisterPressed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QCarshServiceBaseWidget::*)();
            if (_t _q_method = &QCarshServiceBaseWidget::OnMouseButtonPressedSignal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
    (void)_a;
}

const QMetaObject *QCarshServiceBaseWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCarshServiceBaseWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSQCarshServiceBaseWidgetENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int QCarshServiceBaseWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void QCarshServiceBaseWidget::OnMouseButtonPressedSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
