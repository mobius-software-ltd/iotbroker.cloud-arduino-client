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

#ifndef AMQPTYPE_H
#define AMQPTYPE_H

#include <map>
#include "iot-protocols/amqp/classes/enums/enumobject.h"

enum AMQPTypes
{
    AMQP_SOURCE_TYPE        = 0x28,
    AMQP_TARGET_TYPE        = 0x29,
    AMQP_ERROR_TYPE         = 0x1D,
    AMQP_NULL_TYPE          = 0x40,
    AMQP_BOOLEAN_TYPE       = 0x56,
    AMQP_BOOLEAN_TRUE_TYPE  = 0x41,
    AMQP_BOOLEAN_FALSE_TYPE = 0x42,
    AMQP_UBYTE_TYPE         = 0x50,
    AMQP_USHORT_TYPE        = 0x60,
    AMQP_UINT_TYPE          = 0x70,
    AMQP_SMALL_UINT_TYPE    = 0x52,
    AMQP_UINT0_TYPE         = 0x43,
    AMQP_ULONG_TYPE         = 0x80,
    AMQP_SMALL_ULONG_TYPE   = 0x53,
    AMQP_ULONG0_TYPE        = 0x44,
    AMQP_BYTE_TYPE          = 0x51,
    AMQP_SHORT_TYPE         = 0x61,
    AMQP_INT_TYPE           = 0x71,
    AMQP_SMALL_INT_TYPE     = 0x54,
    AMQP_LONG_TYPE          = 0x81,
    AMQP_SMALL_LONG_TYPE    = 0x55,
    AMQP_FLOAT_TYPE         = 0x72,
    AMQP_DOUBLE_TYPE        = 0x82,
    AMQP_DECIMAL32_TYPE     = 0x74,
    AMQP_DECIMAL64_TYPE     = 0x84,
    AMQP_DECIMAL128_TYPE    = 0x94,
    AMQP_CHAR_TYPE          = 0x73,
    AMQP_TIMESTAMP_TYPE     = 0x83,
    AMQP_UUID_TYPE          = 0x98,
    AMQP_BINARY8_TYPE       = 0xA0,
    AMQP_BINARY32_TYPE      = 0xB0,
    AMQP_STRING8_TYPE       = 0xA1,
    AMQP_STRING32_TYPE      = 0xB1,
    AMQP_SYMBOL8_TYPE       = 0xA3,
    AMQP_SYMBOL32_TYPE      = 0xB3,
    AMQP_LIST0_TYPE         = 0x45,
    AMQP_LIST8_TYPE         = 0xC0,
    AMQP_LIST32_TYPE        = 0xD0,
    AMQP_MAP8_TYPE          = 0xC1,
    AMQP_MAP32_TYPE         = 0xD1,
    AMQP_ARRAY8_TYPE        = 0xE0,
    AMQP_ARRAY32_TYPE       = 0xF0,
};

static String const AMQP_SOURCE_TYPE_STRING        = "Source";
static String const AMQP_TARGET_TYPE_STRING        = "Target";
static String const AMQP_ERROR_TYPE_STRING         = "Error";
static String const AMQP_NULL_TYPE_STRING          = "Null";
static String const AMQP_BOOLEAN_TYPE_STRING       = "Boolean";
static String const AMQP_BOOLEAN_TRUE_TYPE_STRING  = "True";
static String const AMQP_BOOLEAN_FALSE_TYPE_STRING = "False";
static String const AMQP_UBYTE_TYPE_STRING         = "UByte";
static String const AMQP_USHORT_TYPE_STRING        = "UShort";
static String const AMQP_UINT_TYPE_STRING          = "UInt";
static String const AMQP_SMALL_UINT_TYPE_STRING    = "SmallUint";
static String const AMQP_UINT0_TYPE_STRING         = "UInt0";
static String const AMQP_ULONG_TYPE_STRING         = "ULong";
static String const AMQP_SMALL_ULONG_TYPE_STRING   = "SmallULong";
static String const AMQP_ULONG0_TYPE_STRING        = "ULong0";
static String const AMQP_BYTE_TYPE_STRING          = "Byte";
static String const AMQP_SHORT_TYPE_STRING         = "Short";
static String const AMQP_INT_TYPE_STRING           = "Int";
static String const AMQP_SMALL_INT_TYPE_STRING     = "SmallInt";
static String const AMQP_LONG_TYPE_STRING          = "Long";
static String const AMQP_SMALL_LONG_TYPE_STRING    = "SmallLong";
static String const AMQP_FLOAT_TYPE_STRING         = "Float";
static String const AMQP_DOUBLE_TYPE_STRING        = "Double";
static String const AMQP_DECIMAL32_TYPE_STRING     = "Decimal32";
static String const AMQP_DECIMAL64_TYPE_STRING     = "Decimal64";
static String const AMQP_DECIMAL128_TYPE_STRING    = "Decimal128";
static String const AMQP_CHAR_TYPE_STRING          = "Chart";
static String const AMQP_TIMESTAMP_TYPE_STRING     = "Timestamp";
static String const AMQP_UUID_TYPE_STRING          = "UUID";
static String const AMQP_BINARY8_TYPE_STRING       = "Binary8 ";
static String const AMQP_BINARY32_TYPE_STRING      = "Binary32";
static String const AMQP_STRING8_TYPE_STRING       = "String8";
static String const AMQP_STRING32_TYPE_STRING      = "String32";
static String const AMQP_SYMBOL8_TYPE_STRING       = "Symbol8";
static String const AMQP_SYMBOL32_TYPE_STRING      = "Symbol32";
static String const AMQP_LIST0_TYPE_STRING         = "List0";
static String const AMQP_LIST8_TYPE_STRING         = "List8";
static String const AMQP_LIST32_TYPE_STRING        = "List32";
static String const AMQP_MAP8_TYPE_STRING          = "Map8";
static String const AMQP_MAP32_TYPE_STRING         = "Map32";
static String const AMQP_ARRAY8_TYPE_STRING        = "Array8";
static String const AMQP_ARRAY32_TYPE_STRING       = "Array32";

class AMQPType : public EnumObject
{
private:

    int value;

public:
    AMQPType();
    AMQPType(int value);

    int getValue();
    String getName();
};

#endif // AMQPTYPE_H
