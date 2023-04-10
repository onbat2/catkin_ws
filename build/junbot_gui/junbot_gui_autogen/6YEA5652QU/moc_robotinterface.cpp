/****************************************************************************
** Meta object code from reading C++ file 'robotinterface.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "include/robotinterface.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'robotinterface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RobotInterface_t {
    QByteArrayData data[8];
    char stringdata0[136];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RobotInterface_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RobotInterface_t qt_meta_stringdata_RobotInterface = {
    {
QT_MOC_LITERAL(0, 0, 14), // "RobotInterface"
QT_MOC_LITERAL(1, 15, 24), // "on_actionAbout_triggered"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 17), // "slot_batteryState"
QT_MOC_LITERAL(4, 59, 25), // "sensor_msgs::BatteryState"
QT_MOC_LITERAL(5, 85, 16), // "slot_rosShutdown"
QT_MOC_LITERAL(6, 102, 16), // "refreshTopicList"
QT_MOC_LITERAL(7, 119, 16) // "slot_cmd_control"

    },
    "RobotInterface\0on_actionAbout_triggered\0"
    "\0slot_batteryState\0sensor_msgs::BatteryState\0"
    "slot_rosShutdown\0refreshTopicList\0"
    "slot_cmd_control"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RobotInterface[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    1,   40,    2, 0x0a /* Public */,
       5,    0,   43,    2, 0x0a /* Public */,
       6,    0,   44,    2, 0x0a /* Public */,
       7,    0,   45,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void RobotInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RobotInterface *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_actionAbout_triggered(); break;
        case 1: _t->slot_batteryState((*reinterpret_cast< sensor_msgs::BatteryState(*)>(_a[1]))); break;
        case 2: _t->slot_rosShutdown(); break;
        case 3: _t->refreshTopicList(); break;
        case 4: _t->slot_cmd_control(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject RobotInterface::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_RobotInterface.data,
    qt_meta_data_RobotInterface,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RobotInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RobotInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RobotInterface.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int RobotInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
