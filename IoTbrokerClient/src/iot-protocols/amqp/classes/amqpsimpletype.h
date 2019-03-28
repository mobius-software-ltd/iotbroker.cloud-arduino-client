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

#ifndef AMQPSIMPLETYPE_H
#define AMQPSIMPLETYPE_H

//#include <ArduinoSTL.h>
#include <ArduinoJson.h>
#include <ctime>
#include "iot-protocols/amqp/classes/enums/amqptype.h"
#include "iot-protocols/amqp/classes/wrappers/amqpsymbol.h"
#include "iot-protocols/amqp/classes/wrappers/amqpdecimal.h"

class AMQPSimpleType
{

private:

    AMQPTypes type;
    JsonVariant *object;

    static AMQPSimpleType *simpleTypeFromVariant(JsonVariant *value);
    static JsonVariant *wrapSimpleTypeValue(JsonVariant *value, AMQPTypes type);

public:
    AMQPSimpleType();
    AMQPSimpleType(AMQPTypes type, JsonVariant *object);

    AMQPTypes getType() const;
    void setType(const AMQPTypes &value);

    JsonVariant *getObject() const;
    void setObject(JsonVariant *value);

    static bool variantToBool(JsonVariant *value);
    static JsonVariant *boolToVariant(bool value);

    static short variantToUByte(JsonVariant *value);
    static JsonVariant *UByteToVariant(short value);

    static unsigned short variantToUShort(JsonVariant *value);
    static JsonVariant *UShortToVariant(unsigned short value);

    static unsigned int variantToUInt(JsonVariant *value);
    static JsonVariant *UIntToVariant(unsigned int value);

    static unsigned long variantToULong(JsonVariant *value);
    static JsonVariant *ULongToVariant(unsigned long value);

    static char variantToChar(JsonVariant *value);
    static JsonVariant *charToVariant(char value);

    static short variantToShort(JsonVariant *value);
    static JsonVariant *shortToVariant(short value);

    static int variantToInt(JsonVariant *value);
    static JsonVariant *intToVariant(int value);

    static long variantToLong(JsonVariant *value);
    static JsonVariant *longToVariant(long value);

    static float variantToFloat(JsonVariant *value);
    static JsonVariant *floatToVariant(float value);

    static double variantToDouble(JsonVariant *value);
    static JsonVariant *doubleToVariant(double value);

    static time_t variantToTimestamp(JsonVariant *value);
    static JsonVariant *timestampToVariant(time_t value);

    static String variantToUuid(JsonVariant *value);
    static JsonVariant *uuidToVariant(String value);

    static unsigned char * variantToBinary(JsonVariant *value);
    static JsonVariant *binaryToVariant(unsigned char * value);

    static String variantToString(JsonVariant *value);
    static JsonVariant *stringToVariant(String value);

    static AMQPSymbol *variantToSymbol(JsonVariant *value);
    static JsonVariant *symbolToVariant(AMQPSymbol *value);

    static AMQPDecimal *variantToDecimal(JsonVariant *value);
    static JsonVariant *decimalToVariant(AMQPDecimal *value);

};

#endif // AMQPSIMPLETYPE_H
