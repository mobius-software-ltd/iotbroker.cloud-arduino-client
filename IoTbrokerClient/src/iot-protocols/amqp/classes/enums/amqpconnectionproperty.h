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

#ifndef AMQPCONNECTIONPROPERTY_H
#define AMQPCONNECTIONPROPERTY_H

#include <map>
#include "iot-protocols/amqp/classes/enums/enumobject.h"

enum AMQPConnectionProperties
{
    AMQP_PLATFORM_CONNECTION_PROPERTY               = 0,
    AMQP_PRODUCT_CONNECTION_PROPERTY                = 1,
    AMQP_QPID_CLIENT_PID_CONNECTION_PROPERTY        = 2,
    AMQP_QPID_CLIENT_PPID_CONNECTION_PROPERTY       = 3,
    AMQP_QPID_CLIENT_PROCESS_CONNECTION_PROPERTY    = 4,
    AMQP_VERSION_CONNECTION_PROPERTY                = 5,
};

static String const AMQP_PLATFORM_CONNECTION_PROPERTY_STRING = "platform";
static String const AMQP_PRODUCT_CONNECTION_PROPERTY_STRING = "product";
static String const AMQP_QPID_CLIENT_PID_CONNECTION_PROPERTY_STRING = "qpid.client_pid";
static String const AMQP_QPID_CLIENT_PPID_CONNECTION_PROPERTY_STRING = "qpid.client_ppid";
static String const AMQP_QPID_CLIENT_PROCESS_CONNECTION_PROPERTY_STRING = "qpid.client_process";
static String const AMQP_VERSION_CONNECTION_PROPERTY_STRING = "version";

class AMQPConnectionProperty : public EnumObject
{
private:

    int value;

public:
    AMQPConnectionProperty();
    AMQPConnectionProperty(int value);

    int getValue();
    String getName();
};

#endif // AMQPCONNECTIONPROPERTY_H
