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

#include "snpingreq.h"

SNPingreq::SNPingreq()
{

}

SNPingreq::SNPingreq(String clientID)
{
    this->clientID = clientID;
}

int SNPingreq::getLength()
{
    int length = 2;
    if (strlen(this->clientID) > 0) {
        length += strlen(this->clientID);
    }
    return length;
}

int SNPingreq::getType()
{
    return SN_PINGREQ;
}

IotEnumProtocol *SNPingreq::getProtocol()
{
    return new IotEnumProtocol(MQTT_SN_PROTOCOL);
}

String SNPingreq::getClientID() const
{
    return clientID;
}

void SNPingreq::setClientID(const String &value)
{
    clientID = value;
}
