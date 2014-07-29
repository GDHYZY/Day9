/****************************************************************************
** Meta object code from reading C++ file 'painter.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../painter2/painter.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'painter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_myPainter_t {
    QByteArrayData data[17];
    char stringdata[203];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_myPainter_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_myPainter_t qt_meta_stringdata_myPainter = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 6),
QT_MOC_LITERAL(2, 17, 0),
QT_MOC_LITERAL(3, 18, 6),
QT_MOC_LITERAL(4, 25, 10),
QT_MOC_LITERAL(5, 36, 9),
QT_MOC_LITERAL(6, 46, 11),
QT_MOC_LITERAL(7, 58, 10),
QT_MOC_LITERAL(8, 69, 9),
QT_MOC_LITERAL(9, 79, 13),
QT_MOC_LITERAL(10, 93, 16),
QT_MOC_LITERAL(11, 110, 14),
QT_MOC_LITERAL(12, 125, 18),
QT_MOC_LITERAL(13, 144, 14),
QT_MOC_LITERAL(14, 159, 15),
QT_MOC_LITERAL(15, 175, 14),
QT_MOC_LITERAL(16, 190, 12)
    },
    "myPainter\0myredo\0\0myundo\0clearimage\0"
    "grayimage\0mySolidLine\0myDashLine\0"
    "myDotLine\0myDashDotLine\0myDashDotDotLine\0"
    "mySolidPattern\0myDiagCrossPattern\0"
    "myCrossPattern\0myDense7Pattern\0"
    "myBDiagPattern\0myHorPattern"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_myPainter[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x0a /* Public */,
       3,    0,   90,    2, 0x0a /* Public */,
       4,    0,   91,    2, 0x0a /* Public */,
       5,    0,   92,    2, 0x0a /* Public */,
       6,    0,   93,    2, 0x0a /* Public */,
       7,    0,   94,    2, 0x0a /* Public */,
       8,    0,   95,    2, 0x0a /* Public */,
       9,    0,   96,    2, 0x0a /* Public */,
      10,    0,   97,    2, 0x0a /* Public */,
      11,    0,   98,    2, 0x0a /* Public */,
      12,    0,   99,    2, 0x0a /* Public */,
      13,    0,  100,    2, 0x0a /* Public */,
      14,    0,  101,    2, 0x0a /* Public */,
      15,    0,  102,    2, 0x0a /* Public */,
      16,    0,  103,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void myPainter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        myPainter *_t = static_cast<myPainter *>(_o);
        switch (_id) {
        case 0: _t->myredo(); break;
        case 1: _t->myundo(); break;
        case 2: _t->clearimage(); break;
        case 3: _t->grayimage(); break;
        case 4: _t->mySolidLine(); break;
        case 5: _t->myDashLine(); break;
        case 6: _t->myDotLine(); break;
        case 7: _t->myDashDotLine(); break;
        case 8: _t->myDashDotDotLine(); break;
        case 9: _t->mySolidPattern(); break;
        case 10: _t->myDiagCrossPattern(); break;
        case 11: _t->myCrossPattern(); break;
        case 12: _t->myDense7Pattern(); break;
        case 13: _t->myBDiagPattern(); break;
        case 14: _t->myHorPattern(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject myPainter::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_myPainter.data,
      qt_meta_data_myPainter,  qt_static_metacall, 0, 0}
};


const QMetaObject *myPainter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *myPainter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_myPainter.stringdata))
        return static_cast<void*>(const_cast< myPainter*>(this));
    return QWidget::qt_metacast(_clname);
}

int myPainter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
