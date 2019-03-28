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

#include "amqpsaslcode.h"

AMQPSASLCode::AMQPSASLCode()
{
    this->map = std::map<int, String>();
    this->map.insert(std::pair<int, String>(AMQP_OK_SASL_CODE, AMQP_OK_SASL_CODE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_AUTH_SASL_CODE, AMQP_AUTH_SASL_CODE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_SYS_SASL_CODE, AMQP_SYS_SASL_CODE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_SYS_PERM_SASL_CODE, AMQP_SYS_PERM_SASL_CODE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_SYS_TEMP_SASL_CODE, AMQP_SYS_TEMP_SASL_CODE_STRING));
}

AMQPSASLCode::AMQPSASLCode(int value) : AMQPSASLCode()
{
    this->value = value;
}

int AMQPSASLCode::getValue()
{
    return this->value;
}

String AMQPSASLCode::getName()
{
    return EnumObject::getName(this->value);
}
