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

#include "amqpflow.h"
#include "iot-protocols/amqp/classes/constructors/amqpdescribedconstructor.h"
#include "iot-protocols/amqp/classes/headerapi/amqpwrapper.h"
#include "iot-protocols/amqp/classes/headerapi/amqpunwrapper.h"
#include "iot-protocols/amqp/classes/tlv/fixed/amqptlvfixed.h"
#include "iot-protocols/amqp/classes/tlv/fixed/amqptlvnull.h"
#include "iot-protocols/amqp/classes/amqpsimpletype.h"

AMQPFlow::AMQPFlow() : AMQPHeader(new AMQPHeaderCode(AMQP_FLOW_HEADER_CODE))
{
    this->nextIncomingId = NULL;
    this->incomingWindow = NULL;
    this->nextOutgoingId = NULL;
    this->outgoingWindow = NULL;
    this->handle = NULL;
    this->deliveryCount = NULL;
    this->linkCredit = NULL;
    this->avaliable = NULL;
    this->drain = NULL;
    this->echo = NULL;
    this->properties = NULL;
}

int AMQPFlow::getLength()
{
    int length = 8;
    AMQPTLVList *arguments = this->arguments();
    length += arguments->getLength();
    return length;
}

int AMQPFlow::getType()
{
    return AMQP_FLOW_HEADER_CODE;
}

AMQPTLVList *AMQPFlow::arguments()
{
    AMQPTLVList *list = new AMQPTLVList();

    if (this->nextIncomingId != NULL) {
        list->addElementWithIndex(0, AMQPWrapper::wrapUInt(AMQPSimpleType::variantToUInt(this->nextIncomingId)));
    }
    if (this->incomingWindow == NULL) {
        printf("AMQPFlow::arguments::incomingWindow");
        return new AMQPTLVList();
    }
    list->addElementWithIndex(1, AMQPWrapper::wrapUInt(AMQPSimpleType::variantToUInt(this->incomingWindow)));

    if (this->nextOutgoingId == NULL) {
        printf("AMQPFlow::arguments::nextOutgoingId");
        return new AMQPTLVList();
    }
    list->addElementWithIndex(2, AMQPWrapper::wrapUInt(AMQPSimpleType::variantToUInt(this->nextOutgoingId)));

    if (this->outgoingWindow == NULL) {
        printf("AMQPFlow::arguments::outgoingWindow");
        return new AMQPTLVList();
    }
    list->addElementWithIndex(3, AMQPWrapper::wrapUInt(AMQPSimpleType::variantToUInt(this->outgoingWindow)));

    if (this->handle != NULL) {
        list->addElementWithIndex(4, AMQPWrapper::wrapUInt(AMQPSimpleType::variantToUInt(this->handle)));
    }

    if (this->deliveryCount != NULL) {
        if (this->handle != NULL) {
            list->addElementWithIndex(5, AMQPWrapper::wrapUInt(AMQPSimpleType::variantToUInt(this->deliveryCount)));
        } else {
            printf("AMQPFlow::arguments::deliveryCount");
            return new AMQPTLVList();
        }
    }

    if (this->linkCredit != NULL) {
        if (this->handle != NULL) {
            list->addElementWithIndex(6, AMQPWrapper::wrapUInt(AMQPSimpleType::variantToUInt(this->linkCredit)));
        } else {
            printf("AMQPFlow::arguments::linkCredit");
            return new AMQPTLVList();
        }
    }

    if (this->avaliable != NULL) {
        if (this->handle != NULL) {
            list->addElementWithIndex(7, AMQPWrapper::wrapUInt(AMQPSimpleType::variantToUInt(this->avaliable)));
        } else {
            printf("AMQPFlow::arguments::avaliable");
            return new AMQPTLVList();
        }
    }

    if (this->drain != NULL) {
        if (this->handle != NULL) {
            list->addElementWithIndex(8, AMQPWrapper::wrapBool(AMQPSimpleType::variantToBool(this->drain)));
        } else {
            printf("AMQPFlow::arguments::drain");
            return new AMQPTLVList();
        }
    }

    if (this->echo != NULL) {
        list->addElementWithIndex(9, AMQPWrapper::wrapBool(AMQPSimpleType::variantToBool(this->echo)));
    }

    if (this->properties.count() != 0) {
        list->addElementWithIndex(10, AMQPWrapper::wrapMap(this->properties));
    }

    unsigned char * data = malloc(sizeof(char));
    data[0] = this->code->getValue();
    AMQPType *type = new AMQPType(AMQP_SMALL_ULONG_TYPE);
    AMQPTLVFixed *fixed = new AMQPTLVFixed(type, data);

    AMQPType *constructorType = new AMQPType(list->getTypeValue());
    AMQPDescribedConstructor *constructor = new AMQPDescribedConstructor(constructorType, fixed);

    list->setConstructor(constructor);
    return list;
}

void AMQPFlow::fillArguments(AMQPTLVList *list)
{
    int size = list->getList().count();

    if (size < 4) {
        printf("AMQPFlow::arguments::wrong_size");
    }
    if (size > 11) {
        printf("AMQPFlow::arguments::wrong_size");
    }
    if (size > 0) {
        TLVAMQP *element = list->getList()[0];
        if (!element->isNull()) {
            this->nextIncomingId = AMQPSimpleType::UIntToVariant(AMQPUnwrapper::unwrapUInt(element));
        }
    }
    if (size > 1) {
        TLVAMQP *element = list->getList()[1];
        if (element->isNull()) {
            printf("AMQPFlow::arguments::incomingWindow");
        }
        this->incomingWindow = AMQPSimpleType::UIntToVariant(AMQPUnwrapper::unwrapUInt(element));
    }
    if (size > 2) {
        TLVAMQP *element = list->getList()[2];
        if (element->isNull()) {
            printf("AMQPFlow::arguments::nextOutgoingId");
        }
        this->nextOutgoingId = AMQPSimpleType::UIntToVariant(AMQPUnwrapper::unwrapUInt(element));
    }
    if (size > 3) {
        TLVAMQP *element = list->getList()[3];
        if (element->isNull()) {
            printf("AMQPFlow::arguments::outgoingWindow");
        }
        this->outgoingWindow = AMQPSimpleType::UIntToVariant(AMQPUnwrapper::unwrapUInt(element));
    }
    if (size > 4) {
        TLVAMQP *element = list->getList()[4];
        if (!element->isNull()) {
            this->handle = AMQPSimpleType::UIntToVariant(AMQPUnwrapper::unwrapUInt(element));
        }
    }
    if (size > 5) {
        TLVAMQP *element = list->getList()[5];
        if (!element->isNull()) {
            if (this->handle != NULL) {
                this->deliveryCount = AMQPSimpleType::UIntToVariant(AMQPUnwrapper::unwrapUInt(element));
            } else {
                printf("AMQPFlow::arguments::deliveryCount");
            }
        }
    }
    if (size > 6) {
        TLVAMQP *element = list->getList()[6];
        if (!element->isNull()) {
            if (this->handle != NULL) {
                this->linkCredit = AMQPSimpleType::UIntToVariant(AMQPUnwrapper::unwrapUInt(element));
            } else {
                printf("AMQPFlow::arguments::linkCredit");
            }
        }
    }
    if (size > 7) {
        TLVAMQP *element = list->getList()[7];
        if (!element->isNull()) {
            if (this->handle != NULL) {
                this->avaliable = AMQPSimpleType::UIntToVariant(AMQPUnwrapper::unwrapUInt(element));
            } else {
                printf("AMQPFlow::arguments::avaliable");
            }
        }
    }
    if (size > 8) {
        TLVAMQP *element = list->getList()[8];
        if (!element->isNull()) {
            if (this->handle != NULL) {
                this->drain = AMQPSimpleType::boolToVariant(AMQPUnwrapper::unwrapBool(element));
            } else {
                printf("AMQPFlow::arguments::drain");
            }
        }
    }
    if (size > 9) {
        TLVAMQP *element = list->getList()[9];
        if (!element->isNull()) {
            this->echo = AMQPSimpleType::boolToVariant(AMQPUnwrapper::unwrapBool(element));
        }
    }
    if (size > 10) {
        TLVAMQP *element = list->getList()[10];
        if (!element->isNull()) {
            this->properties = AMQPUnwrapper::unwrapMap(element);
        }
    }
}

void AMQPFlow::addProperty(String key, JsonVariant *value)
{
    JsonVariant *variantKey;
    variantKey.set(AMQPSimpleType::symbolToVariant(new AMQPSymbol(key)));
    this->properties.insert(variantKey, value);
}

JsonVariant *AMQPFlow::getNextIncomingId() const
{
    return nextIncomingId;
}

void AMQPFlow::setNextIncomingId(JsonVariant *value)
{
    nextIncomingId = value;
}

JsonVariant *AMQPFlow::getIncomingWindow() const
{
    return incomingWindow;
}

void AMQPFlow::setIncomingWindow(JsonVariant *value)
{
    incomingWindow = value;
}

JsonVariant *AMQPFlow::getNextOutgoingId() const
{
    return nextOutgoingId;
}

void AMQPFlow::setNextOutgoingId(JsonVariant *value)
{
    nextOutgoingId = value;
}

JsonVariant *AMQPFlow::getOutgoingWindow() const
{
    return outgoingWindow;
}

void AMQPFlow::setOutgoingWindow(JsonVariant *value)
{
    outgoingWindow = value;
}

JsonVariant *AMQPFlow::getHandle() const
{
    return handle;
}

void AMQPFlow::setHandle(JsonVariant *value)
{
    handle = value;
}

JsonVariant *AMQPFlow::getDeliveryCount() const
{
    return deliveryCount;
}

void AMQPFlow::setDeliveryCount(JsonVariant *value)
{
    deliveryCount = value;
}

JsonVariant *AMQPFlow::getLinkCredit() const
{
    return linkCredit;
}

void AMQPFlow::setLinkCredit(JsonVariant *value)
{
    linkCredit = value;
}

JsonVariant *AMQPFlow::getAvaliable() const
{
    return avaliable;
}

void AMQPFlow::setAvaliable(JsonVariant *value)
{
    avaliable = value;
}

JsonVariant *AMQPFlow::getDrain() const
{
    return drain;
}

void AMQPFlow::setDrain(JsonVariant *value)
{
    drain = value;
}

JsonVariant *AMQPFlow::getEcho() const
{
    return echo;
}

void AMQPFlow::setEcho(JsonVariant *value)
{
    echo = value;
}

map<JsonVariant *, JsonVariant *> AMQPFlow::getProperties() const
{
    return properties;
}

void AMQPFlow::setProperties(const map<JsonVariant *, JsonVariant *> &value)
{
    properties = value;
}
