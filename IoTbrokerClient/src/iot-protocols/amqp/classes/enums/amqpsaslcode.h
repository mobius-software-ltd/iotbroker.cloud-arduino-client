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

#ifndef AMQPSASLCODE_H
#define AMQPSASLCODE_H

#include <map>
#include "iot-protocols/amqp/classes/enums/enumobject.h"

enum AMQPSASLCodes
{
    AMQP_OK_SASL_CODE       = 0,
    AMQP_AUTH_SASL_CODE     = 1,
    AMQP_SYS_SASL_CODE      = 2,
    AMQP_SYS_PERM_SASL_CODE = 3,
    AMQP_SYS_TEMP_SASL_CODE = 4,
};

static String const AMQP_OK_SASL_CODE_STRING = "ok";
static String const AMQP_AUTH_SASL_CODE_STRING = "auth";
static String const AMQP_SYS_SASL_CODE_STRING = "sys";
static String const AMQP_SYS_PERM_SASL_CODE_STRING = "sys-perm";
static String const AMQP_SYS_TEMP_SASL_CODE_STRING = "sys-temp";

class AMQPSASLCode : public EnumObject
{
private:

    int value;

public:
    AMQPSASLCode();
    AMQPSASLCode(int value);

    int getValue();
    String getName();
};

#endif // AMQPSASLCODE_H
