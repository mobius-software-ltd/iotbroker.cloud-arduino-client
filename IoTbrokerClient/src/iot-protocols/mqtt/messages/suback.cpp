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

#include "suback.h"
#include "iot-protocols/mqtt/classes/mqttenums.h"

Suback::Suback()
{
    this->packetID = 0;
}

Suback::Suback(int packetID)
{
    this->packetID = packetID;
}

Suback::Suback(int packetID, list<SubackCode> *returnCodes)
{
    this->packetID = packetID;
    this->returnCodes = returnCodes;
}

int Suback::getPacketID()
{
    return this->packetID;
}

void Suback::setPacketID(int packetID)
{
    this->packetID = packetID;
}

int Suback::getLength()
{
    return this->returnCodes->size() + 2;
}

int Suback::getType()
{
    return MQ_SUBACK;
}

IotEnumProtocol *Suback::getProtocol()
{
    return new IotEnumProtocol(MQTT_PROTOCOL);
}

list<SubackCode> *Suback::getReturnCodes()
{
    return this->returnCodes;
}

void Suback::setReturnCodes(list<SubackCode> *returnCodes)
{
    this->returnCodes = returnCodes;
}

bool Suback::isValidCode(SubackCode code)
{
    if (code == ACCEPTED_QOS0 || code == ACCEPTED_QOS1 || code == ACCEPTED_QOS2) {
        return true;
    }
    return false;
}
