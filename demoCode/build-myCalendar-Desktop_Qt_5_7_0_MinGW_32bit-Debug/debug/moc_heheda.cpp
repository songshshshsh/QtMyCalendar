/****************************************************************************
** Meta object code from reading C++ file 'heheda.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../myCalendar/heheda.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'heheda.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Heheda_t {
    QByteArrayData data[8];
    char stringdata0[67];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Heheda_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Heheda_t qt_meta_stringdata_Heheda = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Heheda"
QT_MOC_LITERAL(1, 7, 10), // "updateinfo"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 11), // "memochanged"
QT_MOC_LITERAL(4, 31, 12), // "textlistshow"
QT_MOC_LITERAL(5, 44, 4), // "date"
QT_MOC_LITERAL(6, 49, 11), // "updatefiles"
QT_MOC_LITERAL(7, 61, 5) // "piece"

    },
    "Heheda\0updateinfo\0\0memochanged\0"
    "textlistshow\0date\0updatefiles\0piece"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Heheda[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x0a /* Public */,
       3,    0,   35,    2, 0x0a /* Public */,
       4,    1,   36,    2, 0x0a /* Public */,
       6,    2,   39,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QDate,    5,
    QMetaType::Void, QMetaType::QDate, QMetaType::QString,    5,    7,

       0        // eod
};

void Heheda::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Heheda *_t = static_cast<Heheda *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateinfo(); break;
        case 1: _t->memochanged(); break;
        case 2: _t->textlistshow((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 3: _t->updatefiles((*reinterpret_cast< const QDate(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject Heheda::staticMetaObject = {
    { &QCalendarWidget::staticMetaObject, qt_meta_stringdata_Heheda.data,
      qt_meta_data_Heheda,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Heheda::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Heheda::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Heheda.stringdata0))
        return static_cast<void*>(const_cast< Heheda*>(this));
    return QCalendarWidget::qt_metacast(_clname);
}

int Heheda::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCalendarWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
