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

#include "snunsubscribe.h"

SNUnsubscribe::SNUnsubscribe()
{

}

SNUnsubscribe::SNUnsubscribe(int packetID, Topic *topic)
{
    this->packetID = packetID;
    this->topic = topic;
}

int SNUnsubscribe::getLength()
{
    int length = 5;
    length += this->topic->getLength();
    if (this->topic->getLength() > 250) {
        length += 2;
    }
    return length;
}

int SNUnsubscribe::getType()
{
    return SN_UNSUBSCRIBE;
}

IotEnumProtocol *SNUnsubscribe::getProtocol()
{
    return new IotEnumProtocol(MQTT_SN_PROTOCOL);
}

int SNUnsubscribe::getPacketID()
{
    return packetID;
}

void SNUnsubscribe::setPacketID(int value)
{
    packetID = value;
}

Topic *SNUnsubscribe::getTopic() const
{
    return topic;
}

void SNUnsubscribe::setTopic(Topic *value)
{
    topic = value;
}
