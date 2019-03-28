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

#include "snwilltopic.h"

SNWillTopic::SNWillTopic()
{

}

SNWillTopic::SNWillTopic(SNFullTopic *topic, bool isRetain)
{
    this->topic = topic;
    this->isRetain = isRetain;
}

int SNWillTopic::getLength()
{
    int length = 2;
    if (this->topic != NULL) {
        length += topic->getLength() + 1;
        if (topic->getLength() > 252) {
            length += 2;
        }
    }
    return length;
}

int SNWillTopic::getType()
{
    return SN_WILLTOPIC;
}

IotEnumProtocol *SNWillTopic::getProtocol()
{
    return new IotEnumProtocol(MQTT_SN_PROTOCOL);
}

SNFullTopic *SNWillTopic::getTopic() const
{
    return topic;
}

void SNWillTopic::setTopic(SNFullTopic *value)
{
    topic = value;
}

bool SNWillTopic::getIsRetain() const
{
    return isRetain;
}

void SNWillTopic::setIsRetain(bool value)
{
    isRetain = value;
}
