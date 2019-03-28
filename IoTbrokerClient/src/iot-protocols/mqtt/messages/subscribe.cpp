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

#include "subscribe.h"
#include "iot-protocols/mqtt/classes/mqttenums.h"

Subscribe::Subscribe()
{
    this->packetID = 0;
}

Subscribe::Subscribe(int packetID)
{
    this->packetID = packetID;
}

Subscribe::Subscribe(list<MQTopic> *topics)
{
    this->packetID = 0;
    this->topics = topics;
}

Subscribe::Subscribe(int packetID, list<MQTopic> *topics)
{
    this->packetID = packetID;
    this->topics = topics;
}

int Subscribe::getPacketID()
{
    return this->packetID;
}

void Subscribe::setPacketID(int packetID)
{
    this->packetID = packetID;
}

int Subscribe::getLength()
{
    int length = 0;
    length += this->packetID != 0 ? 2 : 0;
    for (int i = 0; i < this->topics->size(); i++) {
        MQTopic item = this->topics->at(i);
        length += item.getName().length() + 3;
    }
    return length;
}

int Subscribe::getType()
{
    return MQ_SUBSCRIBE;
}

IotEnumProtocol *Subscribe::getProtocol()
{
    return new IotEnumProtocol(MQTT_PROTOCOL);
}

list<MQTopic> *Subscribe::getTopics()
{
    return this->topics;
}

void Subscribe::setTopics(list<MQTopic> *topics)
{
    this->topics = topics;
}
