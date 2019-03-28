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

#include "snidentifiertopic.h"

SNIdentifierTopic::SNIdentifierTopic()
{

}

SNIdentifierTopic::SNIdentifierTopic(int value, QoS *qos)
{
    this->value = value;
    this->qos = qos;
}

SNTopicTypes SNIdentifierTopic::getType()
{
    return SN_ID_TOPIC_TYPE;
}

QoS *SNIdentifierTopic::getQoS()
{
    return this->qos;
}

unsigned char * SNIdentifierTopic::encode()
{
    short shortValue = (short)this->value;
    unsigned char * buffer = NULL;
    buffer = malloc(sizeof unsigned char * 2)
    add_short(&buffer[0], shortValue);

    return buffer;
}

int SNIdentifierTopic::getLength()
{
    return 2;
}
