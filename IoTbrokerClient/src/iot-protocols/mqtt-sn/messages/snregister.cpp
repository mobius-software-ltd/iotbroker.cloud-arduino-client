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

#include "snregister.h"

SNRegister::SNRegister()
{

}

SNRegister::SNRegister(int topicID, int packetID, String topicName)
{
    this->topicID = topicID;
    this->packetID = packetID;
    this->topicName = topicName;
}

int SNRegister::getLength()
{
    if (strlen(this->topicName) == 0) {
        printf("SNRegister must contain a valid topic name");
        return 0;
    }

    int length = 6;
    length += strlen(this->topicName);
    if (strlen(this->topicName) > 249) {
        length += 2;
    }
    return length;
}

int SNRegister::getType()
{
    return SN_REGISTER;
}

IotEnumProtocol *SNRegister::getProtocol()
{
    return new IotEnumProtocol(MQTT_SN_PROTOCOL);
}

int SNRegister::getTopicID() const
{
    return topicID;
}

void SNRegister::setTopicID(int value)
{
    topicID = value;
}

int SNRegister::getPacketID()
{
    return packetID;
}

void SNRegister::setPacketID(int value)
{
    packetID = value;
}

String SNRegister::getTopicName() const
{
    return topicName;
}

void SNRegister::setTopicName(const String &value)
{
    topicName = value;
}
