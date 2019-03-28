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

#ifndef AMQPLIFETIMEPOLICY_H
#define AMQPLIFETIMEPOLICY_H

#include <map>
#include "iot-protocols/amqp/classes/enums/enumobject.h"

enum AMQPLifetimePolicies
{
    AMQP_DELETE_ON_CLOSE_LIFE_TIME_POLICY                   = 0x2b,
    AMQP_DELETE_ON_NO_LINKS_LIFE_TIME_POLICY                = 0x2c,
    AMQP_DELETE_ON_NO_MESSAGES_LIFE_TIME_POLICY             = 0x2d,
    AMQP_DELETE_ON_NO_LINKS_OR_MESSAGES_LIFE_TIME_POLICY    = 0x2e,
};

static String const AMQP_DELETE_ON_CLOSE_LIFE_TIME_POLICY_STRING = "Delete on close";
static String const AMQP_DELETE_ON_NO_LINKS_LIFE_TIME_POLICY_STRING = "Delete on no links";
static String const AMQP_DELETE_ON_NO_MESSAGES_LIFE_TIME_POLICY_STRING = "Delete on no messages";
static String const AMQP_DELETE_ON_NO_LINKS_OR_MESSAGES_LIFE_TIME_POLICY_STRING = "Delete on no links or messages";

class AMQPLifetimePolicy : public EnumObject
{
private:

    int value;

public:
    AMQPLifetimePolicy();
    AMQPLifetimePolicy(int value);

    int getValue();
    String getName();

};

#endif // AMQPLIFETIMEPOLICY_H
