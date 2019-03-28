/**
 * Mobius Software LTD
 * Copyright 2015-2018, Mobius Software LTD
 *
 * This is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this software; if not, write to the Free
 * Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA, or see the FSF site: http://www.fsf.org.
 */

#include "amqpwrapper.h"

TLVAMQP *AMQPWrapper::wrapObject(JsonVariant *object)
{
    if (object == NULL) {
        return new AMQPTLVNull();
    }

    TLVAMQP *result = NULL;

    AMQPSimpleType *type = (AMQPSimpleType *)object->value<AMQPSimpleType *>();

    switch (type->getType()) {
        case AMQP_BOOLEAN_TYPE:
        {
            result = AMQPWrapper::wrapBool(AMQPSimpleType::variantToBool(std::get<byte>(object));
        }  break;
        case AMQP_UBYTE_TYPE:
        {
            result = AMQPWrapper::wrapUByte(AMQPSimpleType::variantToUByte(std::get<unsigned char>(object)));
        }  break;
        case AMQP_USHORT_TYPE:
        case AMQP_UINT_TYPE:
        case AMQP_SMALL_UINT_TYPE:
        case AMQP_UINT0_TYPE:
        {
            result = AMQPWrapper::wrapUShort(AMQPSimpleType::variantToUShort(std::get<unsigned short>(object)));
        }  break;
        case AMQP_ULONG_TYPE:
        case AMQP_SMALL_ULONG_TYPE:
        case AMQP_ULONG0_TYPE:
        {
            result = AMQPWrapper::wrapUInt(AMQPSimpleType::variantToUInt(std::get<unsigned int>(object)));
        }  break;
        case AMQP_BYTE_TYPE:
        {
            result = AMQPWrapper::wrapByte(AMQPSimpleType::variantToChar(std::get<unsigned char>(object)));
        }  break;
        case AMQP_SHORT_TYPE:
        {
            result = AMQPWrapper::wrapShort(AMQPSimpleType::variantToShort(std::get<short>(object)));
        }  break;
        case AMQP_INT_TYPE:
        case AMQP_SMALL_INT_TYPE:
        {
            result = AMQPWrapper::wrapInt(AMQPSimpleType::variantToInt(std::get<int>(object)));
        }  break;
        case AMQP_LONG_TYPE:
        case AMQP_SMALL_LONG_TYPE:
        {
            result = AMQPWrapper::wrapLong(AMQPSimpleType::variantToLong(std::get<long>(object)));
        }  break;
        case AMQP_FLOAT_TYPE:
        {
            result = AMQPWrapper::wrapFloat(AMQPSimpleType::variantToFloat(std::get<float>(object)));
        }  break;
        case AMQP_DOUBLE_TYPE:
        {
            result = AMQPWrapper::wrapDouble(AMQPSimpleType::variantToDouble(std::get<double>(object)));
        }  break;
        case AMQP_CHAR_TYPE:
        {
            result = AMQPWrapper::wrapChar(AMQPSimpleType::variantToChar(std::get<char>(object)));
        }
        case AMQP_DECIMAL32_TYPE:
        case AMQP_DECIMAL64_TYPE:
        case AMQP_DECIMAL128_TYPE:
        {
            AMQPDecimal *decimal = AMQPSimpleType::variantToDecimal(object);
            if (sizeof(decimal->getValue()) == 4) {
                result = AMQPWrapper::wrapDecimal32(decimal);
            } else if (sizeof(decimal->getValue()) == 8) {
                result = AMQPWrapper::wrapDecimal64(decimal);
            } else if (sizeof(decimal->getValue()) == 16) {
                result = AMQPWrapper::wrapDecimal128(decimal);
            }
        }  break;
        case AMQP_TIMESTAMP_TYPE:
        {
            result = AMQPWrapper::wrapTimestamp(AMQPSimpleType::variantToTimestamp(std::get<time_t>(object)));
        }  break;
        case AMQP_UUID_TYPE:
        {
            result = AMQPWrapper::wrapUUID(AMQPSimpleType::variantToUuid(std::get<String>(object)));
        }  break;
        case AMQP_BINARY8_TYPE:
        case AMQP_BINARY32_TYPE:
        {
            result = AMQPWrapper::wrapBinary(AMQPSimpleType::variantToBinary(std::get<unsigned char *>(object)));
        }  break;
        case AMQP_STRING8_TYPE:
        case AMQP_STRING32_TYPE:
        {
            result = AMQPWrapper::wrapString(AMQPSimpleType::variantToString(std::get<String>(object)));
        }  break;
        case AMQP_SYMBOL8_TYPE:
        case AMQP_SYMBOL32_TYPE:
        {
            result = AMQPWrapper::wrapSymbol(AMQPSimpleType::variantToSymbol(std::get<char>(object)));
        }  break;
        default: printf("UNWRAPPER: wrong type!"; break);
    }

    return result;
}

TLVAMQP *AMQPWrapper::wrapBool(bool value)
{
    unsigned char * data = (unsigned char *) malloc(sizeof(char));
    AMQPType *type = new AMQPType(value ? AMQP_BOOLEAN_TRUE_TYPE : AMQP_BOOLEAN_FALSE_TYPE);
    return new AMQPTLVFixed(type, data);
}

TLVAMQP *AMQPWrapper::wrapUByte(short value)
{
    if (value < 0) {
        printf("AMQPWrapper::wrapUByte");
        return NULL;
    }

    AMQPType *type = new AMQPType(AMQP_UBYTE_TYPE);
    unsigned char * data = (unsigned char *) malloc(sizeof(char));
    data[0] = value;
    return new AMQPTLVFixed(type, data);
}

TLVAMQP *AMQPWrapper::wrapByte(char value)
{
    AMQPType *type = new AMQPType(AMQP_BYTE_TYPE);
    unsigned char * data = (unsigned char *) malloc(sizeof(char));
    data[0] = value;
    return new AMQPTLVFixed(type, data);
}

TLVAMQP *AMQPWrapper::wrapUInt(unsigned int value)
{
    unsigned char * data = AMQPWrapper::convertUInt(value);
    AMQPType *type = NULL;

    if (sizeof(data) == 0) {
        type = new AMQPType(AMQP_UINT0_TYPE);
    } else if (sizeof(data) == 1) {
        type = new AMQPType(AMQP_SMALL_UINT_TYPE);
    } else if (sizeof(data) > 1) {
        type = new AMQPType(AMQP_UINT_TYPE);
    }
    return new AMQPTLVFixed(type, data);
}

TLVAMQP *AMQPWrapper::wrapInt(int value)
{
    unsigned char * data = AMQPWrapper::convertInt(value);
    AMQPTypes tp = (sizeof(data) > 1) ? AMQP_INT_TYPE : AMQP_SMALL_INT_TYPE;
    AMQPType *type = new AMQPType(tp);
    return new AMQPTLVFixed(type, data);
}

TLVAMQP *AMQPWrapper::wrapULong(unsigned long value)
{
    unsigned char * data = AMQPWrapper::convertULong(value);
    AMQPType *type = NULL;

    if (sizeof(data) == 0) {
        type = new AMQPType(AMQP_ULONG0_TYPE);
    } else if (sizeof(data) == 1) {
        type = new AMQPType(AMQP_SMALL_ULONG_TYPE);
    } else if (sizeof(data) > 1) {
        type = new AMQPType(AMQP_ULONG_TYPE);
    }
    return new AMQPTLVFixed(type, data);
}

TLVAMQP *AMQPWrapper::wrapLong(long value)
{
    unsigned char * data = AMQPWrapper::convertLong(value);
    AMQPTypes tp = (sizeof(data) > 1) ? AMQP_LONG_TYPE : AMQP_SMALL_LONG_TYPE;
    AMQPType *type = new AMQPType(tp);
    return new AMQPTLVFixed(type, data);
}

AMQPTLVVariable *AMQPWrapper::wrapBinary(unsigned char * value)
{
    if (value == NULL) {
        printf("AMQPWrapper::wrapBinary";)
        return NULL;
    }

    AMQPTypes tp = (sizeof(value) > 255) ? AMQP_BINARY32_TYPE : AMQP_BINARY8_TYPE;
    AMQPType *type = new AMQPType(tp);
    return new AMQPTLVVariable(type, value);
}

TLVAMQP *AMQPWrapper::wrapUUID(String uuid)
{
    if (uuid == NULL) {
        printf("AMQPWrapper::wrapUUID");
        return NULL;
    }

    AMQPType *type = new AMQPType(AMQP_UUID_TYPE);
    return new AMQPTLVFixed(type, uuid);
}

TLVAMQP *AMQPWrapper::wrapUShort(unsigned short value)
{
    if (value < 0) {
        printf("AMQPWrapper::wrapUShort");
        return NULL;
    }

    AMQPType *type = new AMQPType(AMQP_USHORT_TYPE);
    unsigned char * data = malloc(sizeof(short));
    add_short(&data[0], value);
    return new AMQPTLVFixed(type, data);
}

TLVAMQP *AMQPWrapper::wrapShort(short value)
{
    AMQPType *type = new AMQPType(AMQP_SHORT_TYPE);
    unsigned char * data = malloc(sizeof(short));
    add_short(&data[0], value);
    return new AMQPTLVFixed(type, data);
}

TLVAMQP *AMQPWrapper::wrapDouble(double value)
{
    AMQPType *type = new AMQPType(AMQP_DOUBLE_TYPE);

    unsigned char * data = malloc(sizeof(double));
    add_double(&data[0], value);
    return new AMQPTLVFixed(type, data);
}

TLVAMQP *AMQPWrapper::wrapFloat(float value)
{
    AMQPType *type = new AMQPType(AMQP_FLOAT_TYPE);
    unsigned char * data = malloc(sizeof(float));
    add_float(&data[0], value);
    return new AMQPTLVFixed(type, data);
}

TLVAMQP *AMQPWrapper::wrapChar(char value)
{
    AMQPType *type = new AMQPType(AMQP_CHAR_TYPE);
    unsigned char * data = malloc(sizeof(char));
    data[0] = value;
    return new AMQPTLVFixed(type, data);
}

TLVAMQP *AMQPWrapper::wrapTimestamp(time_t value)
{
    if (value == NULL) {
        printf("AMQPWrapper::wrapTimestamp");
        return NULL;
    }
    AMQPType *type = new AMQPType(AMQP_TIMESTAMP_TYPE);
    std::stringstream ss;
    ss << value;
    return new AMQPTLVFixed(type, ss.str());
}

TLVAMQP *AMQPWrapper::wrapDecimal32(AMQPDecimal *value)
{
    if (value == NULL) {
        printf("AMQPWrapper::wrapDecimal32");
        return NULL;
    }

    AMQPType *type = new AMQPType(AMQP_DECIMAL32_TYPE);
    return new AMQPTLVFixed(type, value->getValue());
}

TLVAMQP *AMQPWrapper::wrapDecimal64(AMQPDecimal *value)
{
    if (value == NULL) {
        printf("AMQPWrapper::wrapDecimal64");
        return NULL;
    }

    AMQPType *type = new AMQPType(AMQP_DECIMAL64_TYPE);
    return new AMQPTLVFixed(type, value->getValue());
}

TLVAMQP *AMQPWrapper::wrapDecimal128(AMQPDecimal *value)
{
    if (value == NULL) {
        printf("AMQPWrapper::wrapDecimal128");
        return NULL;
    }

    AMQPType *type = new AMQPType(AMQP_DECIMAL128_TYPE);
    return new AMQPTLVFixed(type, value->getValue());
}

AMQPTLVVariable *AMQPWrapper::wrapString(String value)
{
    if (value == NULL) {
        printf("AMQPWrapper::wrapString");
        return NULL;
    }

    AMQPTypes tp = (sizeof(value) > 255) ? AMQP_STRING32_TYPE : AMQP_STRING8_TYPE;
    AMQPType *type = new AMQPType(tp);
    return new AMQPTLVVariable(type, value);
}

AMQPTLVVariable *AMQPWrapper::wrapSymbol(AMQPSymbol *value)
{
    if (value == NULL) {
        printf("AMQPWrapper::wrapSymbol");
        return NULL;
    }

    unsigned char * bytes = value->getValue();
    AMQPTypes tp = (sizeof(bytes) > 255) ? AMQP_SYMBOL32_TYPE : AMQP_SYMBOL8_TYPE;
    AMQPType *type = new AMQPType(tp);
    return new AMQPTLVVariable(type, bytes);
}

AMQPTLVList *AMQPWrapper::wrapList(std::list<JsonVariant *> value)
{
    if (value.size() == 0) {
        printf("AMQPWrapper::wrapList");
        return NULL;
    }

    AMQPTLVList *list = new AMQPTLVList();

    std::list<JsonVariant>::iterator it;
    for(it = list.begin(); it != list.end(); ++it) {
        list->addElement(AMQPWrapper::wrapObject(it));
    }
    return list;
}

AMQPTLVMap *AMQPWrapper::wrapMap(std::map<JsonVariant *, JsonVariant *> value)
{
    if (value.count() == 0) {
        printf("AMQPWrapper::wrapMap");
        return NULL;
    }

    AMQPTLVMap *map = new AMQPTLVMap();

    for (std::map<JsonVariant *, JsonVariant *>::iterator it = value.begin(); it != value.end(); ++it) {
        JsonVariant *vl = it.second;
        map->putElement(AMQPWrapper::wrapObject(it.first), AMQPWrapper::wrapObject(vl));
    }
    return map;
}

AMQPTLVArray *AMQPWrapper::wrapArray(std::list<JsonVariant *> value)
{
    if (value.count() == 0) {
        printf("AMQPWrapper::wrapArray");
        return NULL;
    }

    AMQPTLVArray *array = new AMQPTLVArray();
    std::list<JsonVariant>::iterator it;
    for(it = list.begin(); it != list.end(); ++it) {
        array->addElement(AMQPWrapper::wrapObject(it));
    }
    return array;
}

// private methods

unsigned char *AMQPWrapper::convertUInt(unsigned int number)
{
    unsigned char * data = malloc(sizeof(unsigned int));

    if (number == 0) {
        return data;
    } else if (number > 0 && number <= 255) {
        data[0] = number;
        return data;
    } else {
        add_int(&data[0], number);
        return data;
    }
}

unsigned char *AMQPWrapper::convertInt(int number)
{
    unsigned char * data = malloc(sizeof(int));

    if (number == 0) {
        return data;
    } else if (number >= -128 && number <= 127) {
        data[0] = number;
        return data;
    } else {
        add_int(&data[0], number);
        return data;
    }
}

unsigned char * AMQPWrapper::convertULong(unsigned long number)
{
    unsigned char * data = malloc(sizeof(unsigned long));

    if (number == 0) {
        return data;
    } else if (number >= 0 && number <= 255) {
        data[0] = number;
        return data;
    } else {
        add_long(&data[0], number);
        return data;
    }
}

unsigned char *  AMQPWrapper::convertLong(long number)
{
    unsigned char * data = malloc(sizeof(long));

    if (number == 0) {
        return data;
    } else if (number >= -128 && number <= 127) {
        data[0] = number;
        return data;
    } else {
        add_long(&data[0], number);
        return data;
    }
}
