/****************************************************************************
** Meta object code from reading C++ file 'GameController.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/gui/GameController.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GameController.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.11.2. It"
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
struct qt_meta_tag_ZN14GameControllerE_t {};
} // unnamed namespace

template <> constexpr inline auto GameController::qt_create_metaobjectdata<qt_meta_tag_ZN14GameControllerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "GameController",
        "gameInitialized",
        "",
        "success",
        "gameLoaded",
        "gameSaved",
        "turnProcessed",
        "resultText",
        "combatProcessed",
        "eventTriggered",
        "eventText",
        "choices",
        "tavernOpened",
        "actions",
        "locationEntered",
        "locationName",
        "inventoryUpdated",
        "inventoryText",
        "questUpdated",
        "questText",
        "heroStatusUpdated",
        "statusText",
        "gameOver",
        "reason",
        "returnedToMainMenu",
        "combatStarted",
        "enemyName",
        "enemyHp",
        "enemyMaxHp",
        "enemyAttack",
        "enemyDefense",
        "combatUpdated",
        "heroHp",
        "heroMaxHp",
        "combatEnded",
        "message"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'gameInitialized'
        QtMocHelpers::SignalData<void(bool)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 3 },
        }}),
        // Signal 'gameLoaded'
        QtMocHelpers::SignalData<void(bool)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 3 },
        }}),
        // Signal 'gameSaved'
        QtMocHelpers::SignalData<void(bool)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 3 },
        }}),
        // Signal 'turnProcessed'
        QtMocHelpers::SignalData<void(const QString &)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 7 },
        }}),
        // Signal 'combatProcessed'
        QtMocHelpers::SignalData<void(const QString &)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 7 },
        }}),
        // Signal 'eventTriggered'
        QtMocHelpers::SignalData<void(const QString &, const QStringList &)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 10 }, { QMetaType::QStringList, 11 },
        }}),
        // Signal 'tavernOpened'
        QtMocHelpers::SignalData<void(const QStringList &)>(12, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QStringList, 13 },
        }}),
        // Signal 'locationEntered'
        QtMocHelpers::SignalData<void(const QString &, const QStringList &)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 15 }, { QMetaType::QStringList, 13 },
        }}),
        // Signal 'inventoryUpdated'
        QtMocHelpers::SignalData<void(const QString &)>(16, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 17 },
        }}),
        // Signal 'questUpdated'
        QtMocHelpers::SignalData<void(const QString &)>(18, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 19 },
        }}),
        // Signal 'heroStatusUpdated'
        QtMocHelpers::SignalData<void(const QString &)>(20, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 21 },
        }}),
        // Signal 'gameOver'
        QtMocHelpers::SignalData<void(const QString &)>(22, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 23 },
        }}),
        // Signal 'returnedToMainMenu'
        QtMocHelpers::SignalData<void()>(24, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'combatStarted'
        QtMocHelpers::SignalData<void(const QString &, int, int, int, int)>(25, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 26 }, { QMetaType::Int, 27 }, { QMetaType::Int, 28 }, { QMetaType::Int, 29 },
            { QMetaType::Int, 30 },
        }}),
        // Signal 'combatUpdated'
        QtMocHelpers::SignalData<void(int, int, int, int)>(31, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 27 }, { QMetaType::Int, 28 }, { QMetaType::Int, 32 }, { QMetaType::Int, 33 },
        }}),
        // Signal 'combatEnded'
        QtMocHelpers::SignalData<void(const QString &)>(34, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 35 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<GameController, qt_meta_tag_ZN14GameControllerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject GameController::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14GameControllerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14GameControllerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN14GameControllerE_t>.metaTypes,
    nullptr
} };

void GameController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<GameController *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->gameInitialized((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 1: _t->gameLoaded((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 2: _t->gameSaved((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 3: _t->turnProcessed((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->combatProcessed((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->eventTriggered((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QStringList>>(_a[2]))); break;
        case 6: _t->tavernOpened((*reinterpret_cast<std::add_pointer_t<QStringList>>(_a[1]))); break;
        case 7: _t->locationEntered((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QStringList>>(_a[2]))); break;
        case 8: _t->inventoryUpdated((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 9: _t->questUpdated((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 10: _t->heroStatusUpdated((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 11: _t->gameOver((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 12: _t->returnedToMainMenu(); break;
        case 13: _t->combatStarted((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[4])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[5]))); break;
        case 14: _t->combatUpdated((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[4]))); break;
        case 15: _t->combatEnded((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (GameController::*)(bool )>(_a, &GameController::gameInitialized, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (GameController::*)(bool )>(_a, &GameController::gameLoaded, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (GameController::*)(bool )>(_a, &GameController::gameSaved, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (GameController::*)(const QString & )>(_a, &GameController::turnProcessed, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (GameController::*)(const QString & )>(_a, &GameController::combatProcessed, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (GameController::*)(const QString & , const QStringList & )>(_a, &GameController::eventTriggered, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (GameController::*)(const QStringList & )>(_a, &GameController::tavernOpened, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (GameController::*)(const QString & , const QStringList & )>(_a, &GameController::locationEntered, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (GameController::*)(const QString & )>(_a, &GameController::inventoryUpdated, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (GameController::*)(const QString & )>(_a, &GameController::questUpdated, 9))
            return;
        if (QtMocHelpers::indexOfMethod<void (GameController::*)(const QString & )>(_a, &GameController::heroStatusUpdated, 10))
            return;
        if (QtMocHelpers::indexOfMethod<void (GameController::*)(const QString & )>(_a, &GameController::gameOver, 11))
            return;
        if (QtMocHelpers::indexOfMethod<void (GameController::*)()>(_a, &GameController::returnedToMainMenu, 12))
            return;
        if (QtMocHelpers::indexOfMethod<void (GameController::*)(const QString & , int , int , int , int )>(_a, &GameController::combatStarted, 13))
            return;
        if (QtMocHelpers::indexOfMethod<void (GameController::*)(int , int , int , int )>(_a, &GameController::combatUpdated, 14))
            return;
        if (QtMocHelpers::indexOfMethod<void (GameController::*)(const QString & )>(_a, &GameController::combatEnded, 15))
            return;
    }
}

const QMetaObject *GameController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GameController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14GameControllerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int GameController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void GameController::gameInitialized(bool _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void GameController::gameLoaded(bool _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void GameController::gameSaved(bool _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void GameController::turnProcessed(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void GameController::combatProcessed(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void GameController::eventTriggered(const QString & _t1, const QStringList & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1, _t2);
}

// SIGNAL 6
void GameController::tavernOpened(const QStringList & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1);
}

// SIGNAL 7
void GameController::locationEntered(const QString & _t1, const QStringList & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 7, nullptr, _t1, _t2);
}

// SIGNAL 8
void GameController::inventoryUpdated(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 8, nullptr, _t1);
}

// SIGNAL 9
void GameController::questUpdated(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 9, nullptr, _t1);
}

// SIGNAL 10
void GameController::heroStatusUpdated(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 10, nullptr, _t1);
}

// SIGNAL 11
void GameController::gameOver(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 11, nullptr, _t1);
}

// SIGNAL 12
void GameController::returnedToMainMenu()
{
    QMetaObject::activate(this, &staticMetaObject, 12, nullptr);
}

// SIGNAL 13
void GameController::combatStarted(const QString & _t1, int _t2, int _t3, int _t4, int _t5)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 13, nullptr, _t1, _t2, _t3, _t4, _t5);
}

// SIGNAL 14
void GameController::combatUpdated(int _t1, int _t2, int _t3, int _t4)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 14, nullptr, _t1, _t2, _t3, _t4);
}

// SIGNAL 15
void GameController::combatEnded(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 15, nullptr, _t1);
}
QT_WARNING_POP
