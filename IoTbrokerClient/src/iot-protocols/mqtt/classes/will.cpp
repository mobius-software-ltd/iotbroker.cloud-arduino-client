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

#include "will.h"

Will::Will()
{

}

Will::Will(MQTopic *topic, unsigned char *content[], bool retain)
{
    this->topic = topic;
    this->content = content[];
    this->retain = retain;
}

int Will::retrieveLength()
{
    return this->topic->getLength() + strlen(this->content) + 4;
}

MQTopic *Will::getTopic()
{
    return this->topic;
}

void Will::setTopic(MQTopic *topic)
{
    this->topic = topic;
}

QByteArray Will::getContent()
{
    return this->content;
}

void Will::setContent(QByteArray content)
{
    this->content = content;
}

bool Will::isRetain()
{
    return this->retain;
}

void Will::setRetain(bool retain)
{
    this->retain = retain;
}

bool Will::isValid()
{
    return this->topic != NULL && this->topic->getLength() > 0 && !this->content.isEmpty() && this->topic->getQoS() != NULL;
}
