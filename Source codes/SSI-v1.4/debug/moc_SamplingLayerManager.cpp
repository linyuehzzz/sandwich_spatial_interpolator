/****************************************************************************
** Meta object code from reading C++ file 'SamplingLayerManager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SamplingLayerManager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SamplingLayerManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SamplingLayerManager_t {
    QByteArrayData data[19];
    char stringdata0[227];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SamplingLayerManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SamplingLayerManager_t qt_meta_stringdata_SamplingLayerManager = {
    {
QT_MOC_LITERAL(0, 0, 20), // "SamplingLayerManager"
QT_MOC_LITERAL(1, 21, 8), // "SendData"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 6), // "code_2"
QT_MOC_LITERAL(4, 38, 5), // "field"
QT_MOC_LITERAL(5, 44, 8), // "filename"
QT_MOC_LITERAL(6, 53, 6), // "code_3"
QT_MOC_LITERAL(7, 60, 4), // "size"
QT_MOC_LITERAL(8, 65, 13), // "GetFieldNames"
QT_MOC_LITERAL(9, 79, 15), // "vector<QString>"
QT_MOC_LITERAL(10, 95, 4), // "path"
QT_MOC_LITERAL(11, 100, 16), // "SetComboBoxValue"
QT_MOC_LITERAL(12, 117, 20), // "ComboBoxValueChanged"
QT_MOC_LITERAL(13, 138, 15), // "on_load_clicked"
QT_MOC_LITERAL(14, 154, 17), // "on_create_clicked"
QT_MOC_LITERAL(15, 172, 11), // "ReceiveData"
QT_MOC_LITERAL(16, 184, 10), // "sampleSize"
QT_MOC_LITERAL(17, 195, 17), // "on_Cancel_clicked"
QT_MOC_LITERAL(18, 213, 13) // "on_OK_clicked"

    },
    "SamplingLayerManager\0SendData\0\0code_2\0"
    "field\0filename\0code_3\0size\0GetFieldNames\0"
    "vector<QString>\0path\0SetComboBoxValue\0"
    "ComboBoxValueChanged\0on_load_clicked\0"
    "on_create_clicked\0ReceiveData\0sampleSize\0"
    "on_Cancel_clicked\0on_OK_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SamplingLayerManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    5,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,   70,    2, 0x0a /* Public */,
      11,    0,   73,    2, 0x0a /* Public */,
      12,    1,   74,    2, 0x0a /* Public */,
      13,    0,   77,    2, 0x08 /* Private */,
      14,    0,   78,    2, 0x08 /* Private */,
      15,    2,   79,    2, 0x08 /* Private */,
      17,    0,   84,    2, 0x08 /* Private */,
      18,    0,   85,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::Int, QMetaType::Int,    3,    4,    5,    6,    7,

 // slots: parameters
    0x80000000 | 9, QMetaType::QString,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,   16,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SamplingLayerManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SamplingLayerManager *_t = static_cast<SamplingLayerManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SendData((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 1: { vector<QString> _r = _t->GetFieldNames((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< vector<QString>*>(_a[0]) = _r; }  break;
        case 2: _t->SetComboBoxValue(); break;
        case 3: _t->ComboBoxValueChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->on_load_clicked(); break;
        case 5: _t->on_create_clicked(); break;
        case 6: _t->ReceiveData((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->on_Cancel_clicked(); break;
        case 8: _t->on_OK_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SamplingLayerManager::*_t)(int , QString , QString , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SamplingLayerManager::SendData)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject SamplingLayerManager::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SamplingLayerManager.data,
      qt_meta_data_SamplingLayerManager,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SamplingLayerManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SamplingLayerManager::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SamplingLayerManager.stringdata0))
        return static_cast<void*>(const_cast< SamplingLayerManager*>(this));
    return QDialog::qt_metacast(_clname);
}

int SamplingLayerManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void SamplingLayerManager::SendData(int _t1, QString _t2, QString _t3, int _t4, int _t5)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
