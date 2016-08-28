/****************************************************************************
** Meta object code from reading C++ file 'calendar.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../myCalendar/calendar.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'calendar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_calendar_t {
    QByteArrayData data[3];
    char stringdata0[18];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_calendar_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_calendar_t qt_meta_stringdata_calendar = {
    {
QT_MOC_LITERAL(0, 0, 8), // "calendar"
QT_MOC_LITERAL(1, 9, 7), // "addNote"
QT_MOC_LITERAL(2, 17, 0) // ""

    },
    "calendar\0addNote\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_calendar[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QDate,    2,

       0        // eod
};

void calendar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        calendar *_t = static_cast<calendar *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->addNote((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject calendar::staticMetaObject = {
    { &QCalendarWidget::staticMetaObject, qt_meta_stringdata_calendar.data,
      qt_meta_data_calendar,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *calendar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *calendar::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_calendar.stringdata0))
        return static_cast<void*>(const_cast< calendar*>(this));
    return QCalendarWidget::qt_metacast(_clname);
}

int calendar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCalendarWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
