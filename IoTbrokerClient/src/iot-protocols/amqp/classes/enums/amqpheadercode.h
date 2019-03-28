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

#ifndef AMQPHEADERCODE_H
#define AMQPHEADERCODE_H

#include <map>
#include "iot-protocols/amqp/classes/enums/enumobject.h"

enum AMQPHeaderCodes
{
    AMQP_PROTOCOL_HEADER_CODE       = 0x08,
    AMQP_OPEN_HEADER_CODE           = 0x10,
    AMQP_BEGIN_HEADER_CODE          = 0x11,
    AMQP_ATTACH_HEADER_CODE         = 0x12,
    AMQP_FLOW_HEADER_CODE           = 0x13,
    AMQP_TRANSFER_HEADER_CODE       = 0x14,
    AMQP_DISPOSITION_HEADER_CODE    = 0x15,
    AMQP_DETACH_HEADER_CODE         = 0x16,
    AMQP_END_HEADER_CODE            = 0x17,
    AMQP_CLOSE_HEADER_CODE          = 0x18,
    AMQP_MECHANISMS_HEADER_CODE     = 0x40,
    AMQP_INIT_HEADER_CODE           = 0x41,
    AMQP_CHALLENGE_HEADER_CODE      = 0x42,
    AMQP_RESPONSE_HEADER_CODE       = 0x43,
    AMQP_OUTCOME_HEADER_CODE        = 0x44,
    AMQP_PING_HEADER_CODE           = 0x00,
};

static String const AMQP_PROTOCOL_HEADER_CODE_STRING       = "Protocol header";
static String const AMQP_OPEN_HEADER_CODE_STRING           = "Open";
static String const AMQP_BEGIN_HEADER_CODE_STRING          = "Begin";
static String const AMQP_ATTACH_HEADER_CODE_STRING         = "Attach";
static String const AMQP_FLOW_HEADER_CODE_STRING           = "Flow";
static String const AMQP_TRANSFER_HEADER_CODE_STRING       = "Transfer";
static String const AMQP_DISPOSITION_HEADER_CODE_STRING    = "Disposition";
static String const AMQP_DETACH_HEADER_CODE_STRING         = "Detach";
static String const AMQP_END_HEADER_CODE_STRING            = "End";
static String const AMQP_CLOSE_HEADER_CODE_STRING          = "Close";
static String const AMQP_MECHANISMS_HEADER_CODE_STRING     = "Mechanisms";
static String const AMQP_INIT_HEADER_CODE_STRING           = "Init";
static String const AMQP_CHALLENGE_HEADER_CODE_STRING      = "Challenge";
static String const AMQP_RESPONSE_HEADER_CODE_STRING       = "Response";
static String const AMQP_OUTCOME_HEADER_CODE_STRING        = "Outcome";
static String const AMQP_PING_HEADER_CODE_STRING           = "Ping";

class AMQPHeaderCode : public EnumObject
{
private:

    int value;

public:
    AMQPHeaderCode();
    AMQPHeaderCode(int value);

    int getValue();
    String getName();
};

#endif // AMQPHEADERCODE_H
