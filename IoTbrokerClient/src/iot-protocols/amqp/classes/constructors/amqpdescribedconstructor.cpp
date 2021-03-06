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

#include "amqpdescribedconstructor.h"

AMQPDescribedConstructor::AMQPDescribedConstructor(AMQPType *type, TLVAMQP *descriptor) : AMQPSimpleConstructor(type)
{
    this->descriptor = descriptor;
}

unsigned char *AMQPDescribedConstructor::getData()
{
    unsigned char *data = (unsigned char*) malloc(sizeof(unsigned char) * (sizeof(this->descriptor->getData())+2));
    int i = 0;

    data[i++] = 0;
    int string_length = sizeof(this->descriptor->getData());
    memcpy(&data[i], this->descriptor->getData(), string_length);
    i+=string_length;
    data[i] = this->type->getValue();
    return data;
}

int AMQPDescribedConstructor::getLength()
{
    return sizeof(this->descriptor->getData()) + 2;
}

int AMQPDescribedConstructor::getDescriptorCode()
{
    unsigned char * data = (unsigned char*) malloc(sizeof(unsigned char) * sizeof(this->descriptor->getData()));
    int string_length = sizeof(this->descriptor->getData());
    memcpy(&data[0], this->descriptor->getData(), string_length);
    return data[1];
}
