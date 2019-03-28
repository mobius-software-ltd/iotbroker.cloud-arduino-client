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

#ifndef AMQPUNWRAPPER_H
#define AMQPUNWRAPPER_H

#include "iot-protocols/amqp/classes/tlv/api/tlvamqp.h"
#include "iot-protocols/amqp/classes/wrappers/amqpdecimal.h"
#include "iot-protocols/amqp/classes/wrappers/amqpsymbol.h"
#include "iot-protocols/amqp/classes/tlv/array/amqptlvarray.h"
#include "iot-protocols/amqp/classes/tlv/compound/amqptlvlist.h"
#include "iot-protocols/amqp/classes/tlv/compound/amqptlvmap.h"

//#include <chrono>
#include <ctime>
#include <StandardCplusplus.h>
#include <map>
#include <list>

class AMQPUnwrapper
{
public:

    static JsonVariant *unwrap(TLVAMQP *value);

    static short unwrapUByte(TLVAMQP *tlv);
    static char unwrapByte(TLVAMQP *tlv);
    static int unwrapUShort(TLVAMQP *tlv);
    static short unwrapShort(TLVAMQP *tlv);
    static long unwrapUInt(TLVAMQP *tlv);
    static int unwrapInt(TLVAMQP *tlv);
    static unsigned long unwrapULong(TLVAMQP *tlv);
    static long unwrapLong(TLVAMQP *tlv);
    static bool unwrapBool(TLVAMQP *tlv);
    static double unwrapDouble(TLVAMQP *tlv);
    static float unwrapFloat(TLVAMQP *tlv);
    static time_t unwrapTimestamp(TLVAMQP *tlv);
    static AMQPDecimal *unwrapDecimal(TLVAMQP *tlv);
    static int unwrapChar(TLVAMQP *tlv);
    static String unwrapString(TLVAMQP *tlv);
    static AMQPSymbol *unwrapSymbol(TLVAMQP *tlv);
    static unsigned char * unwrapBinary(TLVAMQP *tlv);
    static String unwrapUUID(TLVAMQP *tlv);
    static std::list<JsonVariant *> unwrapList(TLVAMQP *tlv);
    static std::map<JsonVariant *, JsonVariant *> unwrapMap(TLVAMQP *tlv);
    static std::list<JsonVariant *> unwrapArray(TLVAMQP *tlv);
};

#endif // AMQPUNWRAPPER_H
