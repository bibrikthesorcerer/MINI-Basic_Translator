/****************************************************************************
** Meta object code from reading C++ file 'translator.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Translator-Mini-Basic/translator.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'translator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.0. It"
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
struct qt_meta_stringdata_CLASSTranslatorENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSTranslatorENDCLASS = QtMocHelpers::stringData(
    "Translator",
    "slotChangedWindowTitle",
    "",
    "slotNewDocument",
    "slotLoad",
    "slotSave",
    "slotSaveAs",
    "slotAbout",
    "slotWindows",
    "slotSetActiveSubWindow",
    "slotTranslate"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSTranslatorENDCLASS_t {
    uint offsetsAndSizes[22];
    char stringdata0[11];
    char stringdata1[23];
    char stringdata2[1];
    char stringdata3[16];
    char stringdata4[9];
    char stringdata5[9];
    char stringdata6[11];
    char stringdata7[10];
    char stringdata8[12];
    char stringdata9[23];
    char stringdata10[14];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSTranslatorENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSTranslatorENDCLASS_t qt_meta_stringdata_CLASSTranslatorENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "Translator"
        QT_MOC_LITERAL(11, 22),  // "slotChangedWindowTitle"
        QT_MOC_LITERAL(34, 0),  // ""
        QT_MOC_LITERAL(35, 15),  // "slotNewDocument"
        QT_MOC_LITERAL(51, 8),  // "slotLoad"
        QT_MOC_LITERAL(60, 8),  // "slotSave"
        QT_MOC_LITERAL(69, 10),  // "slotSaveAs"
        QT_MOC_LITERAL(80, 9),  // "slotAbout"
        QT_MOC_LITERAL(90, 11),  // "slotWindows"
        QT_MOC_LITERAL(102, 22),  // "slotSetActiveSubWindow"
        QT_MOC_LITERAL(125, 13)   // "slotTranslate"
    },
    "Translator",
    "slotChangedWindowTitle",
    "",
    "slotNewDocument",
    "slotLoad",
    "slotSave",
    "slotSaveAs",
    "slotAbout",
    "slotWindows",
    "slotSetActiveSubWindow",
    "slotTranslate"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSTranslatorENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   68,    2, 0x08,    1 /* Private */,
       3,    0,   71,    2, 0x08,    3 /* Private */,
       4,    0,   72,    2, 0x08,    4 /* Private */,
       5,    0,   73,    2, 0x08,    5 /* Private */,
       6,    0,   74,    2, 0x08,    6 /* Private */,
       7,    0,   75,    2, 0x08,    7 /* Private */,
       8,    0,   76,    2, 0x08,    8 /* Private */,
       9,    1,   77,    2, 0x08,    9 /* Private */,
      10,    0,   80,    2, 0x08,   11 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QObjectStar,    2,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject Translator::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSTranslatorENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSTranslatorENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSTranslatorENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Translator, std::true_type>,
        // method 'slotChangedWindowTitle'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'slotNewDocument'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'slotLoad'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'slotSave'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'slotSaveAs'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'slotAbout'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'slotWindows'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'slotSetActiveSubWindow'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QObject *, std::false_type>,
        // method 'slotTranslate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void Translator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Translator *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->slotChangedWindowTitle((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->slotNewDocument(); break;
        case 2: _t->slotLoad(); break;
        case 3: _t->slotSave(); break;
        case 4: _t->slotSaveAs(); break;
        case 5: _t->slotAbout(); break;
        case 6: _t->slotWindows(); break;
        case 7: _t->slotSetActiveSubWindow((*reinterpret_cast< std::add_pointer_t<QObject*>>(_a[1]))); break;
        case 8: _t->slotTranslate(); break;
        default: ;
        }
    }
}

const QMetaObject *Translator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Translator::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSTranslatorENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Translator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
