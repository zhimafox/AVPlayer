/****************************************************************************
** Meta object code from reading C++ file 'FxProgressBar.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../FxVideoPlayer/FxProgressBar.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FxProgressBar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.1. It"
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
struct qt_meta_stringdata_CLASSFxProgressBarENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSFxProgressBarENDCLASS = QtMocHelpers::stringData(
    "FxProgressBar",
    "shouldShowThumbnail",
    "",
    "shouldHideThumbnail",
    "shouldSeekProgress",
    "ratio",
    "shouldWatchProgress",
    "shouldUpdateThumbnailPosition",
    "point"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSFxProgressBarENDCLASS_t {
    uint offsetsAndSizes[18];
    char stringdata0[14];
    char stringdata1[20];
    char stringdata2[1];
    char stringdata3[20];
    char stringdata4[19];
    char stringdata5[6];
    char stringdata6[20];
    char stringdata7[30];
    char stringdata8[6];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSFxProgressBarENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSFxProgressBarENDCLASS_t qt_meta_stringdata_CLASSFxProgressBarENDCLASS = {
    {
        QT_MOC_LITERAL(0, 13),  // "FxProgressBar"
        QT_MOC_LITERAL(14, 19),  // "shouldShowThumbnail"
        QT_MOC_LITERAL(34, 0),  // ""
        QT_MOC_LITERAL(35, 19),  // "shouldHideThumbnail"
        QT_MOC_LITERAL(55, 18),  // "shouldSeekProgress"
        QT_MOC_LITERAL(74, 5),  // "ratio"
        QT_MOC_LITERAL(80, 19),  // "shouldWatchProgress"
        QT_MOC_LITERAL(100, 29),  // "shouldUpdateThumbnailPosition"
        QT_MOC_LITERAL(130, 5)   // "point"
    },
    "FxProgressBar",
    "shouldShowThumbnail",
    "",
    "shouldHideThumbnail",
    "shouldSeekProgress",
    "ratio",
    "shouldWatchProgress",
    "shouldUpdateThumbnailPosition",
    "point"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSFxProgressBarENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   44,    2, 0x06,    1 /* Public */,
       3,    0,   45,    2, 0x06,    2 /* Public */,
       4,    1,   46,    2, 0x06,    3 /* Public */,
       6,    1,   49,    2, 0x06,    5 /* Public */,
       7,    1,   52,    2, 0x06,    7 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::QPointF,    8,

       0        // eod
};

Q_CONSTINIT const QMetaObject FxProgressBar::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSFxProgressBarENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSFxProgressBarENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSFxProgressBarENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<FxProgressBar, std::true_type>,
        // method 'shouldShowThumbnail'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'shouldHideThumbnail'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'shouldSeekProgress'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'shouldWatchProgress'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'shouldUpdateThumbnailPosition'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPointF, std::false_type>
    >,
    nullptr
} };

void FxProgressBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FxProgressBar *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->shouldShowThumbnail(); break;
        case 1: _t->shouldHideThumbnail(); break;
        case 2: _t->shouldSeekProgress((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->shouldWatchProgress((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->shouldUpdateThumbnailPosition((*reinterpret_cast< std::add_pointer_t<QPointF>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FxProgressBar::*)();
            if (_t _q_method = &FxProgressBar::shouldShowThumbnail; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (FxProgressBar::*)();
            if (_t _q_method = &FxProgressBar::shouldHideThumbnail; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (FxProgressBar::*)(int );
            if (_t _q_method = &FxProgressBar::shouldSeekProgress; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (FxProgressBar::*)(int );
            if (_t _q_method = &FxProgressBar::shouldWatchProgress; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (FxProgressBar::*)(QPointF );
            if (_t _q_method = &FxProgressBar::shouldUpdateThumbnailPosition; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject *FxProgressBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FxProgressBar::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSFxProgressBarENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int FxProgressBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void FxProgressBar::shouldShowThumbnail()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void FxProgressBar::shouldHideThumbnail()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void FxProgressBar::shouldSeekProgress(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void FxProgressBar::shouldWatchProgress(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void FxProgressBar::shouldUpdateThumbnailPosition(QPointF _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
