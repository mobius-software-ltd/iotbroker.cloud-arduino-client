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

#ifndef AMQPROLECODE_H
#define AMQPROLECODE_H

#include <map>
#include "iot-protocols/amqp/classes/enums/enumobject.h"

enum AMQPRoleCodes
{
    AMQP_SENDER_ROLE_CODE = false,
    AMQP_RECEIVER_ROLE_CODE = true,
};

static String const AMQP_SENDER_ROLE_CODE_STRING = "sender";
static String const AMQP_RECEIVER_ROLE_CODE_STRING = "receiver";

class AMQPRoleCode : public EnumObject
{
private:

    int value;

public:
    AMQPRoleCode();
    AMQPRoleCode(int value);

    int getValue();
    String getName();
};

#endif // AMQPROLECODE_H
