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

#include "snpublish.h"

SNPublish::SNPublish()
{

}

SNPublish::SNPublish(int packetID, Topic *topic, unsigned char *content, bool isDup, bool isRetain)
{
    this->packetID = packetID;
    this->topic = topic;
    this->content = content;
    this->isDup = isDup;
    this->isRetain = isRetain;
}

int SNPublish::getLength()
{
    int length = 5;
    length += this->getTopic()->getLength();
    length += sizeof(this->content);
    if (sizeof(this->content) > 248) {
        length += 2;
    }
    return length;
}

int SNPublish::getType()
{
    return SN_PUBLISH;
}

IotEnumProtocol *SNPublish::getProtocol()
{
    return new IotEnumProtocol(MQTT_SN_PROTOCOL);
}

int SNPublish::getPacketID()
{
    return packetID;
}

void SNPublish::setPacketID(int value)
{
    packetID = value;
}

Topic *SNPublish::getTopic() const
{
    return topic;
}

void SNPublish::setTopic(Topic *value)
{
    topic = value;
}

unsigned char *SNPublish::getContent() const
{
    return content;
}

void SNPublish::setContent(unsigned char *value)
{
    content = value;
}

bool SNPublish::getIsDup() const
{
    return isDup;
}

void SNPublish::setIsDup(bool value)
{
    isDup = value;
}

bool SNPublish::getIsRetain() const
{
    return isRetain;
}

void SNPublish::setIsRetain(bool value)
{
    isRetain = value;
}
