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

#include "unsubscribe.h"
#include "iot-protocols/mqtt/classes/mqttenums.h"

Unsubscribe::Unsubscribe()
{
    this->packetID = 0;
}

Unsubscribe::Unsubscribe(list<String> *topics)
{
    this->packetID = 0;
    this->topics = topics;
}

Unsubscribe::Unsubscribe(int packetID, list<String> *topics)
{
    this->packetID = packetID;
    this->topics = topics;
}

int Unsubscribe::getPacketID()
{
    return this->packetID;
}

void Unsubscribe::setPacketID(int packetID)
{
    this->packetID = packetID;
}

int Unsubscribe::getLength()
{
    int length = 2;
    for (int i = 0; i < this->topics->size(); i++) {
        String item = this->topics->at(i);
        length += item.length() + 2;
    }
    return length;
}

int Unsubscribe::getType()
{
    return MQ_UNSUBSCRIBE;
}

IotEnumProtocol *Unsubscribe::getProtocol()
{
    return new IotEnumProtocol(MQTT_PROTOCOL);
}

list<String> *Unsubscribe::getTopics()
{
    return topics;
}

void Unsubscribe::setTopics(list<String> *topics)
{
    this->topics = topics;
}
