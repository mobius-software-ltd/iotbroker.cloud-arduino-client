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

#include "amqpheader.h"

AMQPHeader::AMQPHeader()
{
    this->doff = 2;
    this->typeValue = 0;
    this->channel = 0;
}


AMQPHeader::AMQPHeader(AMQPHeaderCode *code) : AMQPHeader()
{
    this->code = code;
    this->doff = 2;
    this->typeValue = 0;
    this->channel = 0;
}

int AMQPHeader::getLength()
{
    return 8;
}

int AMQPHeader::getType()
{
    return 0;
}

IotEnumProtocol *AMQPHeader::getProtocol()
{
    return new IotEnumProtocol(AMQP_PROTOCOL);
}

AMQPHeaderCode *AMQPHeader::getCode() const
{
    return code;
}

void AMQPHeader::setCode(AMQPHeaderCode *value)
{
    code = value;
}

int AMQPHeader::getDoff() const
{
    return doff;
}

void AMQPHeader::setDoff(int value)
{
    doff = value;
}

int AMQPHeader::getTypeValue() const
{
    return typeValue;
}

void AMQPHeader::setTypeValue(int value)
{
    typeValue = value;
}

int AMQPHeader::getChannel() const
{
    return channel;
}

void AMQPHeader::setChannel(int value)
{
    channel = value;
}
