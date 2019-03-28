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

#include "amqptype.h"

AMQPType::AMQPType()
{
    this->map = std::map<int, String>();
    this->map.insert(std::pair<int, String>(AMQP_SOURCE_TYPE, AMQP_SOURCE_TYPE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_TARGET_TYPE, AMQP_TARGET_TYPE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_ERROR_TYPE, AMQP_ERROR_TYPE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_NULL_TYPE, AMQP_NULL_TYPE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_BOOLEAN_TYPE, AMQP_BOOLEAN_TYPE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_BOOLEAN_TRUE_TYPE, AMQP_BOOLEAN_TRUE_TYPE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_BOOLEAN_FALSE_TYPE, AMQP_BOOLEAN_FALSE_TYPE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_UBYTE_TYPE, AMQP_UBYTE_TYPE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_USHORT_TYPE, AMQP_USHORT_TYPE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_UINT_TYPE, AMQP_UINT_TYPE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_SMALL_UINT_TYPE, AMQP_SMALL_UINT_TYPE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_UINT0_TYPE, AMQP_UINT0_TYPE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_ULONG_TYPE, AMQP_ULONG_TYPE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_SMALL_ULONG_TYPE, AMQP_SMALL_ULONG_TYPE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_ULONG0_TYPE, AMQP_ULONG0_TYPE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_BYTE_TYPE, AMQP_BYTE_TYPE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_SHORT_TYPE, AMQP_SHORT_TYPE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_INT_TYPE, AMQP_INT_TYPE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_SMALL_INT_TYPE, AMQP_SMALL_INT_TYPE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_LONG_TYPE, AMQP_LONG_TYPE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_SMALL_LONG_TYPE, AMQP_SMALL_LONG_TYPE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_FLOAT_TYPE, AMQP_FLOAT_TYPE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_DOUBLE_TYPE, AMQP_DOUBLE_TYPE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_DECIMAL32_TYPE, AMQP_DECIMAL32_TYPE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_DECIMAL64_TYPE, AMQP_DECIMAL64_TYPE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_DECIMAL128_TYPE, AMQP_DECIMAL128_TYPE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_CHAR_TYPE, AMQP_CHAR_TYPE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_TIMESTAMP_TYPE, AMQP_TIMESTAMP_TYPE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_UUID_TYPE, AMQP_UUID_TYPE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_BINARY8_TYPE, AMQP_BINARY8_TYPE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_BINARY32_TYPE, AMQP_BINARY32_TYPE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_STRING8_TYPE, AMQP_STRING8_TYPE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_STRING32_TYPE, AMQP_STRING32_TYPE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_SYMBOL8_TYPE, AMQP_SYMBOL8_TYPE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_SYMBOL32_TYPE, AMQP_SYMBOL32_TYPE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_LIST0_TYPE, AMQP_LIST0_TYPE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_LIST8_TYPE, AMQP_LIST8_TYPE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_LIST32_TYPE, AMQP_LIST32_TYPE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_MAP8_TYPE, AMQP_MAP8_TYPE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_MAP32_TYPE, AMQP_MAP32_TYPE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_ARRAY8_TYPE, AMQP_ARRAY8_TYPE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_ARRAY32_TYPE, AMQP_ARRAY32_TYPE_STRING));
}

AMQPType::AMQPType(int value) : AMQPType()
{
    this->value = value;
}

int AMQPType::getValue()
{
    return this->value;
}

String AMQPType::getName()
{
    return EnumObject::getName(this->value);
}
