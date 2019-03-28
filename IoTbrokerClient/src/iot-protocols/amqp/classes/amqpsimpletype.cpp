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

#include "amqpsimpletype.h"

AMQPSimpleType::AMQPSimpleType()
{

}

AMQPSimpleType::AMQPSimpleType(AMQPTypes type, JsonVariant *object)
{
    this->type = type;
    this->object = object;
}

AMQPTypes AMQPSimpleType::getType() const
{
    return type;
}

void AMQPSimpleType::setType(const AMQPTypes &value)
{
    type = value;
}

JsonVariant *AMQPSimpleType::getObject() const
{
    return object;
}

void AMQPSimpleType::setObject(JsonVariant *value)
{
    object = value;
}

bool AMQPSimpleType::variantToBool(JsonVariant *value)
{
    AMQPSimpleType *type = simpleTypeFromVariant(value);
    return type->getObject()->as<bool>();
}

JsonVariant *AMQPSimpleType::boolToVariant(bool value)
{
    JsonVariant valueVariant;
    valueVariant.set(value);
    return wrapSimpleTypeValue(valueVariant, AMQP_BOOLEAN_TYPE);
}

short AMQPSimpleType::variantToUByte(JsonVariant *value)
{
    AMQPSimpleType *type = simpleTypeFromVariant(value);
    return type->getObject()->as<short>();
}

JsonVariant *AMQPSimpleType::UByteToVariant(short value)
{
    JsonVariant valueVariant;
    valueVariant.set(value);
    return wrapSimpleTypeValue(valueVariant, AMQP_UBYTE_TYPE);
}

unsigned short AMQPSimpleType::variantToUShort(JsonVariant *value)
{
    AMQPSimpleType *type = simpleTypeFromVariant(value);
    return type->getObject()->as<unsigned short>();
}

JsonVariant *AMQPSimpleType::UShortToVariant(unsigned short value)
{
    JsonVariant valueVariant;
    valueVariant.set(value);
    return wrapSimpleTypeValue(valueVariant, AMQP_USHORT_TYPE);
}

unsigned int AMQPSimpleType::variantToUInt(JsonVariant *value)
{
    AMQPSimpleType *type = simpleTypeFromVariant(value);
    return type->getObject()->as<unsigned int>();
}

JsonVariant *AMQPSimpleType::UIntToVariant(unsigned int value)
{
    JsonVariant valueVariant;
    valueVariant.set(value);
    return wrapSimpleTypeValue(valueVariant, AMQP_UINT0_TYPE);
}

unsigned long AMQPSimpleType::variantToULong(JsonVariant *value)
{
    AMQPSimpleType *type = simpleTypeFromVariant(value);
    return type->getObject()->as<unsigned long>();
}

JsonVariant *AMQPSimpleType::ULongToVariant(unsigned long value)
{
    JsonVariant valueVariant;
    valueVariant.set(value);
    return wrapSimpleTypeValue(valueVariant, AMQP_ULONG_TYPE);
}

char AMQPSimpleType::variantToChar(JsonVariant *value)
{
    AMQPSimpleType *type = simpleTypeFromVariant(value);
    return type->getObject()->as<char>();
}

JsonVariant *AMQPSimpleType::charToVariant(char value)
{
    JsonVariant valueVariant;
    valueVariant.set(value);
    return wrapSimpleTypeValue(valueVariant, AMQP_CHAR_TYPE);
}

short AMQPSimpleType::variantToShort(JsonVariant *value)
{
    AMQPSimpleType *type = simpleTypeFromVariant(value);
    return type->getObject()->as<short>();
}

JsonVariant *AMQPSimpleType::shortToVariant(short value)
{
    JsonVariant valueVariant;
    valueVariant.set(value);
    return wrapSimpleTypeValue(valueVariant, AMQP_SHORT_TYPE);
}

int AMQPSimpleType::variantToInt(JsonVariant *value)
{
    AMQPSimpleType *type = simpleTypeFromVariant(value);
    return type->getObject()->as<int>();
}

JsonVariant *AMQPSimpleType::intToVariant(int value)
{
    JsonVariant valueVariant;
    valueVariant.set(value);
    return wrapSimpleTypeValue(valueVariant, AMQP_INT_TYPE);
}

long AMQPSimpleType::variantToLong(JsonVariant *value)
{
    AMQPSimpleType *type = simpleTypeFromVariant(value);
    return type->getObject()->as<long>();
}

JsonVariant *AMQPSimpleType::longToVariant(long value)
{
    JsonVariant valueVariant;
    valueVariant.set(value);
    return wrapSimpleTypeValue(valueVariant, AMQP_LONG_TYPE);
}

float AMQPSimpleType::variantToFloat(JsonVariant *value)
{
    AMQPSimpleType *type = simpleTypeFromVariant(value);
    return type->getObject()->as<float>();
}

JsonVariant *AMQPSimpleType::floatToVariant(float value)
{
    JsonVariant valueVariant;
    valueVariant.set(value);
    return wrapSimpleTypeValue(valueVariant, AMQP_FLOAT_TYPE);
}

double AMQPSimpleType::variantToDouble(JsonVariant *value)
{
    AMQPSimpleType *type = simpleTypeFromVariant(value);
    return type->getObject()->as<double>();
}

JsonVariant *AMQPSimpleType::doubleToVariant(double value)
{
    JsonVariant valueVariant;
    valueVariant.set(value);
    return wrapSimpleTypeValue(valueVariant, AMQP_DOUBLE_TYPE);
}

time_t AMQPSimpleType::variantToTimestamp(JsonVariant *value)
{
    AMQPSimpleType *type = simpleTypeFromVariant(value);
    return type->getObject()->as<time_t>();
}

JsonVariant *AMQPSimpleType::timestampToVariant(time_t value)
{
    JsonVariant valueVariant;
    valueVariant.set(value);
    return wrapSimpleTypeValue(valueVariant, AMQP_TIMESTAMP_TYPE);
}

String AMQPSimpleType::variantToUuid(JsonVariant *value)
{
    AMQPSimpleType *type = simpleTypeFromVariant(value);
    return type->getObject()->as<String>();
}

JsonVariant *AMQPSimpleType::uuidToVariant(String value)
{
    JsonVariant valueVariant;
    valueVariant.set(value);
    return wrapSimpleTypeValue(valueVariant, AMQP_UUID_TYPE);
}

unsigned char * AMQPSimpleType::variantToBinary(JsonVariant *value)
{
    AMQPSimpleType *type = simpleTypeFromVariant(value);
    return type->getObject()->as<unsigned char *>();
}

JsonVariant *AMQPSimpleType::binaryToVariant(unsigned char * value)
{
    JsonVariant valueVariant;
    valueVariant.set(value);
    return wrapSimpleTypeValue(valueVariant, AMQP_BINARY8_TYPE);
}

String AMQPSimpleType::variantToString(JsonVariant *value)
{
    AMQPSimpleType *type = simpleTypeFromVariant(value);
    return type->getObject()->as<String>();
}

JsonVariant *AMQPSimpleType::stringToVariant(String value)
{
    JsonVariant valueVariant;
    valueVariant.set(value);
    return wrapSimpleTypeValue(valueVariant, AMQP_STRING8_TYPE);
}

AMQPSymbol *AMQPSimpleType::variantToSymbol(JsonVariant *value)
{
    AMQPSimpleType *type = simpleTypeFromVariant(value);
    if (type->getType() == AMQP_SYMBOL8_TYPE || type->getType() == AMQP_SYMBOL32_TYPE) {
        String value = type->getObject()->as<String>();
        return new AMQPSymbol(value);
    }
    return new AMQPSymbol();
}

JsonVariant *AMQPSimpleType::symbolToVariant(AMQPSymbol *value)
{
    JsonVariant valueVariant;
    valueVariant.set(value);
    return wrapSimpleTypeValue(valueVariant, AMQP_SYMBOL8_TYPE);
}

AMQPDecimal *AMQPSimpleType::variantToDecimal(JsonVariant *value)
{
    AMQPSimpleType *type = simpleTypeFromVariant(value);
    if (type->getType() == AMQP_DECIMAL32_TYPE || type->getType() == AMQP_DECIMAL64_TYPE || type->getType() == AMQP_DECIMAL128_TYPE) {
        short value = type->getObject()->as<short>();
        return new AMQPDecimal(value);
    }
    return new AMQPDecimal();
}

JsonVariant *AMQPSimpleType::decimalToVariant(AMQPDecimal *value)
{
    JsonVariant valueVariant;
    valueVariant.set(value);
    return wrapSimpleTypeValue(valueVariant, AMQP_DECIMAL32_TYPE);
}

// private methods

AMQPSimpleType *AMQPSimpleType::simpleTypeFromVariant(JsonVariant *value)
{
    AMQPSimpleType *type = value.as<AMQPSimpleType>();
    return type;
}

JsonVariant *AMQPSimpleType::wrapSimpleTypeValue(JsonVariant *value, AMQPTypes type)
{
    AMQPSimpleType *sType = new AMQPSimpleType(type, value);
    JsonVariant valueVariant;
    valueVariant.set(value);
    return valueVariant;
}
