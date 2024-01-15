/****************************************************************************
** Meta object code from reading C++ file 'nextshapeview.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../TetrisPartOne/nextshapeview.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'nextshapeview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.0. It"
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
struct qt_meta_stringdata_CLASSNextShapeViewENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSNextShapeViewENDCLASS = QtMocHelpers::stringData(
    "NextShapeView",
    "nextShapeToGraphicTetris",
    "",
    "createNextShape",
    "sendNextShapeNum",
    "clearScene"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSNextShapeViewENDCLASS_t {
    uint offsetsAndSizes[12];
    char stringdata0[14];
    char stringdata1[25];
    char stringdata2[1];
    char stringdata3[16];
    char stringdata4[17];
    char stringdata5[11];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSNextShapeViewENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSNextShapeViewENDCLASS_t qt_meta_stringdata_CLASSNextShapeViewENDCLASS = {
    {
        QT_MOC_LITERAL(0, 13),  // "NextShapeView"
        QT_MOC_LITERAL(14, 24),  // "nextShapeToGraphicTetris"
        QT_MOC_LITERAL(39, 0),  // ""
        QT_MOC_LITERAL(40, 15),  // "createNextShape"
        QT_MOC_LITERAL(56, 16),  // "sendNextShapeNum"
        QT_MOC_LITERAL(73, 10)   // "clearScene"
    },
    "NextShapeView",
    "nextShapeToGraphicTetris",
    "",
    "createNextShape",
    "sendNextShapeNum",
    "clearScene"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSNextShapeViewENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   38,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       3,    0,   41,    2, 0x0a,    3 /* Public */,
       4,    0,   42,    2, 0x0a,    4 /* Public */,
       5,    0,   43,    2, 0x0a,    5 /* Public */,

 // signals: parameters
    QMetaType::Int, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject NextShapeView::staticMetaObject = { {
    QMetaObject::SuperData::link<GraphicTetris::staticMetaObject>(),
    qt_meta_stringdata_CLASSNextShapeViewENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSNextShapeViewENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSNextShapeViewENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<NextShapeView, std::true_type>,
        // method 'nextShapeToGraphicTetris'
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'createNextShape'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sendNextShapeNum'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'clearScene'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void NextShapeView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NextShapeView *>(_o);
        (void)_t;
        switch (_id) {
        case 0: { int _r = _t->nextShapeToGraphicTetris((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 1: _t->createNextShape(); break;
        case 2: _t->sendNextShapeNum(); break;
        case 3: _t->clearScene(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = int (NextShapeView::*)(int );
            if (_t _q_method = &NextShapeView::nextShapeToGraphicTetris; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *NextShapeView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NextShapeView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSNextShapeViewENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return GraphicTetris::qt_metacast(_clname);
}

int NextShapeView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = GraphicTetris::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
int NextShapeView::nextShapeToGraphicTetris(int _t1)
{
    int _t0{};
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t0))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
    return _t0;
}
QT_WARNING_POP
