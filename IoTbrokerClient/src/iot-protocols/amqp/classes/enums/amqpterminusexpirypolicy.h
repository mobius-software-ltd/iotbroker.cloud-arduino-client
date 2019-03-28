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

#ifndef AMQPTERMINUSEXPIRYPOLICY_H
#define AMQPTERMINUSEXPIRYPOLICY_H

#include <map>
#include "iot-protocols/amqp/classes/enums/enumobject.h"

enum AMQPTerminusExpiryPolicies
{
    AMQP_LINK_DETACH_TERMINUS_EXPIRY_POLICIES       = 0,
    AMQP_SESSION_END_TERMINUS_EXPIRY_POLICIES       = 1,
    AMQP_CONNECTION_CLOSE_TERMINUS_EXPIRY_POLICIES  = 2,
    AMQP_NEVER_TERMINUS_EXPIRY_POLICIES             = 3,
};

static String const AMQP_LINK_DETACH_TERMINUS_EXPIRY_POLICIES_STRING = "link-detach";
static String const AMQP_SESSION_END_TERMINUS_EXPIRY_POLICIES_STRING = "session-end";
static String const AMQP_CONNECTION_CLOSE_TERMINUS_EXPIRY_POLICIES_STRING = "connection-close";
static String const AMQP_NEVER_TERMINUS_EXPIRY_POLICIES_STRING = "none";

class AMQPTerminusExpiryPolicy : public EnumObject
{
private:

    int value;

public:
    AMQPTerminusExpiryPolicy();
    AMQPTerminusExpiryPolicy(int value);

    int getValue();
    String getName();
};

#endif // AMQPTERMINUSEXPIRYPOLICY_H
