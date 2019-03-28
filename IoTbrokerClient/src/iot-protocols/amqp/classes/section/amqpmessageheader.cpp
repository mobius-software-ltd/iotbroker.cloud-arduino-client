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

#include "amqpmessageheader.h"
#include "iot-protocols/amqp/classes/headerapi/amqpwrapper.h"
#include "iot-protocols/amqp/classes/headerapi/amqpunwrapper.h"
#include "iot-protocols/amqp/classes/constructors/amqpdescribedconstructor.h"

AMQPMessageHeader::AMQPMessageHeader()
{

}

TLVAMQP *AMQPMessageHeader::getValue()
{
    AMQPTLVList *list = new AMQPTLVList();

    if (this->durable != NULL) {
        list->addElementWithIndex(0, AMQPWrapper::wrapBool(AMQPSimpleType::variantToBool(this->durable)));
    }
    if (this->priority != NULL) {
        list->addElementWithIndex(1, AMQPWrapper::wrapUByte(AMQPSimpleType::variantToUByte(this->priority)));
    }
    if (this->milliseconds != NULL) {
        list->addElementWithIndex(2, AMQPWrapper::wrapUInt(AMQPSimpleType::variantToUInt(this->milliseconds)));
    }
    if (this->firstAquirer != NULL) {
        list->addElementWithIndex(3, AMQPWrapper::wrapBool(AMQPSimpleType::variantToBool(this->firstAquirer)));
    }
    if (this->deliveryCount != NULL) {
        list->addElementWithIndex(4, AMQPWrapper::wrapUInt(AMQPSimpleType::variantToUInt(this->deliveryCount)));
    }

    unsigned char * data = NULL;
    data = malloc(sizeof(char));
    data[0] = (char) 0x70;
    AMQPType *type = new AMQPType(AMQP_SMALL_ULONG_TYPE);
    AMQPTLVFixed *fixed = new AMQPTLVFixed(type, data);

    AMQPType *constructorType = new AMQPType(list->getTypeValue());
    AMQPDescribedConstructor *constructor = new AMQPDescribedConstructor(constructorType, fixed);

    list->setConstructor(constructor);
    return list;
}

AMQPSectionCode *AMQPMessageHeader::getCode()
{
    return new AMQPSectionCode(AMQP_HEADER_SECTION_CODE);
}

void AMQPMessageHeader::fill(TLVAMQP *value)
{
    AMQPTLVList *list = new AMQPTLVList();

    if (list->getList().size() > 0) {
        TLVAMQP *element = list->getList()[0];
        if (!element->isNull()) {
            this->durable = AMQPSimpleType::boolToVariant(AMQPUnwrapper::unwrapBool(element));
        }
    }
    if (list->getList().size() > 1) {
        TLVAMQP *element = list->getList()[1];
        if (!element->isNull()) {
            this->priority = AMQPSimpleType::UByteToVariant(AMQPUnwrapper::unwrapUByte(element));
        }
    }
    if (list->getList().size() > 2) {
        TLVAMQP *element = list->getList()[2];
        if (!element->isNull()) {
            this->milliseconds = AMQPSimpleType::UIntToVariant(AMQPUnwrapper::unwrapUInt(element));
        }
    }
    if (list->getList().size() > 3) {
        TLVAMQP *element = list->getList()[3];
        if (!element->isNull()) {
            this->firstAquirer = AMQPSimpleType::boolToVariant(AMQPUnwrapper::unwrapBool(element));
        }
    }
    if (list->getList().size() > 4) {
        TLVAMQP *element = list->getList()[4];
        if (!element->isNull()) {
            this->deliveryCount = AMQPSimpleType::UIntToVariant(AMQPUnwrapper::unwrapUInt(element));
        }
    }
}

JsonVariant *AMQPMessageHeader::getDurable() const
{
    return durable;
}

void AMQPMessageHeader::setDurable(JsonVariant *value)
{
    durable = value;
}

JsonVariant *AMQPMessageHeader::getPriority() const
{
    return priority;
}

void AMQPMessageHeader::setPriority(JsonVariant *value)
{
    priority = value;
}

JsonVariant *AMQPMessageHeader::getMilliseconds() const
{
    return milliseconds;
}

void AMQPMessageHeader::setMilliseconds(JsonVariant *value)
{
    milliseconds = value;
}

JsonVariant *AMQPMessageHeader::getFirstAquirer() const
{
    return firstAquirer;
}

void AMQPMessageHeader::setFirstAquirer(JsonVariant *value)
{
    firstAquirer = value;
}

JsonVariant *AMQPMessageHeader::getDeliveryCount() const
{
    return deliveryCount;
}

void AMQPMessageHeader::setDeliveryCount(JsonVariant *value)
{
    deliveryCount = value;
}
