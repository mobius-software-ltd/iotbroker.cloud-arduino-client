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

#include "connect.h"
#include "iot-protocols/mqtt/classes/mqttenums.h"

Connect::Connect()
{
    this->protocolLevel = 4;
}

Connect::Connect(String username, String password, String clientID, bool cleanSession, int keepAlive, Will *will)
{
    this->username = username;
    this->password = password;
    this->clientID = clientID;
    this->cleanSession = cleanSession;
    this->keepAlive = keepAlive;
    this->will = will;
    this->protocolLevel = 4;
}

int Connect::getLength()
{
    int length = 10;
    length += this->clientID.length() + 2;
    length += isWillFlag() ? this->will->retrieveLength() : 0;
    length += this->username != NULL ? this->username.length() + 2 : 0;
    length += this->password != NULL ? this->password.length() + 2 : 0;
    return length;
}

int Connect::getType()
{
    return MQ_CONNECT;
}

IotEnumProtocol *Connect::getProtocol()
{
    return new IotEnumProtocol(MQTT_PROTOCOL);
}

int Connect::getProtocolLevel()
{
    return this->protocolLevel;
}

void Connect::setProtocolLevel(int protocolLevel)
{
    this->protocolLevel = protocolLevel;
}

bool Connect::isCleanSession()
{
    return this->cleanSession;
}

void Connect::setCleanSession(bool cleanSession)
{
    this->cleanSession = cleanSession;
}

bool Connect::isWillFlag()
{
    return (this->getWill()->getTopic()->getName().length() > 0 && this->getWill()->getContent().size() > 0);
}

Will *Connect::getWill()
{
    return this->will;
}

void Connect::setWill(Will *will)
{
    this->will = will;
}

int Connect::getKeepAlive()
{
    return this->keepAlive;
}

void Connect::setKeepAlive(int keepAlive)
{
    this->keepAlive = keepAlive;
}

String Connect::getClientID()
{
    return this->clientID;
}

void Connect::setClientID(String clientID)
{
    this->clientID = clientID;
}

bool Connect::isUsernameFlag()
{
    return this->username != NULL;
}

String Connect::getUsername()
{
    return this->username;
}

void Connect::setUsername(String username)
{
    this->username = username;
}

bool Connect::isPasswordFlag()
{
    return this->password != NULL;
}

String Connect::getPassword()
{
    return this->password;
}

void Connect::setPassword(String password)
{
    this->password = password;
}
