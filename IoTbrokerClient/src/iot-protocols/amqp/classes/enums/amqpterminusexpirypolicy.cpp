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

#include "amqpterminusexpirypolicy.h"

AMQPTerminusExpiryPolicy::AMQPTerminusExpiryPolicy()
{
    this->map = std::map<int, String>();
    this->map.insert(std::pair<int, String>(AMQP_LINK_DETACH_TERMINUS_EXPIRY_POLICIES, AMQP_LINK_DETACH_TERMINUS_EXPIRY_POLICIES_STRING));
    this->map.insert(std::pair<int, String>(AMQP_SESSION_END_TERMINUS_EXPIRY_POLICIES, AMQP_SESSION_END_TERMINUS_EXPIRY_POLICIES_STRING));
    this->map.insert(std::pair<int, String>(AMQP_CONNECTION_CLOSE_TERMINUS_EXPIRY_POLICIES, AMQP_CONNECTION_CLOSE_TERMINUS_EXPIRY_POLICIES_STRING));
    this->map.insert(std::pair<int, String>(AMQP_NEVER_TERMINUS_EXPIRY_POLICIES, AMQP_NEVER_TERMINUS_EXPIRY_POLICIES_STRING));
}

AMQPTerminusExpiryPolicy::AMQPTerminusExpiryPolicy(int value) : AMQPTerminusExpiryPolicy()
{
    this->value = value;
}

int AMQPTerminusExpiryPolicy::getValue()
{
    return this->value;
}

String AMQPTerminusExpiryPolicy::getName()
{
    return EnumObject::getName(this->value);
}
