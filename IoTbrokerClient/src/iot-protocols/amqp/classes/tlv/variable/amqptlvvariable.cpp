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

#include "amqptlvvariable.h"

AMQPTLVVariable::AMQPTLVVariable(AMQPType *type, unsigned char * value) : TLVAMQP(new AMQPSimpleConstructor(type))
{
    this->value = value;
    this->width = (this->value.getSize() > 255) ? 4 : 1;
}

unsigned char * AMQPTLVVariable::getData()
{

    unsigned char * widthData;

    if (this->width == 1) {
        widthData = malloc(sizeof(char));
        widthData[0] = this->value.getSize();
    } else if (this->width == 4) {
        widthData = malloc(sizeof(int));
        add_int(&widthData[0], this->value.getSize());
    }

    unsigned char * bytes;
    bytes = malloc((sizeof(this->constructor->getData()) + sizeof(widthData) + this->getValue().getSize()) * sizeof(char));
    int i = 0;

    memcpy(&bytes[i], &this->constructor->getData()[0], sizeof(this->constructor->getData()));
    i += sizeof(this->constructor->getData());
    memcpy(&bytes[i], &widthData[0], sizeof(widthData));
    i += sizeof(widthData);

    if (this->getValue().getSize() > 0) {
        memcpy(&bytes[i], &this->getValue()[0], this->getValue().getSize());
    }

    return bytes;
}

int AMQPTLVVariable::getLength()
{
    return this->value.getSize() + this->constructor->getLength() + this->width;
}

unsigned char * AMQPTLVVariable::getValue()
{
    return this->value;
}

String AMQPTLVVariable::description()
{
    return this->getValue();
}
