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

#include "snsuback.h"

SNSuback::SNSuback()
{

}

SNSuback::SNSuback(int topicID, int packetID, SNReturnCode code, QoS *qos)
{
    this->topicID = topicID;
    this->packetID = packetID;
    this->code = code;
    this->qos = qos;
}

int SNSuback::getLength()
{
    return 8;
}

int SNSuback::getType()
{
    return SN_SUBACK;
}

IotEnumProtocol *SNSuback::getProtocol()
{
    return new IotEnumProtocol(MQTT_SN_PROTOCOL);
}

int SNSuback::getPacketID()
{
    return this->packetID;
}

void SNSuback::setPacketID(int value)
{
    this->packetID = value;
}

int SNSuback::getTopicID() const
{
    return topicID;
}

void SNSuback::setTopicID(int value)
{
    topicID = value;
}

SNReturnCode SNSuback::getCode() const
{
    return code;
}

void SNSuback::setCode(const SNReturnCode &value)
{
    code = value;
}

QoS *SNSuback::getQos() const
{
    return qos;
}

void SNSuback::setQos(QoS *value)
{
    qos = value;
}
