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

#include "amqpattach.h"
#include "iot-protocols/amqp/classes/amqpsimpletype.h"
#include "iot-protocols/amqp/classes/headerapi/amqpwrapper.h"
#include "iot-protocols/amqp/classes/headerapi/amqpunwrapper.h"
#include "iot-protocols/amqp/classes/constructors/amqpdescribedconstructor.h"

AMQPAttach::AMQPAttach() : AMQPHeader(new AMQPHeaderCode(AMQP_ATTACH_HEADER_CODE))
{
    this->handle = NULL;
    this->role = NULL;
    this->sendCodes = NULL;
    this->receivedCodes = NULL;
    this->source = NULL;
    this->target = NULL;
    this->incompleteUnsettled = NULL;
    this->initialDeliveryCount = NULL;
    this->maxMessageSize = NULL;
    this->unsettled = NULL;
    this->offeredCapabilities = NULL;
    this->desiredCapabilities = NULL;
    this->properties = NULL;
}

int AMQPAttach::getLength()
{
    int length = 8;
    AMQPTLVList *arguments = this->arguments();
    length += arguments->getLength();
    return length;
}

int AMQPAttach::getType()
{
    return AMQP_ATTACH_HEADER_CODE;
}

AMQPTLVList *AMQPAttach::arguments()
{
    AMQPTLVList *list = new AMQPTLVList();

    if (this->name.isNull()) {
        return new AMQPTLVList();
    }
    list->addElementWithIndex(0, AMQPWrapper::wrapString(this->name));

    if (this->handle == NULL) {
        return new AMQPTLVList();
    }
    list->addElementWithIndex(1, AMQPWrapper::wrapUInt(AMQPSimpleType::variantToUInt(this->handle)));

    if (this->role == NULL) {
        return new AMQPTLVList();
    }
    list->addElementWithIndex(2, AMQPWrapper::wrapBool(this->role->getValue()));

    if (this->sendCodes != NULL) {
        list->addElementWithIndex(3, AMQPWrapper::wrapUByte(this->sendCodes->getValue()));
    }

    if (this->receivedCodes != NULL) {
        list->addElementWithIndex(4, AMQPWrapper::wrapUByte(this->receivedCodes->getValue()));
    }

    if (this->source != NULL) {
        list->addElementWithIndex(5, this->source->getList());
    }

    if (this->target != NULL) {
        list->addElementWithIndex(6, this->target->getlist());
    }

    if (this->unsettled.count() != 0) {
        list->addElementWithIndex(7, AMQPWrapper::wrapMap(this->unsettled));
    }

    if (this->incompleteUnsettled != NULL) {
        list->addElementWithIndex(8, AMQPWrapper::wrapBool(AMQPSimpleType::variantToBool(this->incompleteUnsettled)));
    }

    if (this->initialDeliveryCount != NULL) {
        list->addElementWithIndex(9, AMQPWrapper::wrapUInt(AMQPSimpleType::variantToUInt(this->initialDeliveryCount)));
    } else if (this->role->getValue() == AMQP_SENDER_ROLE_CODE) {
        printf("AMQPAttach::arguments::initialDeliveryCount");
        return new AMQPTLVList();
    }

    if (this->maxMessageSize != NULL) {
        list->addElementWithIndex(10, AMQPWrapper::wrapULong(AMQPSimpleType::variantToULong(this->maxMessageSize)));
    }

    if (this->offeredCapabilities.count() != 0) {
        list->addElementWithIndex(11, AMQPWrapper::wrapArray(this->offeredCapabilities));
    }

    if (this->desiredCapabilities.count() != 0) {
        list->addElementWithIndex(12, AMQPWrapper::wrapArray(this->desiredCapabilities));
    }

    if (this->properties.count() != 0) {
        list->addElementWithIndex(13, AMQPWrapper::wrapMap(this->properties));
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

void AMQPAttach::fillArguments(AMQPTLVList *list)
{
    int size = list->getList().count();

    if (size < 3) {
        printf("AMQPAttach::fillArguments");
        return;
    }
    if (size > 14) {
        printf("AMQPAttach::fillArguments");
        return;
    }
    if (size > 0) {
        TLVAMQP *element = list->getList()[0];
        if (element->isNull()) {
            printf("AMQPAttach::fillArguments::name");
            return;
        }
        this->name = AMQPUnwrapper::unwrapString(element);
    }
    if (size > 1) {
        TLVAMQP *element = list->getList()[1];
        if (element->isNull()) {
            printf("AMQPAttach::fillArguments::handle");
            return;
        }
        this->handle = AMQPSimpleType::UIntToVariant(AMQPUnwrapper::unwrapUInt(element));
    }
    if (size > 2) {
        TLVAMQP *element = list->getList()[2];
        if (element->isNull()) {
            printf("AMQPAttach::fillArguments::role");
            return;
        }
        this->role = new AMQPRoleCode(AMQPUnwrapper::unwrapBool(element));
    }
    if (size > 3) {
        TLVAMQP *element = list->getList()[3];
        if (!element->isNull()) {
            this->sendCodes = new AMQPSendCode(AMQPUnwrapper::unwrapUByte(element));
        }
    }
    if (size > 4) {
        TLVAMQP *element = list->getList()[4];
        if (!element->isNull()) {
            this->receivedCodes = new AMQPReceiverSettleMode(AMQPUnwrapper::unwrapUByte(element));
        }
    }
    if (size > 5) {
        TLVAMQP *element = list->getList()[5];
        if (!element->isNull()) {
            if (element->getTypeValue() != AMQP_LIST0_TYPE && element->getTypeValue() != AMQP_LIST8_TYPE && element->getTypeValue() != AMQP_LIST32_TYPE) {
                printf("AMQPAttach::fillArguments::source");
                return;
            }
            this->source = new AMQPSource();
            this->source->fill((AMQPTLVList *)element);
        }
    }
    if (size > 6) {
        TLVAMQP *element = list->getList()[6];
        if (!element->isNull()) {
            if (element->getTypeValue() != AMQP_LIST0_TYPE && element->getTypeValue() != AMQP_LIST8_TYPE && element->getTypeValue() != AMQP_LIST32_TYPE) {
                printf("AMQPAttach::fillArguments::target");
                return;
            }
            this->target = new AMQPTarget();
            this->target->fill((AMQPTLVList *)element);
        }
    }
    if (size > 7) {
        TLVAMQP *element = list->getList()[7];
        if (!element->isNull()) {
            this->unsettled = AMQPUnwrapper::unwrapMap(element);
        }
    }
    if (size > 8) {
        TLVAMQP *element = list->getList()[8];
        if (!element->isNull()) {
            this->incompleteUnsettled = AMQPSimpleType::boolToVariant(AMQPUnwrapper::unwrapBool(element));
        }
    }
    if (size > 9) {
        TLVAMQP *element = list->getList()[9];
        if (!element->isNull()) {
            this->initialDeliveryCount = AMQPSimpleType::UIntToVariant(AMQPUnwrapper::unwrapUInt(element));
        } else {
            printf("AMQPAttach::fillArguments::initialDeliveryCount");
            return;
        }
    }
    if (size > 10) {
        TLVAMQP *element = list->getList()[10];
        if (!element->isNull()) {
            this->maxMessageSize = AMQPSimpleType::ULongToVariant(AMQPUnwrapper::unwrapULong(element));
        }
    }
    if (size > 11) {
        TLVAMQP *element = list->getList()[11];
        if (!element->isNull()) {
            this->offeredCapabilities = AMQPUnwrapper::unwrapArray(element);
        }
    }
    if (size > 12) {
        TLVAMQP *element = list->getList()[12];
        if (!element->isNull()) {
            this->desiredCapabilities = AMQPUnwrapper::unwrapArray(element);
        }
    }
    if (size > 13) {
        TLVAMQP *element = list->getList()[13];
        if (!element->isNull()) {
            this->properties = AMQPUnwrapper::unwrapMap(element);
        }
    }
}

void AMQPAttach::addUnsettled(String key, JsonVariant *value)
{
    JsonVariant *keyVariant = AMQPSimpleType::symbolToVariant(new AMQPSymbol(key));
    this->unsettled.insert(keyVariant, value);
}

void AMQPAttach::addOfferedCapability(list<String> array)
{
    std::list<String>::iterator it;
    for (it = array.begin(); it != array.end(); ++it){
        JsonVariant *itemVariant = AMQPSimpleType::symbolToVariant(new AMQPSymbol(it));
        this->offeredCapabilities.push_back(itemVariant);
    }
}

void AMQPAttach::addDesiredCapability(list<String> array)
{
    std::list<String>::iterator it;
    for (it = array.begin(); it != array.end(); ++it){
        JsonVariant *itemVariant = AMQPSimpleType::symbolToVariant(new AMQPSymbol(it));
        this->desiredCapabilities.push_back(itemVariant);
    }
}

void AMQPAttach::addProperty(String key, JsonVariant *value)
{
    JsonVariant *keyVariant = AMQPSimpleType::symbolToVariant(new AMQPSymbol(key));
    this->properties.insert(keyVariant, value);
}

String AMQPAttach::getName() const
{
    return name;
}

void AMQPAttach::setName(const String &value)
{
    name = value;
}

JsonVariant *AMQPAttach::getHandle() const
{
    return handle;
}

void AMQPAttach::setHandle(JsonVariant *value)
{
    handle = value;
}

AMQPRoleCode *AMQPAttach::getRole() const
{
    return role;
}

void AMQPAttach::setRole(AMQPRoleCode *value)
{
    role = value;
}

AMQPSendCode *AMQPAttach::getSendCodes() const
{
    return sendCodes;
}

void AMQPAttach::setSendCodes(AMQPSendCode *value)
{
    sendCodes = value;
}

AMQPReceiverSettleMode *AMQPAttach::getReceivedCodes() const
{
    return receivedCodes;
}

void AMQPAttach::setReceivedCodes(AMQPReceiverSettleMode *value)
{
    receivedCodes = value;
}

AMQPSource *AMQPAttach::getSource() const
{
    return source;
}

void AMQPAttach::setSource(AMQPSource *value)
{
    source = value;
}

AMQPTarget *AMQPAttach::getTarget() const
{
    return target;
}

void AMQPAttach::setTarget(AMQPTarget *value)
{
    target = value;
}

std::map<JsonVariant *, JsonVariant *> AMQPAttach::getUnsettled() const
{
    return unsettled;
}

void AMQPAttach::setUnsettled(const std::map<JsonVariant *, JsonVariant *> &value)
{
    unsettled = value;
}

JsonVariant *AMQPAttach::getIncompleteUnsettled() const
{
    return incompleteUnsettled;
}

void AMQPAttach::setIncompleteUnsettled(JsonVariant *value)
{
    incompleteUnsettled = value;
}

JsonVariant *AMQPAttach::getInitialDeliveryCount() const
{
    return initialDeliveryCount;
}

void AMQPAttach::setInitialDeliveryCount(JsonVariant *value)
{
    initialDeliveryCount = value;
}

JsonVariant *AMQPAttach::getMaxMessageSize() const
{
    return maxMessageSize;
}

void AMQPAttach::setMaxMessageSize(JsonVariant *value)
{
    maxMessageSize = value;
}

std::list<JsonVariant *> AMQPAttach::getOfferedCapabilities() const
{
    return offeredCapabilities;
}

void AMQPAttach::setOfferedCapabilities(const std::list<JsonVariant *> &value)
{
    offeredCapabilities = value;
}

std::list<JsonVariant *> AMQPAttach::getDesiredCapabilities() const
{
    return desiredCapabilities;
}

void AMQPAttach::setDesiredCapabilities(const std::list<JsonVariant *> &value)
{
    desiredCapabilities = value;
}

std::map<JsonVariant *, JsonVariant *> AMQPAttach::getProperties() const
{
    return properties;
}

void AMQPAttach::setProperties(const std::map<JsonVariant *, JsonVariant *> &value)
{
    properties = value;
}
