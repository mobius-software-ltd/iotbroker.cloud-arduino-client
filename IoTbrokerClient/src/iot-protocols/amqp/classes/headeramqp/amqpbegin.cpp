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

#include "amqpbegin.h"
#include "iot-protocols/amqp/classes/constructors/amqpdescribedconstructor.h"
#include "iot-protocols/amqp/classes/headerapi/amqpwrapper.h"
#include "iot-protocols/amqp/classes/headerapi/amqpunwrapper.h"
#include "iot-protocols/amqp/classes/tlv/fixed/amqptlvfixed.h"
#include "iot-protocols/amqp/classes/tlv/fixed/amqptlvnull.h"
#include "iot-protocols/amqp/classes/amqpsimpletype.h"

AMQPBegin::AMQPBegin() : AMQPHeader(new AMQPHeaderCode(AMQP_BEGIN_HEADER_CODE))
{
    this->remoteChannel = NULL;
    this->nextOutgoingID = NULL;
    this->incomingWindow = NULL;
    this->outgoingWindow = NULL;
    this->handleMax = NULL;
    this->offeredCapabilities =  NULL;
    this->desiredCapabilities =  NULL;
    this->properties =  NULL;
}

int AMQPBegin::getLength()
{
    int length = 8;
    AMQPTLVList *arguments = this->arguments();
    length += arguments->getLength();
    return length;
}

int AMQPBegin::getType()
{
    return AMQP_BEGIN_HEADER_CODE;
}

AMQPTLVList *AMQPBegin::arguments()
{
    AMQPTLVList *list = new AMQPTLVList();

    if (this->remoteChannel != NULL) {
        list->addElementWithIndex(0, AMQPWrapper::wrapUShort(AMQPSimpleType::variantToUShort(this->remoteChannel)));
    }
    if (this->nextOutgoingID == NULL) {
        return new AMQPTLVList();
    }
    list->addElementWithIndex(1, AMQPWrapper::wrapUInt(AMQPSimpleType::variantToUInt(this->nextOutgoingID)));

    if (this->incomingWindow == NULL) {
        return new AMQPTLVList();
    }
    list->addElementWithIndex(2, AMQPWrapper::wrapUInt(AMQPSimpleType::variantToUInt(this->incomingWindow)));

    if (this->outgoingWindow == NULL) {
        return new AMQPTLVList();
    }
    list->addElementWithIndex(3, AMQPWrapper::wrapUInt(AMQPSimpleType::variantToUInt(this->outgoingWindow)));

    if (this->handleMax != NULL) {
        list->addElementWithIndex(4, AMQPWrapper::wrapUInt(AMQPSimpleType::variantToUInt(this->handleMax)));
    }
    if (this->offeredCapabilities.count() != 0) {
        list->addElementWithIndex(5, AMQPWrapper::wrapArray(this->offeredCapabilities));
    }
    if (this->desiredCapabilities.count() != 0) {
        list->addElementWithIndex(6, AMQPWrapper::wrapArray(this->desiredCapabilities));
    }
    if (this->properties.count() != 0) {
        list->addElementWithIndex(7, AMQPWrapper::wrapMap(this->properties));
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

void AMQPBegin::fillArguments(AMQPTLVList *list)
{
    int size = list->getList().count();

    if (size < 4) {
        printf("AMQPBegin::fillArguments::size == 0");
        return;
    }
    if (size > 8) {
        printf("AMQPBegin::fillArguments::wrong_size");
        return;
    }
    if (size > 0) {
        TLVAMQP *element = list->getList()[0];
        if (!element->isNull()) {
            this->remoteChannel = AMQPSimpleType::UShortToVariant(AMQPUnwrapper::unwrapUShort(element));
        }
    }
    if (size > 1) {
        TLVAMQP *element = list->getList()[1];
        if (element->isNull()) {
            printf("AMQPBegin::fillArguments::nextOutgoingID");
        }
        this->nextOutgoingID = AMQPSimpleType::UIntToVariant(AMQPUnwrapper::unwrapUInt(element));
    }
    if (size > 2) {
        TLVAMQP *element = list->getList()[2];
        if (element->isNull()) {
            printf("AMQPBegin::fillArguments::incomingWindow");
        }
        this->incomingWindow = AMQPSimpleType::UIntToVariant(AMQPUnwrapper::unwrapUInt(element));
    }
    if (size > 3) {
        TLVAMQP *element = list->getList()[3];
        if (element->isNull()) {
            printf("AMQPBegin::fillArguments::outgoingWindow");
        }
        this->outgoingWindow = AMQPSimpleType::UIntToVariant(AMQPUnwrapper::unwrapUInt(element));
    }
    if (size > 4) {
        TLVAMQP *element = list->getList().[4];
        if (!element->isNull()) {
            this->handleMax = AMQPSimpleType::UIntToVariant(AMQPUnwrapper::unwrapUInt(element));
        }
    }
    if (size > 5) {
        TLVAMQP *element = list->getList()[5];
        if (!element->isNull()) {
            this->offeredCapabilities = AMQPUnwrapper::unwrapArray(element);
        }
    }
    if (size > 6) {
        TLVAMQP *element = list->getList()[6];
        if (!element->isNull()) {
            this->desiredCapabilities = AMQPUnwrapper::unwrapArray(element);
        }
    }
    if (size > 7) {
        TLVAMQP *element = list->getList()[7];
        if (!element->isNull()) {
            this->properties = AMQPUnwrapper::unwrapMap(element);
        }
    }
}

void AMQPBegin::addOfferedCapability(list<String> list)
{
    std::list<String>::iterator it;
    for (it = array.begin(); it != array.end(); ++it){
        JsonVariant *variant = AMQPSimpleType::symbolToVariant(new AMQPSymbol(it));
        this->offeredCapabilities.push_back(variant);
    }
}

void AMQPBegin::addDesiredCapability(list<String> list)
{
    std::list<String>::iterator it;
    for (it = array.begin(); it != array.end(); ++it){
        JsonVariant *variant = AMQPSimpleType::symbolToVariant(new AMQPSymbol(it));
        this->desiredCapabilities.push_back(variant);
    }
}

void AMQPBegin::addProperty(String key, variant *value)
{
    JsonVariant *variantKey = AMQPSimpleType::symbolToVariant(new AMQPSymbol(key));
    this->properties.insert(variantKey, value);
}

JsonVariant *AMQPBegin::getRemoteChannel() const
{
    return remoteChannel;
}

void AMQPBegin::setRemoteChannel(JsonVariant *value)
{
    remoteChannel = value;
}

JsonVariant *AMQPBegin::getNextOutgoingID() const
{
    return nextOutgoingID;
}

void AMQPBegin::setNextOutgoingID(JsonVariant *value)
{
    nextOutgoingID = value;
}

JsonVariant *AMQPBegin::getIncomingWindow() const
{
    return incomingWindow;
}

void AMQPBegin::setIncomingWindow(JsonVariant *value)
{
    incomingWindow = value;
}

JsonVariant *AMQPBegin::getOutgoingWindow() const
{
    return outgoingWindow;
}

void AMQPBegin::setOutgoingWindow(JsonVariant *value)
{
    outgoingWindow = value;
}

JsonVariant *AMQPBegin::getHandleMax() const
{
    return handleMax;
}

void AMQPBegin::setHandleMax(JsonVariant *value)
{
    handleMax = value;
}

list<JsonVariant *> AMQPBegin::getOfferedCapabilities() const
{
    return offeredCapabilities;
}

void AMQPBegin::setOfferedCapabilities(const list<JsonVariant *> &value)
{
    offeredCapabilities = value;
}

list<JsonVariant *> AMQPBegin::getDesiredCapabilities() const
{
    return desiredCapabilities;
}

void AMQPBegin::setDesiredCapabilities(const list<JsonVariant *> &value)
{
    desiredCapabilities = value;
}

map<JsonVariant *, JsonVariant *> AMQPBegin::getProperties() const
{
    return properties;
}

void AMQPBegin::setProperties(const map<JsonVariant *, JsonVariant *> &value)
{
    properties = value;
}
