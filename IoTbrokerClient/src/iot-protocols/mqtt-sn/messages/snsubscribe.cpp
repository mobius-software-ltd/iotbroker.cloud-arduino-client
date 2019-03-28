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

#include "snsubscribe.h"

SNSubscribe::SNSubscribe()
{

}

SNSubscribe::SNSubscribe(int packetID, Topic *topic, bool isDup)
{
    this->packetID = packetID;
    this->topic = topic;
    this->isDup = isDup;
}

int SNSubscribe::getLength()
{
    int length = 5;
    length += this->topic->getLength();
    if (this->topic->getLength() > 250) {
        length += 2;
    }
    return length;
}

int SNSubscribe::getType()
{
    return SN_SUBSCRIBE;
}

IotEnumProtocol *SNSubscribe::getProtocol()
{
    return new IotEnumProtocol(MQTT_SN_PROTOCOL);
}

int SNSubscribe::getPacketID()
{
    return packetID;
}

void SNSubscribe::setPacketID(int value)
{
    packetID = value;
}

Topic *SNSubscribe::getTopic() const
{
    return topic;
}

void SNSubscribe::setTopic(Topic *value)
{
    topic = value;
}

bool SNSubscribe::getIsDup() const
{
    return isDup;
}

void SNSubscribe::setIsDup(bool value)
{
    isDup = value;
}
