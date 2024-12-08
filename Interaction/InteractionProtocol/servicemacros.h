/** @file
\copyright   (c) CodLix LLC
\authors     Колосов В.В.
\version     1.0
Project:     VideoSystem
File:        servicemacros.h
* @brief     Протокол взаимодействия клиента с сервером. Сервисные макросы.
**/
#ifndef SERVICEMACROS_H
#define SERVICEMACROS_H

#include <QObject>
#include "interactionprotocoltypes.h"

/// \brief макрос самокопирования класса струтктуры для оператора присваивания
#define OPERATOR_EQUAL_BODY \
    if (this != &obj) { \
        selfCopy(obj); \
    } \
    return *this

/// \brief тег тип класса EDataType
#define TYPE_TAG "_type"

#define UID_REQUEST_TAG "_uidRequest"

/// \remark парсеры в/из JSON типов данных

/// \brief парсинг из json-поля в пременную типа QString
#define JSON_TO_QDATETIME(_json, _variable) \
    _variable = QDateTime::fromString(_json.value(#_variable).toString(), Qt::ISODate)

/// \brief парсинг пременной типа QString в json-object
#define QDATETIME_TO_JSON(_variable, _object) \
    _object.insert(#_variable, QJsonValue::fromVariant(_variable.toString(Qt::ISODate)))

/// \brief парсинг из json-поля в пременную типа QString
#define JSON_TO_QSTRING(_json, _variable) \
    _variable = _json.value(#_variable).toString()

/// \brief парсинг из json-поля в пременную типа QString без тримминга
#define JSON_TO_QSTRING_NO_TRIM(_json, _variable) \
    _variable = _json.value(#_variable).toString()

/// \brief парсинг пременной типа QString в json-object
#define QSTRING_TO_JSON(_variable, _object) \
    _object.insert(#_variable, QJsonValue::fromVariant(_variable))

/// \brief парсинг из json-поля в пременную типа QUuid
#define JSON_TO_QUUID(_json, _variable) \
    _variable = QUuid(_json.value(#_variable).toString())

/// \brief парсинг пременной типа QUuid в json-object
#define QUUID_TO_JSON(_variable, _object) \
    _object.insert(#_variable, QJsonValue::fromVariant(_variable.toString()))

/// \brief парсинг из json-поля в пременную типа enum enumType
 #define JSON_TO_ENUM(_json, enumType, _variable) \
    _variable = static_cast<enumType>( _json.value(#_variable).toString().toUInt() )

/// \brief парсинг пременной типа enum enumType в json-object
#define ENUM_TO_JSON(_variable, _object) \
    _object.insert(#_variable, QJsonValue::fromVariant( QString::number(static_cast<quint32>(_variable)) ))

/// \brief парсинг из json-поля в пременную типа double
#define JSON_TO_DOUBLE(_json, _variable) \
    _variable = _json.value(#_variable).toDouble()

/// \brief парсинг пременной типа double в json-object
#define DOUBLE_TO_JSON(_variable, _object) \
    _object.insert(#_variable, QJsonValue::fromVariant(_variable))

/// \brief парсинг из json-поля в пременную типа int
#define JSON_TO_INT(_json, _variable) \
    _variable = _json.value(#_variable).toInt()

/// \brief парсинг пременной типа int в json-object
#define INT_TO_JSON(_variable, _object) \
    _object.insert(#_variable, QJsonValue::fromVariant(_variable))


/// \brief парсинг из json-поля в пременную типа long_long
#define JSON_TO_LONG_LONG(_json, _variable) \
    _variable = _json.value(#_variable).toString().toLongLong()

/// \brief парсинг пременной типа int в json-object
#define LONG_LONG_TO_JSON(_variable, _object) \
    _object.insert(#_variable, QJsonValue::fromVariant(QString::number(_variable)))

/// \brief парсинг из json-поля в пременную типа bool
#define JSON_TO_BOOL(_json, _variable) \
    _variable = _json.value(#_variable).toBool()

/// \brief парсинг пременной типа bool в json-object
#define BOOL_TO_JSON(_variable, _object) \
    _object.insert(#_variable, QJsonValue::fromVariant(_variable))

/// \brief парсинг пременной типа Vector<_typeItem>, где _typeItem - Jsonable в json-object
#define QVECTOR_STRUCT_TO_JSON(_variable, _typeItem, _object) \
    if (!_variable.isEmpty()) { \
        QJsonArray json##_variable; \
        foreach (_typeItem _item, _variable) { \
            json##_variable.append( _item.toJsonObject() ); \
        } \
        _object.insert(#_variable, json##_variable); \
    }

/// \brief парсинг из json-поля в пременную типа Vector<_typeItem>, где _typeItem - Jsonable
#define JSON_TO_QVECTOR_STRUCT(_json, _typeItem, _variable) \
    if (_json.contains(#_variable)) { \
        auto _items = _json.value(#_variable); \
        if (_items.isArray()) { \
            auto _itemsArray = _items.toArray(); \
            if (!_itemsArray.isEmpty()) { \
                foreach (QJsonValue _value, _itemsArray) { \
                    _typeItem _item( _value.toObject() ); \
                    _variable.append( _item ); \
                } \
            } \
        } \
    }

/// \brief парсинг из json-поля в пременную типа _typeItem - Jsonable
#define JSON_TO_STRUCT(_json, _typeItem, _variable) \
    if (_json.contains(#_variable)) { \
        auto _items = _json.value(#_variable); \
        if (_items.isArray()) { \
            auto _itemsArray = _items.toArray(); \
            if (!_itemsArray.isEmpty()) { \
                foreach (QJsonValue _value, _itemsArray) { \
                    _variable = _typeItem( _value.toObject() ); \
                    break; \
                } \
            } \
        } \
    }

/// \brief парсинг пременной типа _typeItem - Jsonable в json-object
#define STRUCT_TO_JSON(_variable, _typeItem, _object) \
    { \
        QJsonArray json##_variable; \
        json##_variable.append( _variable.toJsonObject() ); \
        _object.insert(#_variable, json##_variable); \
    }

#define QMAP_QUUID_STRUCT_TO_JSON(_variable, _typeItem, _object) \
    if (!_variable.isEmpty()) { \
        QJsonArray json##_variable; \
        QJsonArray json##_variable##_keys; \
        auto _variable##_count = _variable.keys().length(); \
        auto _variable##_keys = _variable.keys(); \
        for (auto _variable##_index = 0; _variable##_index < _variable##_count; _variable##_index++) { \
            json##_variable##_keys.append( _variable##_keys[_variable##_index].toString().trimmed()  ); \
            json##_variable.append( _variable.operator [](_variable##_keys[_variable##_index]).toJsonObject() ); \
        } \
        _object.insert(#_variable, json##_variable); \
        _object.insert(QString(#_variable) + "_keys", json##_variable##_keys); \
    }

#define JSON_TO_QMAP_QUUID_STRUCT(_json, _typeItem, _variable) \
    if (_json.contains(#_variable)) { \
        auto _items = _json.value(#_variable); \
        auto _items##_keys = _json.value(QString(#_variable) + "_keys"); \
        if (_items.isArray()) { \
            auto _itemsArray = _items.toArray(); \
            auto _itemsArray##_keys = _items##_keys.toArray(); \
            auto _variable##_count =  _itemsArray.count(); \
            for (auto _variable##_index = 0; _variable##_index < _variable##_count; _variable##_index++) { \
                QUuid _variable##_uid = QUuid( _itemsArray##_keys[_variable##_index].toString() ); \
                _typeItem _item( _itemsArray[_variable##_index].toObject() ); \
                _variable.insert(_variable##_uid, _item); \
            } \
        } \
    }

#endif // SERVICEMACROS_H
