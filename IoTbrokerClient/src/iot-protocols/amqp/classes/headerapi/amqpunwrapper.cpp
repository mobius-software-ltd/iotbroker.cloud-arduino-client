unwrapTimestamp/**
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

#include "amqpunwrapper.h"
#include "iot-protocols/amqp/classes/amqpsimpletype.h"

JsonVariant *AMQPUnwrapper::unwrap(TLVAMQP *value)
{
    switch (value->getTypeValue()) {
        case AMQP_NULL_TYPE:
        {
            return NULL;
        }  break;
        case AMQP_BOOLEAN_TYPE:
        case AMQP_BOOLEAN_TRUE_TYPE:
        case AMQP_BOOLEAN_FALSE_TYPE:
        {
            return AMQPSimpleType::boolToVariant(AMQPUnwrapper::unwrapBool(value));
        }  break;
        case AMQP_UBYTE_TYPE:
        {
            return AMQPSimpleType::UByteToVariant(AMQPUnwrapper::unwrapUByte(value));
        }  break;
        case AMQP_USHORT_TYPE:
        {
            return AMQPSimpleType::UShortToVariant(AMQPUnwrapper::unwrapUShort(value));
        }  break;
        case AMQP_UINT_TYPE:
        case AMQP_SMALL_UINT_TYPE:
        case AMQP_UINT0_TYPE:
        {
            return AMQPSimpleType::UIntToVariant(AMQPUnwrapper::unwrapUInt(value));
        }  break;
        case AMQP_ULONG_TYPE:
        case AMQP_SMALL_ULONG_TYPE:
        case AMQP_ULONG0_TYPE:
        {
            return AMQPSimpleType::ULongToVariant(AMQPUnwrapper::unwrapULong(value));
        }  break;
        case AMQP_BYTE_TYPE:
        {
            return AMQPSimpleType::charToVariant(AMQPUnwrapper::unwrapByte(value));
        }  break;
        case AMQP_SHORT_TYPE:
        {
            return AMQPSimpleType::shortToVariant(AMQPUnwrapper::unwrapShort(value));
        }  break;
        case AMQP_INT_TYPE:
        case AMQP_SMALL_INT_TYPE:
        {
            return AMQPSimpleType::intToVariant(AMQPUnwrapper::unwrapInt(value));
        }  break;
        case AMQP_LONG_TYPE:
        case AMQP_SMALL_LONG_TYPE:
        {
            return AMQPSimpleType::longToVariant(AMQPUnwrapper::unwrapLong(value));
        }  break;
        case AMQP_FLOAT_TYPE:
        {
            return AMQPSimpleType::floatToVariant(AMQPUnwrapper::unwrapFloat(value));
        }  break;
        case AMQP_DOUBLE_TYPE:
        {
            return AMQPSimpleType::doubleToVariant(AMQPUnwrapper::unwrapDouble(value));
        }  break;
        case AMQP_DECIMAL32_TYPE:
        case AMQP_DECIMAL64_TYPE:
        case AMQP_DECIMAL128_TYPE:
        {
            return AMQPSimpleType::decimalToVariant(AMQPUnwrapper::unwrapDecimal(value));
        }  break;
        case AMQP_CHAR_TYPE:
        {
            return AMQPSimpleType::charToVariant(AMQPUnwrapper::unwrapByte(value));
        }  break;
        case AMQP_TIMESTAMP_TYPE:
        {
            return AMQPSimpleType::timestampToVariant(AMQPUnwrapper::unwrapTimestamp(value));
        }  break;
        case AMQP_UUID_TYPE:
        {
            return AMQPSimpleType::uuidToVariant(AMQPUnwrapper::unwrapUUID(value));
        }  break;
        case AMQP_BINARY8_TYPE:
        case AMQP_BINARY32_TYPE:
        {
            return AMQPSimpleType::binaryToVariant(AMQPUnwrapper::unwrapBinary(value));
        }  break;
        case AMQP_STRING8_TYPE:
        case AMQP_STRING32_TYPE:
        {
            return AMQPSimpleType::stringToVariant(AMQPUnwrapper::unwrapString(value));
        }  break;
        case AMQP_SYMBOL8_TYPE:
        case AMQP_SYMBOL32_TYPE:
        {
            return AMQPSimpleType::symbolToVariant(AMQPUnwrapper::unwrapSymbol(value));
        }  break;
    default: break;
    }
    return NULL;
}

short AMQPUnwrapper::unwrapUByte(TLVAMQP *tlv)
{
    if (tlv->getTypeValue() != AMQP_UBYTE_TYPE) {
        printf("AMQPUnwrapper::unwrapUByte");
        return 0;
    }
    char *bytes = tlv->getValue();
    return (short)(bytes[0] & 0xff);
}

char AMQPUnwrapper::unwrapByte(TLVAMQP *tlv)
{
    if (tlv->getTypeValue() != AMQP_BYTE_TYPE) {
        printf("AMQPUnwrapper::unwrapByte");
        return 0;
    }
    char *bytes = tlv->getValue();
    return bytes[0];
}

int AMQPUnwrapper::unwrapUShort(TLVAMQP *tlv)
{
    if (tlv->getTypeValue() != AMQP_USHORT_TYPE) {
        printf("AMQPUnwrapper::unwrapUShort");
        return 0;
    }

    char *bytes = tlv->getValue();
    short value = get_short(bytes, 0) & 0xffff;
    return value;
}

short AMQPUnwrapper::unwrapShort(TLVAMQP *tlv)
{
    if (tlv->getTypeValue() != AMQP_SHORT_TYPE) {
        printf("AMQPUnwrapper::unwrapShort");
        return 0;
    }

    char *bytes = tlv->getValue();
    short value = get_short(bytes, 0);
    return value;
}

long AMQPUnwrapper::unwrapUInt(TLVAMQP *tlv)
{
    if (tlv->getTypeValue() != AMQP_UINT0_TYPE &&
            tlv->getTypeValue() != AMQP_SMALL_UINT_TYPE &&
            tlv->getTypeValue() != AMQP_UINT_TYPE) {
        printf("AMQPUnwrapper::unwrapUInt");
        return 0;
    }

    if (sizeof(tlv->getValue()) == 0) {
        return 0;
    }
    if (sizeof(tlv->getValue()) == 1) {
        char *bytes = (char *)tlv->getValue();
        return (bytes[0] & 0xff);
    }
    char *bytes = tlv->getValue();
    int value = get_int(bytes, 0) & 0xffffffff;
    return value;
}

int AMQPUnwrapper::unwrapInt(TLVAMQP *tlv)
{
    if (tlv->getTypeValue() != AMQP_INT_TYPE &&
            tlv->getTypeValue() != AMQP_SMALL_INT_TYPE) {
        printf("AMQPUnwrapper::unwrapInt");
        return 0;
    }

    if (sizeof(tlv->getValue()) == 0) {
        return 0;
    }
    if (sizeof(tlv->getValue()) == 1) {
        char *bytes = (char *)tlv->getValue();
        return bytes[0];
    }
    char *bytes = tlv->getValue();
    int value = get_int(bytes, 0);
    return value;
}

unsigned long AMQPUnwrapper::unwrapULong(TLVAMQP *tlv)
{
    if (tlv->getTypeValue() != AMQP_ULONG_TYPE &&
            tlv->getTypeValue() != AMQP_SMALL_ULONG_TYPE &&
            tlv->getTypeValue() != AMQP_ULONG0_TYPE) {
        printf("AMQPUnwrapper::unwrapULong");
        return 0;
    }

    if (sizeof(tlv->getValue()) == 0) {
        return 0;
    }
    if (sizeof(tlv->getValue()) == 1) {
        char *bytes = (char *)tlv->getValue();
        return bytes[0] & 0xff;
    }
    char *bytes = tlv->getValue();
    long value = get_long(bytes, 0);
    return value;
}

long AMQPUnwrapper::unwrapLong(TLVAMQP *tlv)
{
    if (tlv->getTypeValue() != AMQP_LONG_TYPE &&
            tlv->getTypeValue() != AMQP_SMALL_LONG_TYPE) {
        printf("AMQPUnwrapper::unwrapLong");
        return 0;
    }

    if (sizeof(tlv->getValue()) == 0) {
        return 0;
    }
    if (sizeof(tlv->getValue()) == 1) {
        char *bytes = (char *)tlv->getValue();
        return (long)bytes[0];
    }
    char *bytes = tlv->getValue();
    long value = get_long(bytes, 0);
    return value;
}

bool AMQPUnwrapper::unwrapBool(TLVAMQP *tlv)
{
    if (tlv->getTypeValue() == AMQP_BOOLEAN_TYPE) {
        char *bytes = (char *)tlv->getValue();
        char byte = bytes[0];
        if (byte == 0) {
            return false;
        } else if (byte == 1) {
            return true;
        }
    } else if (tlv->getTypeValue() == AMQP_BOOLEAN_TRUE_TYPE) {
        return true;
    } else if (tlv->getTypeValue() == AMQP_BOOLEAN_FALSE_TYPE) {
        return false;
    }
    return false;
}

double AMQPUnwrapper::unwrapDouble(TLVAMQP *tlv)
{
    if (tlv->getTypeValue() != AMQP_DOUBLE_TYPE) {
        printf("AMQPUnwrapper::unwrapDouble");
        return 0;
    }
    char *bytes = tlv->getValue();
    double value = get_double(bytes, 0);
    return value;
}

float AMQPUnwrapper::unwrapFloat(TLVAMQP *tlv)
{
    if (tlv->getTypeValue() != AMQP_FLOAT_TYPE) {
        printf("AMQPUnwrapper::unwrapFloat");
        return 0;
    }
    char *bytes = tlv->getValue();
    float value = get_float(bytes, 0);
    return value;
}

time_t AMQPUnwrapper::unwrapTimestamp(TLVAMQP *tlv)
{
    time_t value;
    if (tlv->getTypeValue() != AMQP_TIMESTAMP_TYPE) {
        printf("AMQPUnwrapper::unwrapTimestamp");
        return value;
    }
    char *bytes = tlv->getValue();
    long value = get_long(bytes, 0);
    return std::chrono::system_clock::to_time_t(value);
}

AMQPDecimal *AMQPUnwrapper::unwrapDecimal(TLVAMQP *tlv)
{
    if (tlv->getTypeValue() != AMQP_DECIMAL32_TYPE &&
            tlv->getTypeValue() != AMQP_DECIMAL64_TYPE &&
            tlv->getTypeValue() != AMQP_DECIMAL128_TYPE) {
        printf("AMQPUnwrapper::unwrapDecimal");
        return NULL;
    }
    return new AMQPDecimal(tlv->getValue());
}

int AMQPUnwrapper::unwrapChar(TLVAMQP *tlv)
{
    if (tlv->getTypeValue() != AMQP_CHAR_TYPE) {
        printf("AMQPUnwrapper::unwrapChar");
        return 0;
    }
    char *bytes = tlv->getValue();
    int value = get_int(bytes, 0);
    return value;
}

String AMQPUnwrapper::unwrapString(TLVAMQP *tlv)
{
    if (tlv->getTypeValue() != AMQP_STRING8_TYPE &&
            tlv->getTypeValue() != AMQP_STRING32_TYPE) {
        printf("AMQPUnwrapper::unwrapString");
        return "";
    }
    char value[sizeof(tlv->getValue())];
    memcpy(value, tlv->getValue()[0], sizeof(tlv->getValue()));
    return value;
}

AMQPSymbol *AMQPUnwrapper::unwrapSymbol(TLVAMQP *tlv)
{
    if (tlv->getTypeValue() != AMQP_SYMBOL8_TYPE &&
            tlv->getTypeValue() != AMQP_SYMBOL32_TYPE) {
        printf("AMQPUnwrapper::unwrapSymbol");
        return NULL;
    }
    char value[sizeof(tlv->getValue())];
    memcpy(value, tlv->getValue()[0], sizeof(tlv->getValue()));
    return new AMQPSymbol(value);
}

unsigned char * AMQPUnwrapper::unwrapBinary(TLVAMQP *tlv)
{
    char * array;
    if (tlv->getTypeValue() != AMQP_BINARY8_TYPE &&
            tlv->getTypeValue() != AMQP_BINARY32_TYPE) {
        printf("AMQPUnwrapper::unwrapData");
        return aray;
    }
    return tlv->getValue();
}

QUuid AMQPUnwrapper::unwrapUUID(TLVAMQP *tlv)
{
    if (tlv->getTypeValue() != AMQP_UUID_TYPE) {
        printf("AMQPUnwrapper::unwrapUUID");
        return NULL;
    }
    return tlv->getValue();
}

list<JsonVariant *> AMQPUnwrapper::unwrapList(TLVAMQP *tlv)
{
    if (tlv->getTypeValue() != AMQP_LIST0_TYPE &&
            tlv->getTypeValue() != AMQP_LIST8_TYPE &&
            tlv->getTypeValue() != AMQP_LIST32_TYPE) {
        printf("AMQPUnwrapper::unwrapList");
        return list<JsonVariant *>();
    }
    list<JsonVariant *> result = list<JsonVariant *>();

    foreach (TLVAMQP *item, ((AMQPTLVList *)tlv)->getList()) {
        result.push_back(AMQPUnwrapper::unwrap(item));
    }
    return result;
}

map<JsonVariant *, JsonVariant *> AMQPUnwrapper::unwrapMap(TLVAMQP *tlv)
{
    if (tlv->getTypeValue() != AMQP_MAP8_TYPE &&
            tlv->getTypeValue() != AMQP_MAP32_TYPE) {
        printf("AMQPUnwrapper::unwrapMap");
        return map<JsonVariant *, JsonVariant *>();
    }

    map<JsonVariant *, JsonVariant *> result;
    AMQPTLVMap *mapTlv = (AMQPTLVMap *)tlv ;

    for (std::map<JsonVariant *, JsonVariant *>::iterator it = mapTlv.begin(); it != mapTlv.end(); ++it) {
      TLVAMQP *value = it->second;
      if (value != NULL) {
          result.insert(std::pair<JsonVariant *, JsonVariant *>(AMQPUnwrapper::unwrap(it->first), AMQPUnwrapper::unwrap(value)));
      }
    }
    return result;
}

list<JsonVariant *> AMQPUnwrapper::unwrapArray(TLVAMQP *tlv)
{
    list<JsonVariant *> result;
    if (tlv->getTypeValue() != AMQP_ARRAY8_TYPE &&
            tlv->getTypeValue() != AMQP_ARRAY32_TYPE) {
        printf("AMQPUnwrapper::unwrapArray");
        return result;
    }

    foreach (TLVAMQP *item, ((AMQPTLVArray *)tlv)->getElements()) {
        result.push_back(AMQPUnwrapper::unwrap(item));
    }
    return result;
}
