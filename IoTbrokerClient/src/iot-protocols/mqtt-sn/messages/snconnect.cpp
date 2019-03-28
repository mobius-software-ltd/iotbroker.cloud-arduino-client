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

#include "snconnect.h"

SNConnect::SNConnect()
{
    this->protocolID = MQTT_SN_PROTOCOL_ID;
}

SNConnect::SNConnect(bool cleanSession, int duration, String clientID, bool willPresent) : SNConnect()
{
    this->cleanSession = cleanSession;
    this->duration = duration;
    this->clientID = clientID;
    this->willPresent = willPresent;
}

int SNConnect::getLength()
{
    if (strlen(this->clientID) <= 0) {
        printf("connect must contain a valid clientID");
        return 0;
    }
    return 6 + strlen(this->clientID);
}

int SNConnect::getType()
{
    return SN_CONNECT;
}

IotEnumProtocol *SNConnect::getProtocol()
{
    return new IotEnumProtocol(MQTT_SN_PROTOCOL);
}

bool SNConnect::getWillPresent() const
{
    return willPresent;
}

void SNConnect::setWillPresent(bool value)
{
    willPresent = value;
}

bool SNConnect::getCleanSession() const
{
    return cleanSession;
}

void SNConnect::setCleanSession(bool value)
{
    cleanSession = value;
}

int SNConnect::getProtocolID() const
{
    return protocolID;
}

void SNConnect::setProtocolID(int value)
{
    protocolID = value;
}

int SNConnect::getDuration() const
{
    return duration;
}

void SNConnect::setDuration(int value)
{
    duration = value;
}

String SNConnect::getClientID() const
{
    return clientID;
}

void SNConnect::setClientID(const String &value)
{
    clientID = value;
}
