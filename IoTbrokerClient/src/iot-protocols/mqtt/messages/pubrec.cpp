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

#include "pubrec.h"
#include "iot-protocols/mqtt/classes/mqttenums.h"

Pubrec::Pubrec()
{
    this->packetID = 0;
}

Pubrec::Pubrec(int packetID)
{
    this->packetID = packetID;
}

int Pubrec::getPacketID()
{
    return this->packetID;
}

void Pubrec::setPacketID(int packetID)
{
    this->packetID = packetID;
}

int Pubrec::getLength()
{
    return 2;
}

int Pubrec::getType()
{
    return MQ_PUBREC;
}

IotEnumProtocol *Pubrec::getProtocol()
{
    return new IotEnumProtocol(MQTT_PROTOCOL);
}
