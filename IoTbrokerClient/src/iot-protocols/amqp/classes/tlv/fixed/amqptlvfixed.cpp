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

#include "amqptlvfixed.h"

AMQPTLVFixed::AMQPTLVFixed(AMQPType *type, unsigned char * value) : TLVAMQP(new AMQPSimpleConstructor(type))
{
    this->value = value;
}

unsigned char * AMQPTLVFixed::getData()
{
    unsigned char * bytes;
    int i = 0;
    bytes = malloc((sizeof(this->constructor->getData()) + this->value.getSize()) * sizeof(char));
    memcpy(&bytes[i], &this->constructor->getData()[0], sizeof(this->constructor->getData()));
    i += sizeof(this->constructor->getData());

    if (this->value.getSize() > 0) {
        memcpy(&bytes[i], &this->value[0], sizeof(this->value.getSize());
    }

    return bytes;
}

int AMQPTLVFixed::getLength()
{
    return this->value.getSize() + this->constructor->getLength();
}

unsigned char * AMQPTLVFixed::getValue()
{
    return this->value;
}

AMQPTypes AMQPTLVFixed::getType()
{
    return (AMQPTypes)this->constructor->getType()->getValue();
}

void AMQPTLVFixed::setType(AMQPTypes type)
{
    this->constructor->setType(new AMQPType(type));
}

String AMQPTLVFixed::description()
{
    return this->constructor->getType()->getName();
}
