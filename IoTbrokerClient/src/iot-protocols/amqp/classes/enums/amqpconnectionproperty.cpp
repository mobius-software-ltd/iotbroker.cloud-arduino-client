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

#include "amqpconnectionproperty.h"

AMQPConnectionProperty::AMQPConnectionProperty()
{
    this->map = std::map<int, String>();

    this->map.insert(std::pair<int, String>(AMQP_PLATFORM_CONNECTION_PROPERTY, AMQP_PLATFORM_CONNECTION_PROPERTY_STRING));
    this->map.insert(std::pair<int, String>(AMQP_PRODUCT_CONNECTION_PROPERTY, AMQP_PRODUCT_CONNECTION_PROPERTY_STRING));
    this->map.insert(std::pair<int, String>(AMQP_QPID_CLIENT_PID_CONNECTION_PROPERTY, AMQP_QPID_CLIENT_PID_CONNECTION_PROPERTY_STRING));
    this->map.insert(std::pair<int, String>(AMQP_QPID_CLIENT_PPID_CONNECTION_PROPERTY, AMQP_QPID_CLIENT_PPID_CONNECTION_PROPERTY_STRING));
    this->map.insert(std::pair<int, String>(AMQP_QPID_CLIENT_PROCESS_CONNECTION_PROPERTY, AMQP_QPID_CLIENT_PROCESS_CONNECTION_PROPERTY_STRING));
    this->map.insert(std::pair<int, String>(AMQP_VERSION_CONNECTION_PROPERTY, AMQP_VERSION_CONNECTION_PROPERTY_STRING));
}

AMQPConnectionProperty::AMQPConnectionProperty(int value) : AMQPConnectionProperty()
{
    this->value = value;
}

int AMQPConnectionProperty::getValue()
{
    return this->value;
}

String AMQPConnectionProperty::getName()
{
    return EnumObject::getName(this->value);
}
