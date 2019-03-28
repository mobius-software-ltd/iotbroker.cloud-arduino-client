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

#include "amqpsequence.h"
#include "iot-protocols/amqp/classes/headerapi/amqpwrapper.h"
#include "iot-protocols/amqp/classes/headerapi/amqpunwrapper.h"
#include "iot-protocols/amqp/classes/constructors/amqpdescribedconstructor.h"

AMQPSequence::AMQPSequence()
{
    this->sequence = NULL;
}

TLVAMQP *AMQPSequence::getValue()
{
    AMQPTLVList *list = new AMQPTLVList();

    if (this->sequence != NULL and this->sequence.size() != 0) {
        list = (AMQPTLVList *)AMQPWrapper::wrapList(this->sequence);
    }

    unsigned char * data = NULL;
    data = malloc(sizeof(char));
    data[0] = (char) 0x76;
    AMQPType *type = new AMQPType(AMQP_SMALL_ULONG_TYPE);
    AMQPTLVFixed *fixed = new AMQPTLVFixed(type, data);

    AMQPType *constructorType = new AMQPType(list->getTypeValue());
    AMQPDescribedConstructor *constructor = new AMQPDescribedConstructor(constructorType, fixed);

    list->setConstructor(constructor);
    return list;
}

AMQPSectionCode *AMQPSequence::getCode()
{
    return new AMQPSectionCode(AMQP_SEQUENCE_SECTION_CODE);
}

void AMQPSequence::fill(TLVAMQP *value)
{
    if (!value->isNull()) {
        this->sequence = AMQPUnwrapper::unwrapList(value);
    }
}

void AMQPSequence::addSequence(list<JsonVariant *> array)
{
    std::list<JsonVariant *>::iterator it;
    for(it=array.begin(); it!=array.end(); ++it){
        this->sequence.push_back(item);
    }
}

list<JsonVariant *> AMQPSequence::getSequence() const
{
    return sequence;
}
