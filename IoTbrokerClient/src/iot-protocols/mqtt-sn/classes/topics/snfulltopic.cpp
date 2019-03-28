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

#include "snfulltopic.h"

SNFullTopic::SNFullTopic()
{

}

SNFullTopic::SNFullTopic(String value, QoS *qos)
{
    this->value = value;
    this->qos = qos;
}

SNTopicTypes SNFullTopic::getType()
{
    return SN_NAMED_TOPIC_TYPE;
}

QoS *SNFullTopic::getQoS()
{
    return this->qos;
}

unsigned char * SNFullTopic::encode()
{
    return this->value;
}

int SNFullTopic::getLength()
{
    return strlen(this->value);
}

String SNFullTopic::getValue() const
{
    return value;
}

void SNFullTopic::setValue(const String &value)
{
    this->value = value;
}
