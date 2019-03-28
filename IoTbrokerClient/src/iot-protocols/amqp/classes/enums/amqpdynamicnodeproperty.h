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

#ifndef AMQPDYNAMICNODEPROPERTY_H
#define AMQPDYNAMICNODEPROPERTY_H

#include <map>
#include "iot-protocols/amqp/classes/enums/enumobject.h"

enum AMQPDynamicNodeProperties
{
    AMQP_SUPPORTED_DIST_MODES_DYNAMIC_NODE_PROPERTY = 0,
    AMQP_DURABLE_DYNAMIC_NODE_PROPERTY              = 1,
    AMQP_AUTO_DELETE_DYNAMIC_NODE_PROPERTY          = 2,
    AMQP_ALTERNATE_EXCHANGE_DYNAMIC_NODE_PROPERTY   = 3,
    AMQP_EXCHANGE_TYPE_DYNAMIC_NODE_PROPERTY        = 4,
};

static String const AMQP_SUPPORTED_DIST_MODES_DYNAMIC_NODE_PROPERTY_STRING = "supported-dist-modes";
static String const AMQP_DURABLE_DYNAMIC_NODE_PROPERTY_STRING = "durable";
static String const AMQP_AUTO_DELETE_DYNAMIC_NODE_PROPERTY_STRING = "auto-delete";
static String const AMQP_ALTERNATE_EXCHANGE_DYNAMIC_NODE_PROPERTY_STRING = "alternate-exchange";
static String const AMQP_EXCHANGE_TYPE_DYNAMIC_NODE_PROPERTY_STRING = "exchange-type";

class AMQPDynamicNodeProperty : public EnumObject
{
private:

    int value;

public:
    AMQPDynamicNodeProperty();
    AMQPDynamicNodeProperty(int value);

    int getValue();
    String getName();
};

#endif // AMQPDYNAMICNODEPROPERTY_H
