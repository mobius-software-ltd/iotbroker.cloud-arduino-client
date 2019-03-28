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

#include "amqpheadercode.h"

AMQPHeaderCode::AMQPHeaderCode()
{
    this->map = std::map<int, String>();
    this->map.insert(std::pair<int, String>(AMQP_PROTOCOL_HEADER_CODE, AMQP_PROTOCOL_HEADER_CODE_String));
    this->map.insert(std::pair<int, String>(AMQP_OPEN_HEADER_CODE, AMQP_OPEN_HEADER_CODE_String));
    this->map.insert(std::pair<int, String>(AMQP_BEGIN_HEADER_CODE, AMQP_BEGIN_HEADER_CODE_String));
    this->map.insert(std::pair<int, String>(AMQP_ATTACH_HEADER_CODE, AMQP_ATTACH_HEADER_CODE_String));
    this->map.insert(std::pair<int, String>(AMQP_FLOW_HEADER_CODE, AMQP_FLOW_HEADER_CODE_String));
    this->map.insert(std::pair<int, String>(AMQP_TRANSFER_HEADER_CODE, AMQP_TRANSFER_HEADER_CODE_String));
    this->map.insert(std::pair<int, String>(AMQP_DISPOSITION_HEADER_CODE, AMQP_DISPOSITION_HEADER_CODE_String));
    this->map.insert(std::pair<int, String>(AMQP_DETACH_HEADER_CODE, AMQP_DETACH_HEADER_CODE_String));
    this->map.insert(std::pair<int, String>(AMQP_END_HEADER_CODE, AMQP_END_HEADER_CODE_String));
    this->map.insert(std::pair<int, String>(AMQP_CLOSE_HEADER_CODE, AMQP_CLOSE_HEADER_CODE_String));
    this->map.insert(std::pair<int, String>(AMQP_MECHANISMS_HEADER_CODE, AMQP_MECHANISMS_HEADER_CODE_String));
    this->map.insert(std::pair<int, String>(AMQP_INIT_HEADER_CODE, AMQP_INIT_HEADER_CODE_String));
    this->map.insert(std::pair<int, String>(AMQP_CHALLENGE_HEADER_CODE, AMQP_CHALLENGE_HEADER_CODE_String));
    this->map.insert(std::pair<int, String>(AMQP_RESPONSE_HEADER_CODE, AMQP_RESPONSE_HEADER_CODE_String));
    this->map.insert(std::pair<int, String>(AMQP_OUTCOME_HEADER_CODE, AMQP_OUTCOME_HEADER_CODE_String));
    this->map.insert(std::pair<int, String>(AMQP_PING_HEADER_CODE, AMQP_PING_HEADER_CODE_String));
}

AMQPHeaderCode::AMQPHeaderCode(int value) : AMQPHeaderCode()
{
    this->value = value;
}

int AMQPHeaderCode::getValue()
{
    return this->value;
}

String AMQPHeaderCode::getName()
{
    return EnumObject::getName(this->value);
}
