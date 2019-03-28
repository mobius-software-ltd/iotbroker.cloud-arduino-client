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

#include "snencapsulated.h"


SNEncapsulated::SNEncapsulated()
{

}

SNEncapsulated::SNEncapsulated(SNRadius radius, String nodeID, Message *message)
{
    this->radius = radius;
    this->wirelessNodeID = nodeID;
    this->message = message;
}

int SNEncapsulated::getLength()
{
    int length = 3;
    if (strlen(this->wirelessNodeID) > 0) {
        length += strlen(this->wirelessNodeID);
    }
    if (this->getMessage()->getLength() > 0) {
        length += this->getMessage()->getLength();
    }
    return length;
}

int SNEncapsulated::getType()
{
    return SN_ENCAPSULATED;
}

IotEnumProtocol *SNEncapsulated::getProtocol()
{
    return new IotEnumProtocol(MQTT_SN_PROTOCOL);
}

SNRadius SNEncapsulated::getRadius() const
{
    return radius;
}

void SNEncapsulated::setRadius(const SNRadius &value)
{
    radius = value;
}

String SNEncapsulated::getWirelessNodeID() const
{
    return wirelessNodeID;
}

void SNEncapsulated::setWirelessNodeID(const String &value)
{
    wirelessNodeID = value;
}

Message *SNEncapsulated::getMessage() const
{
    return message;
}

void SNEncapsulated::setMessage(Message *value)
{
    message = value;
}
