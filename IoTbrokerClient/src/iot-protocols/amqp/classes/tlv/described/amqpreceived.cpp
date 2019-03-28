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

#include "amqpreceived.h"
#include "iot-protocols/amqp/classes/headerapi/amqpunwrapper.h"
#include "iot-protocols/amqp/classes/headerapi/amqpwrapper.h"
#include "iot-protocols/amqp/classes/constructors/amqpdescribedconstructor.h"

void AMQPReceived::fill(AMQPTLVList *list)
{
    if (list->getList().size() > 0) {
        TLVAMQP *element = list->getList()[0];
        if (!element->isNull()) {
            JsonVariant variant;
            variant.set((long long)AMQPUnwrapper::unwrapUInt(element));
            this->sectionNumber = variant;
        }
    }

    if (list->getList().size() > 0) {
        TLVAMQP *element = list->getList()[1]);
        if (!element->isNull()) {
            JsonVariant variant;
            variant.set((long long)AMQPUnwrapper::unwrapULong(element));
            this->sectionOffset = variant;
        }
    }
}

AMQPTLVList *AMQPReceived::getList()
{
    AMQPTLVList *list = new AMQPTLVList();

    if (this->sectionNumber != NULL) {
        list->addElementWithIndex(0, AMQPWrapper::wrapUInt(this->sectionNumber));
    }
    if (this->sectionOffset != NULL) {
        list->addElementWithIndex(1, AMQPWrapper::wrapULong(this->sectionOffset));
    }

    unsigned char * data;
    data = malloc(sizeof(char));
    data[0] = (char) 0x23;

    AMQPType *type = new AMQPType(AMQP_SMALL_ULONG_TYPE);
    AMQPTLVFixed *fixed = new AMQPTLVFixed(type, data);

    AMQPType *constructorType = new AMQPType(list->getTypeValue());
    AMQPDescribedConstructor *constructor = new AMQPDescribedConstructor(constructorType, fixed);

    list->setConstructor(constructor);

    return list;
}

JsonVariant *AMQPReceived::getSectionNumber() const
{
    return sectionNumber;
}

void AMQPReceived::setSectionNumber(JsonVariant *value)
{
    sectionNumber = value;
}

JsonVariant *AMQPReceived::getSectionOffset() const
{
    return sectionOffset;
}

void AMQPReceived::setSectionOffset(JsonVariant *value)
{
    sectionOffset = value;
}
