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
    return value->as<bool>();
}

JsonVariant *AMQPSimpleType::boolToVariant(bool value)
{
    JsonVariant *valueVariant;
    valueVariant->set(value);
    return valueVariant;
}

unsigned short AMQPSimpleType::variantToUByte(JsonVariant *value)
{
    return value->as<unsigned short>();
}

JsonVariant *AMQPSimpleType::UByteToVariant(short value)
{
    JsonVariant *valueVariant;
    valueVariant->set(value);
    return valueVariant;
}

unsigned short AMQPSimpleType::variantToUShort(JsonVariant *value)
{
    return value->as<unsigned short>();
}

JsonVariant *AMQPSimpleType::UShortToVariant(unsigned short value)
{
    JsonVariant *valueVariant;
    valueVariant->set(value);
    return valueVariant;
}

unsigned int AMQPSimpleType::variantToUInt(JsonVariant *value)
{
    return value->as<unsigned int>();
}

JsonVariant *AMQPSimpleType::UIntToVariant(unsigned int value)
{
    JsonVariant *valueVariant;
    valueVariant->set(value);
    return valueVariant;
}

unsigned long AMQPSimpleType::variantToULong(JsonVariant *value)
{
    return value->as<unsigned long>();
}

JsonVariant *AMQPSimpleType::ULongToVariant(unsigned long value)
{
    JsonVariant *valueVariant;
    valueVariant->set(value);
    return valueVariant;
}

char AMQPSimpleType::variantToChar(JsonVariant *value)
{
    return value->as<char>();
}

JsonVariant *AMQPSimpleType::charToVariant(char value)
{
    JsonVariant *valueVariant;
    valueVariant->set(value);
    return valueVariant;
}

short AMQPSimpleType::variantToShort(JsonVariant *value)
{
    return value->as<short>();
}

JsonVariant *AMQPSimpleType::shortToVariant(short value)
{
    JsonVariant *valueVariant;
    valueVariant->set(value);
    return valueVariant;
}

int AMQPSimpleType::variantToInt(JsonVariant *value)
{
    return value->as<int>();
}

JsonVariant *AMQPSimpleType::intToVariant(int value)
{
    JsonVariant *valueVariant;
    valueVariant->set(value);
    return valueVariant;
}

long AMQPSimpleType::variantToLong(JsonVariant *value)
{
    return value->as<long>();
}

JsonVariant *AMQPSimpleType::longToVariant(long value)
{
    JsonVariant *valueVariant;
    valueVariant->set(value);
    return valueVariant;
}

float AMQPSimpleType::variantToFloat(JsonVariant *value)
{
    return value->as<float>();
}

JsonVariant *AMQPSimpleType::floatToVariant(float value)
{
    JsonVariant *valueVariant;
    valueVariant->set(value);
    return valueVariant;
}

double AMQPSimpleType::variantToDouble(JsonVariant *value)
{
    return value->as<double>();
}

JsonVariant *AMQPSimpleType::doubleToVariant(double value)
{
    JsonVariant *valueVariant;
    valueVariant->set(value);
    return valueVariant;
}

time_t AMQPSimpleType::variantToTimestamp(JsonVariant *value)
{
    return value->as<time_t>();
}

JsonVariant *AMQPSimpleType::timestampToVariant(time_t value)
{
    JsonVariant *valueVariant;
    valueVariant->set(value);
    return valueVariant;
}

String AMQPSimpleType::variantToUuid(JsonVariant *value)
{
    return value->as<String>();
}

JsonVariant *AMQPSimpleType::uuidToVariant(String value)
{
    JsonVariant *valueVariant;
    valueVariant->set(value);
    return valueVariant;
}

const char * AMQPSimpleType::variantToBinary(JsonVariant *value)
{
    return value->as<const char *>();
}

JsonVariant *AMQPSimpleType::binaryToVariant(char * value)
{
    JsonVariant *valueVariant;
    valueVariant->set(value);
    return valueVariant;
}

String AMQPSimpleType::variantToString(JsonVariant *value)
{
    return value->as<String>();
}

JsonVariant *AMQPSimpleType::stringToVariant(String value)
{
    JsonVariant *valueVariant;
    valueVariant->set(value);
    return valueVariant;
}

AMQPSymbol *AMQPSimpleType::variantToSymbol(JsonVariant *value)
{
    String get = value->as<String>();
    return new AMQPSymbol(get);
}

JsonVariant *AMQPSimpleType::symbolToVariant(AMQPSymbol *value)
{
    JsonVariant *valueVariant;
    valueVariant->set(value);
    return valueVariant;
}

AMQPDecimal *AMQPSimpleType::variantToDecimal(JsonVariant *value)
{
    short get = value->as<short>();
    return new AMQPDecimal(get);
}

JsonVariant *AMQPSimpleType::decimalToVariant(AMQPDecimal *value)
{
    JsonVariant *valueVariant;
    valueVariant->set(value);
    return valueVariant;
}
