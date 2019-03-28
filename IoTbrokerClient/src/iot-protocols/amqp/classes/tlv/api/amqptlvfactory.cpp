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

#include "amqptlvfactory.h"
#include "iot-protocols/amqp/classes/constructors/amqpdescribedconstructor.h"
#include "iot-protocols/amqp/classes/tlv/fixed/amqptlvnull.h"
#include "iot-protocols/amqp/classes/tlv/fixed/amqptlvfixed.h"
#include "iot-protocols/amqp/classes/tlv/variable/amqptlvvariable.h"
#include "iot-protocols/amqp/classes/tlv/compound/amqptlvlist.h"
#include "iot-protocols/amqp/classes/tlv/compound/amqptlvmap.h"
#include "iot-protocols/amqp/classes/tlv/array/amqptlvarray.h"

TLVAMQP *AMQPTLVFactory::tlvByData(unsigned char *data, int *i)
{
    AMQPSimpleConstructor *constructor = AMQPTLVFactory::constructorByData(data, i);
    TLVAMQP *tlv = AMQPTLVFactory::elementByConstructor(constructor, data, i);
    return tlv;
}

TLVAMQP *AMQPTLVFactory::elementByConstructor(AMQPSimpleConstructor *constructor, unsigned char *data, int *i)
{
    TLVAMQP *tlv = NULL;
    AMQPType *type = constructor->getType();

    switch (type->getValue()) {
        case AMQP_NULL_TYPE:
        {
            tlv = new AMQPTLVNull();
        } break;
        case AMQP_BOOLEAN_TRUE_TYPE:
        case AMQP_BOOLEAN_FALSE_TYPE:
        case AMQP_UINT0_TYPE:
        case AMQP_ULONG0_TYPE:
        {
            unsigned char * array = malloc(sizeof(char));
            tlv = new AMQPTLVFixed(type, array);
        } break;
        case AMQP_BOOLEAN_TYPE:
        case AMQP_UBYTE_TYPE:
        case AMQP_BYTE_TYPE:
        case AMQP_SMALL_UINT_TYPE:
        case AMQP_SMALL_ULONG_TYPE:
        case AMQP_SMALL_INT_TYPE:
        case AMQP_SMALL_LONG_TYPE:
        {
            tlv = new AMQPTLVFixed(type, data[*i]);
        } break;
        case AMQP_SHORT_TYPE:
        case AMQP_USHORT_TYPE:
        {
            unsigned char * bytes = malloc(sizeof(short));
            add_short(&bytes[0], get_short(data, *i));
            *i += 2;
            tlv = new AMQPTLVFixed(type, bytes);
        } break;
        case AMQP_UINT_TYPE:
        case AMQP_INT_TYPE:
        case AMQP_FLOAT_TYPE:
        case AMQP_DECIMAL32_TYPE:
        case AMQP_CHAR_TYPE:
        {
            unsigned char * bytes = malloc(sizeof(int));
            add_int(&bytes[0], get_int(data, *i));
            *i += 4;
            tlv = new AMQPTLVFixed(type, bytes);
        } break;
        case AMQP_ULONG_TYPE:
        case AMQP_LONG_TYPE:
        case AMQP_DECIMAL64_TYPE:
        case AMQP_DOUBLE_TYPE:
        case AMQP_TIMESTAMP_TYPE:
        {
            unsigned char * bytes = malloc(sizeof(long));
            add_long(&bytes[0], get_long(data, *i));
            *i += 4;
            tlv = new AMQPTLVFixed(type, bytes);
        } break;
        case AMQP_DECIMAL128_TYPE:
        case AMQP_UUID_TYPE:
        {
            unsigned char * bytes = malloc(16 * sizeof(char));
            memcpy(&bytes[0], &data[*i], 16);
            *i += 16;
            tlv = new AMQPTLVFixed(type, bytes);
        } break;
        case AMQP_BINARY8_TYPE:
        case AMQP_STRING8_TYPE:
        case AMQP_SYMBOL8_TYPE:
        {
            int var8Length = data[(*i)++] & 0xff;
            unsigned char * bytes = malloc(var8Length * sizeof(char));
            memcpy(&bytes[0], get_string(&data[i], var8Length), var8Length);
            *i += var8Length
            tlv = new AMQPTLVVariable(type, bytes);
        } break;
        case AMQP_BINARY32_TYPE:
        case AMQP_STRING32_TYPE:
        case AMQP_SYMBOL32_TYPE:
        {
            int var32Length = get_int(data, *i);
            *i += 4;
            unsigned char * bytes = malloc(var32Length * sizeof(char));
            memcpy(&bytes[0], get_string(&data[i], var32Length), var32Length);
            *i += var32Length;
            tlv = new AMQPTLVVariable(type, bytes);
        } break;
        case AMQP_LIST0_TYPE:
        {
            tlv = new AMQPTLVList();
        } break;
        case AMQP_LIST8_TYPE:
        {
            *i++;
            int list8count = (data[(*i)++] & 0xff);
            list<TLVAMQP *> list8values;
            for (int j = 0; j < list8count; j++) {
                list8values.push_back(AMQPTLVFactory::tlvByData(data, i));
            }
            tlv = new AMQPTLVList(type, list8values);
        } break;
        case AMQP_LIST32_TYPE:
        {
            *i += 4;
            int list32count = get_int(data, *i);
            *i += 4;
            list<TLVAMQP *> list32values;
            for (int j = 0; j < list32count; j++) {
                list32values.push_back(AMQPTLVFactory::tlvByData(data, i));
            }
            tlv = new AMQPTLVList(type, list32values);
        } break;
        case AMQP_MAP8_TYPE:
        {
            int map8size = (data[(*i)++] & 0xff);
            (*i)++; // map8count
            int stop8 = (int)(*i + map8size - 1);
            AMQPTLVMap *map8 = new AMQPTLVMap();

            while (*i < stop8) {
                map8->putElement(AMQPTLVFactory::tlvByData(data, i), AMQPTLVFactory::tlvByData(data, i));
            }
            tlv = map8;
        } break;
        case AMQP_MAP32_TYPE:
        {
            int map32size = get_int(data, *i);
            *i += 4;
            *i += 4; // map32count
            int stop32 = (int)(*i + map32size - 4);

            AMQPTLVMap *map32 = new AMQPTLVMap();

            while (*i < stop32) {
                map32->putElement(AMQPTLVFactory::tlvByData(data, i), AMQPTLVFactory::tlvByData(data, i));
            }
            tlv = map32;
        } break;
        case AMQP_ARRAY8_TYPE:
        {
            list<TLVAMQP *> array8 = list<TLVAMQP *>();
            (*i)++; // array8size
            int array8count = (data[(*i)++)] & 0xff);
            AMQPSimpleConstructor *array8Constructor = AMQPTLVFactory::constructorByData(data, i);
            for (int j = 0; j < array8count; j++) {
                array8.push_back(AMQPTLVFactory::elementByConstructor(array8Constructor, data, i));
            }
            tlv = new AMQPTLVList(type, array8);
        } break;
        case AMQP_ARRAY32_TYPE:
        {
            list<TLVAMQP *> array32 = list<TLVAMQP *>();
            (*i) += 4; // array32size
            int array32count = get_int(data, *i);
            (*i) += 4;
            AMQPSimpleConstructor *array32Constructor = AMQPTLVFactory::constructorByData(data, i);
            for (int j = 0; j < array32count; j++) {
                array32.append(AMQPTLVFactory::elementByConstructor(array32Constructor, data, i));
            }
            tlv = new AMQPTLVList(type, array32);
        } break;
    }

    if ((AMQPDescribedConstructor *) constructor != NULL) {
        tlv->setConstructor(constructor);
    }

    return tlv;
}

AMQPSimpleConstructor *AMQPTLVFactory::constructorByData(unsigned char *data, int * i)
{
    AMQPType *type = new AMQPType(AMQP_NULL_TYPE);
    AMQPSimpleConstructor *constructor = NULL;

    int codeByte = data[(*i)++];

    if (codeByte == 0) {
        TLVAMQP *descriptor = AMQPTLVFactory::tlvByData(data, i);
        type = new AMQPType(data[(*i)++] & 0xff);
        constructor = new AMQPDescribedConstructor(type, descriptor);
    } else {
        type = new AMQPType(codeByte & 0xff);
        constructor = new AMQPSimpleConstructor(type);
    }

    return constructor;
}
