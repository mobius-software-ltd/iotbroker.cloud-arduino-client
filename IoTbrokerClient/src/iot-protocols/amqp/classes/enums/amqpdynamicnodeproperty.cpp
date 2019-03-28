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

#include "amqpdynamicnodeproperty.h"

AMQPDynamicNodeProperty::AMQPDynamicNodeProperty()
{
    this->map = std::map<int, String>();
    this->map.insert(std::pair<int, String>(AMQP_SUPPORTED_DIST_MODES_DYNAMIC_NODE_PROPERTY, AMQP_SUPPORTED_DIST_MODES_DYNAMIC_NODE_PROPERTY_STRING));
    this->map.insert(std::pair<int, String>(AMQP_DURABLE_DYNAMIC_NODE_PROPERTY, AMQP_DURABLE_DYNAMIC_NODE_PROPERTY_STRING));
    this->map.insert(std::pair<int, String>(AMQP_AUTO_DELETE_DYNAMIC_NODE_PROPERTY, AMQP_AUTO_DELETE_DYNAMIC_NODE_PROPERTY_STRING));
    this->map.insert(std::pair<int, String>(AMQP_ALTERNATE_EXCHANGE_DYNAMIC_NODE_PROPERTY, AMQP_ALTERNATE_EXCHANGE_DYNAMIC_NODE_PROPERTY_STRING));
    this->map.insert(std::pair<int, String>(AMQP_EXCHANGE_TYPE_DYNAMIC_NODE_PROPERTY, AMQP_EXCHANGE_TYPE_DYNAMIC_NODE_PROPERTY_STRING));
}

AMQPDynamicNodeProperty::AMQPDynamicNodeProperty(int value) : AMQPDynamicNodeProperty()
{
    this->value = value;
}

int AMQPDynamicNodeProperty::getValue()
{
    return this->value;
}

String AMQPDynamicNodeProperty::getName()
{
    return EnumObject::getName(this->value);
}
