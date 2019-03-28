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

#include "connack.h"
#include "iot-protocols/mqtt/classes/mqttenums.h"

Connack::Connack()
{

}

Connack::Connack(bool sessionPresent, MQConnackCode returnCode)
{
    this->sessionPresent = sessionPresent;
    this->returnCode = returnCode;
}

int Connack::getLength()
{
    return 2;
}

int Connack::getType()
{
    return MQ_CONNACK;
}

IotEnumProtocol *Connack::getProtocol()
{
    return new IotEnumProtocol(MQTT_PROTOCOL);
}

bool Connack::isSessionPresent()
{
    return this->sessionPresent;
}

void Connack::setSessionPresent(bool sessionPresent)
{
    this->sessionPresent = sessionPresent;
}

MQConnackCode Connack::getReturnCode()
{
    return this->returnCode;
}

void Connack::setReturnCode(MQConnackCode returnCode)
{
    this->returnCode = returnCode;
}

bool Connack::isValidReturnCode(MQConnackCode code)
{
    if (code >= MQ_ACCEPTED && code <= MQ_NOT_AUTHORIZED) {
        return true;
    }
    return false;
}
