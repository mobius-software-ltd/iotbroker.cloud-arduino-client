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

#include "amqpopen.h"
#include "iot-protocols/amqp/classes/constructors/amqpdescribedconstructor.h"
#include "iot-protocols/amqp/classes/headerapi/amqpwrapper.h"
#include "iot-protocols/amqp/classes/headerapi/amqpunwrapper.h"
#include "iot-protocols/amqp/classes/tlv/fixed/amqptlvfixed.h"
#include "iot-protocols/amqp/classes/tlv/fixed/amqptlvnull.h"
#include "iot-protocols/amqp/classes/amqpsimpletype.h"

AMQPOpen::AMQPOpen() : AMQPHeader(new AMQPHeaderCode(AMQP_OPEN_HEADER_CODE))
{
    this->maxFrameSize = NULL;
    this->channelMax = NULL;
    this->idleTimeout = NULL;
    this->outgoingLocales = list<JsonVariant *>();
    this->incomingLocales = list<JsonVariant *>();
    this->offeredCapabilities = list<JsonVariant *>();
    this->desiredCapabilities = list<JsonVariant *>();
    this->properties = map<JsonVariant *, JsonVariant *>();
}

int AMQPOpen::getLength()
{
    int length = 8;
    AMQPTLVList *arguments = this->arguments();
    length += arguments->getLength();
    return length;
}

int AMQPOpen::getType()
{
    return AMQP_OPEN_HEADER_CODE;
}

AMQPTLVList *AMQPOpen::arguments()
{
    AMQPTLVList *list = new AMQPTLVList();

    if (this->containerId == NULL) {
        printf("AMQPOpen::arguments::containerId");
        return new AMQPTLVList();
    }
    list->addElementWithIndex(0, AMQPWrapper::wrapString(this->containerId));

    if (this->hostname != NULL) {
        list->addElementWithIndex(1, AMQPWrapper::wrapString(this->hostname));
    }
    if (this->maxFrameSize != NULL) {
        list->addElementWithIndex(2, AMQPWrapper::wrapUInt(AMQPSimpleType::variantToUInt(this->maxFrameSize)));
    }
    if (this->channelMax != NULL) {
        list->addElementWithIndex(3, AMQPWrapper::wrapUShort(AMQPSimpleType::variantToUShort(this->channelMax)));
    }
    if (this->idleTimeout != NULL) {
        list->addElementWithIndex(4, AMQPWrapper::wrapUInt(AMQPSimpleType::variantToUInt(this->idleTimeout)));
    }
    if (this->outgoingLocales.count() != 0) {
        list->addElementWithIndex(5, AMQPWrapper::wrapArray(this->outgoingLocales));
    }
    if (this->incomingLocales.count() != 0) {
        list->addElementWithIndex(6, AMQPWrapper::wrapArray(this->incomingLocales));
    }
    if (this->offeredCapabilities.count() != 0) {
        list->addElementWithIndex(7, AMQPWrapper::wrapArray(this->offeredCapabilities));
    }
    if (this->desiredCapabilities.count() != 0) {
        list->addElementWithIndex(8, AMQPWrapper::wrapArray(this->desiredCapabilities));
    }
    if (this->properties.count() != 0) {
        list->addElementWithIndex(9, AMQPWrapper::wrapMap(this->properties));
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

void AMQPOpen::fillArguments(AMQPTLVList *list)
{
    int size = list->getList().count();

    if (size == 0) {
        printf("AMQPOpen::fillArguments::size == 0");
        return;
    }
    if (size > 10) {
        printf("AMQPOpen::fillArguments::wrong_type");
        return;
    }

    TLVAMQP *element = list->getList()[0];
    if (element->isNull()) {
        printf("AMQPOpen::fillArguments::containerId");
    }
    this->containerId = AMQPUnwrapper::unwrapString(element);

    if (size > 1) {
        element = list->getList()[1];
        if (!element->isNull()) {
            this->hostname = AMQPUnwrapper::unwrapString(element);
        }
    }
    if (size > 2) {
        element = list->getList()[2];
        if (!element->isNull()) {
            this->maxFrameSize = AMQPSimpleType::UIntToVariant(AMQPUnwrapper::unwrapUInt(element));
        }
    }
    if (size > 3) {
        element = list->getList()[3];
        if (!element->isNull()) {
            this->channelMax = AMQPSimpleType::UShortToVariant(AMQPUnwrapper::unwrapUShort(element));
        }
    }
    if (size > 4) {
        element = list->getList()[4];
        if (!element->isNull()) {
            this->idleTimeout = AMQPSimpleType::UIntToVariant(AMQPUnwrapper::unwrapUInt(element));
        }
    }
    if (size > 5) {
        element = list->getList()[5];
        if (!element->isNull()) {
            this->outgoingLocales = AMQPUnwrapper::unwrapArray(element);
        }
    }
    if (size > 6) {
        element = list->getList()[6];
        if (!element->isNull()) {
            this->incomingLocales = AMQPUnwrapper::unwrapArray(element);
        }
    }
    if (size > 7) {
        element = list->getList()[7];
        if (!element->isNull()) {
            this->offeredCapabilities = AMQPUnwrapper::unwrapArray(element);
        }
    }
    if (size > 8) {
        element = list->getList()[8];
        if (!element->isNull()) {
            this->desiredCapabilities = AMQPUnwrapper::unwrapArray(element);
        }
    }
    if (size > 9) {
        element = list->getList()[9];
        if (!element->isNull()) {
            this->properties = AMQPUnwrapper::unwrapMap(element);
        }
    }
}


void AMQPOpen::addOutgoingLocale(list<String> array)
{
    std::list<String>::iterator it;
    for (it = array.begin(); it != array.end(); ++it){
        JsonVariant *variant;
        variant.set(AMQPSimpleType::symbolToVariant(new AMQPSymbol(it)));
        this->outgoingLocales.push_back(variant);
    }
}

void AMQPOpen::addIncomingLocale(list<String> array)
{
    std::list<String>::iterator it;
    for (it = array.begin(); it != array.end(); ++it){
        JsonVariant *variant;
        variant.set(AMQPSimpleType::symbolToVariant(new AMQPSymbol(it)));
        this->incomingLocales.push_back(variant);
    }
}

void AMQPOpen::addOfferedCapability(list<String> array)
{
    std::list<String>::iterator it;
    for (it = array.begin(); it != array.end(); ++it){
        JsonVariant *variant;
        variant.set(AMQPSimpleType::symbolToVariant(new AMQPSymbol(it)));
        this->offeredCapabilities.push_back(variant);
    }
}

void AMQPOpen::addDesiredCapability(list<String> array)
{
    std::list<String>::iterator it;
    for (it = array.begin(); it != array.end(); ++it){
        JsonVariant *variant;
        variant.set(AMQPSimpleType::symbolToVariant(new AMQPSymbol(it)));
        this->desiredCapabilities.push_back(variant);
    }
}

void AMQPOpen::addProperty(String key, variant *value)
{
    JsonVariant *variantKey;
    variantKey.set(AMQPSimpleType::symbolToVariant(new AMQPSymbol(key)));
    this->properties.insert(variantKey, value);
}

String AMQPOpen::getContainerId() const
{
    return containerId;
}

void AMQPOpen::setContainerId(const String &value)
{
    containerId = value;
}

String AMQPOpen::getHostname() const
{
    return hostname;
}

void AMQPOpen::setHostname(const String &value)
{
    hostname = value;
}

JsonVariant *AMQPOpen::getMaxFrameSize() const
{
    return maxFrameSize;
}

void AMQPOpen::setMaxFrameSize(JsonVariant *value)
{
    maxFrameSize = value;
}

JsonVariant *AMQPOpen::getChannelMax() const
{
    return channelMax;
}

void AMQPOpen::setChannelMax(JsonVariant *value)
{
    channelMax = value;
}

JsonVariant *AMQPOpen::getIdleTimeout() const
{
    return idleTimeout;
}

void AMQPOpen::setIdleTimeout(JsonVariant *value)
{
    idleTimeout = value;
}

list<JsonVariant *> AMQPOpen::getOutgoingLocales() const
{
    return outgoingLocales;
}

void AMQPOpen::setOutgoingLocales(const list<JsonVariant *> &value)
{
    outgoingLocales = value;
}

list<JsonVariant *> AMQPOpen::getIncomingLocales() const
{
    return incomingLocales;
}

void AMQPOpen::setIncomingLocales(const list<JsonVariant *> &value)
{
    incomingLocales = value;
}

list<JsonVariant *> AMQPOpen::getOfferedCapabilities() const
{
    return offeredCapabilities;
}

void AMQPOpen::setOfferedCapabilities(const list<JsonVariant *> &value)
{
    offeredCapabilities = value;
}

list<JsonVariant *> AMQPOpen::getDesiredCapabilities() const
{
    return desiredCapabilities;
}

void AMQPOpen::setDesiredCapabilities(const list<JsonVariant *> &value)
{
    desiredCapabilities = value;
}

map<JsonVariant *, JsonVariant *> AMQPOpen::getProperties() const
{
    return properties;
}

void AMQPOpen::setProperties(const map<JsonVariant *, JsonVariant *> &value)
{
    properties = value;
}
