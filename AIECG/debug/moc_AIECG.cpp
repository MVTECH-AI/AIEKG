/****************************************************************************
** Meta object code from reading C++ file 'AIECG.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../AIECG.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AIECG.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AIECG[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       7,    6,    6,    6, 0x08,
      17,    6,    6,    6, 0x08,
      23,    6,    6,    6, 0x08,
      30,    6,    6,    6, 0x08,
      38,    6,    6,    6, 0x08,
      46,    6,    6,    6, 0x08,
      61,    6,    6,    6, 0x08,
      81,   73,    6,    6, 0x08,
     106,    6,    6,    6, 0x08,
     114,    6,    6,    6, 0x08,
     134,    6,    6,    6, 0x08,
     157,    6,    6,    6, 0x08,
     180,    6,    6,    6, 0x08,
     202,    6,    6,    6, 0x08,
     219,    6,    6,    6, 0x08,
     233,    6,    6,    6, 0x08,
     244,    6,    6,    6, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AIECG[] = {
    "AIECG\0\0newfile()\0cut()\0copy()\0paste()\0"
    "print()\0printPreview()\0setUpPage()\0"
    "printer\0printDocument(QPrinter*)\0"
    "about()\0openChannelWidnow()\0"
    "openPlotSignalWindow()\0openGridSignalWindow()\0"
    "openIBISignalWindow()\0openTextWindow()\0"
    "loadSignals()\0loadText()\0beginSVM()\0"
};

void AIECG::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AIECG *_t = static_cast<AIECG *>(_o);
        switch (_id) {
        case 0: _t->newfile(); break;
        case 1: _t->cut(); break;
        case 2: _t->copy(); break;
        case 3: _t->paste(); break;
        case 4: _t->print(); break;
        case 5: _t->printPreview(); break;
        case 6: _t->setUpPage(); break;
        case 7: _t->printDocument((*reinterpret_cast< QPrinter*(*)>(_a[1]))); break;
        case 8: _t->about(); break;
        case 9: _t->openChannelWidnow(); break;
        case 10: _t->openPlotSignalWindow(); break;
        case 11: _t->openGridSignalWindow(); break;
        case 12: _t->openIBISignalWindow(); break;
        case 13: _t->openTextWindow(); break;
        case 14: _t->loadSignals(); break;
        case 15: _t->loadText(); break;
        case 16: _t->beginSVM(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AIECG::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AIECG::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_AIECG,
      qt_meta_data_AIECG, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AIECG::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AIECG::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AIECG::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AIECG))
        return static_cast<void*>(const_cast< AIECG*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int AIECG::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
