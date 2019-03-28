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

#include "publish.h"
#include "iot-protocols/mqtt/classes/mqttenums.h"

Publish::Publish()
{
    this->packetID = 0;
}

Publish::Publish(int packetID)
{
    this->packetID = packetID;
}

Publish::Publish(MQTopic *topic, unsigned char *content[], bool retain, bool dup)
{
    this->packetID = 0;
    this->topic = topic;
    this->content = content[];
    this->retain = retain;
    this->dup = dup;
}

Publish::Publish(int packetID, MQTopic *topic, unsigned char *content[], bool retain, bool dup)
{
    this->packetID = packetID;
    this->topic = topic;
    this->content = content[];
    this->retain = retain;
    this->dup = dup;
}

int Publish::getPacketID()
{
    return this->packetID;
}

void Publish::setPacketID(int packetID)
{
    this->packetID = packetID;
}

int Publish::getLength()
{
    int length = 0;
    length += this->packetID != 0 ? 2 : 0;
    length += this->topic->getLength() + 2;
    length += strlen(this->content);
    return length;
}

int Publish::getType()
{
    return MQ_PUBLISH;
}

IotEnumProtocol *Publish::getProtocol()
{
    return new IotEnumProtocol(MQTT_PROTOCOL);
}

MQTopic *Publish::getTopic()
{
    return this->topic;
}

void Publish::setTopic(MQTopic *topic)
{
    this->topic = topic;
}

QByteArray Publish::getContent()
{
    return this->content;
}

void Publish::setContent(unsigned char *content[])
{
    this->content = content[];
}

bool Publish::isRetain()
{
    return this->retain;
}

void Publish::setRetain(bool retain)
{
    this->retain = retain;
}

bool Publish::isDup()
{
    return this->dup;
}

void Publish::setDup(bool dup)
{
    this->dup = dup;
}
