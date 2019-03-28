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

#include "amqpsource.h"
#include "iot-protocols/amqp/classes/wrappers/amqpsymbol.h"
#include "iot-protocols/amqp/classes/constructors/amqpdescribedconstructor.h"
#include "iot-protocols/amqp/classes/tlv/api/amqptlvfactory.h"
#include "iot-protocols/amqp/classes/tlv/fixed/amqptlvfixed.h"
#include "iot-protocols/amqp/classes/headerapi/amqpwrapper.h"
#include "iot-protocols/amqp/classes/headerapi/amqpunwrapper.h"
#include "iot-protocols/amqp/classes/headerapi/amqpfactory.h"

AMQPSource::AMQPSource()
{
    this->expiryPeriod = NULL;
    this->distributionMode = NULL;
    this->defaultOutcome = NULL;
    this->dynamicNodeProperties = NULL;
    this->filter = NULL;
    this->outcomes = NULL;
    this->capabilities = NULL;
}

AMQPTLVList *AMQPSource::getList()
{
    AMQPTLVList *list = new AMQPTLVList();

    if (!this->address.isEmpty()) {
        list->addElementWithIndex(0, AMQPWrapper::wrapString(this->address));
    }
    if (this->durable != NULL) {
        list->addElementWithIndex(1, AMQPWrapper::wrapUInt(this->durable->getValue()));
    }
    if (this->expiryPeriod != NULL) {
        AMQPSymbol *symbol = new AMQPSymbol(this->expiryPeriod->getName());
        list->addElementWithIndex(2, AMQPWrapper::wrapSymbol(symbol));
    }
    if (this->timeout != NULL) {
        list->addElementWithIndex(3, AMQPWrapper::wrapUInt(this->timeout));
    }
    if (this->dynamic != NULL) {
        list->addElementWithIndex(4, AMQPWrapper::wrapBool(this->dynamic));
    }
    if (this->dynamicNodeProperties.count() != 0) {
        if (this->dynamic != NULL) {
            if ((bool) this->dynamic == true) {
                list->addElementWithIndex(5, AMQPWrapper::wrapMap(this->dynamicNodeProperties));
            } else {
                printf("AMQPSource::getList::dynamicNodeProperties");
            }
        } else {
            printf("AMQPSource::getList::dynamic");
        }
    }
    if (this->distributionMode != NULL) {
        AMQPSymbol *symbol = new AMQPSymbol(this->distributionMode->getName());
        list->addElementWithIndex(6, AMQPWrapper::wrapSymbol(symbol));
    }
    if (this->filter.count() != 0) {
        list->addElementWithIndex(7, AMQPWrapper::wrapMap(this->filter));
    }
    if (this->defaultOutcome != NULL) {
        list->addElementWithIndex(8, this->defaultOutcome->getList());
    }
    if (this->outcomes.count() != 0) {
        list->addElementWithIndex(9, AMQPWrapper::wrapArray(this->outcomes));
    }
    if (this->capabilities.count() != 0) {
        list->addElementWithIndex(9, AMQPWrapper::wrapList(this->capabilities));
    }

    unsigned char * data = NULL;
    data = malloc(sizeof(char));
    data[0] = (char) 0x28;
    AMQPType *type = new AMQPType(AMQP_SMALL_ULONG_TYPE);
    AMQPTLVFixed *fixed = new AMQPTLVFixed(type, data);

    AMQPType *constructorType = new AMQPType(list->getTypeValue());
    AMQPDescribedConstructor *constructor = new AMQPDescribedConstructor(constructorType, fixed);

    list->setConstructor(constructor);

    return list;
}

void AMQPSource::fill(AMQPTLVList *list)
{
    if (list->getList().size() > 0) {
        TLVAMQP *element = list->getList()[0];
        if (!element->isNull()) {
            this->address = AMQPUnwrapper::unwrapString(element);
        }
    }
    if (list->getList().size() > 1) {
        TLVAMQP *element = list->getList()[1];
        if (!element->isNull()) {
            int number = AMQPUnwrapper::unwrapUInt(element);
            this->durable = new AMQPTerminusDurability(number);
        }
    }
    if (list->getList().size() > 2) {
        TLVAMQP *element = list->getList()[2];
        if (!element->isNull()) {
            AMQPSymbol *symbol = AMQPUnwrapper::unwrapSymbol(element);
            AMQPTerminusExpiryPolicy *policy = new AMQPTerminusExpiryPolicy();
            policy = new AMQPTerminusExpiryPolicy(policy->EnumObject::getValue(symbol->getValue()));
            this->expiryPeriod = policy;
        }
    }
    if (list->getList().size() > 3) {
        TLVAMQP *element = list->getList()[3];
        if (!element->isNull()) {
            int number = AMQPUnwrapper::unwrapUInt(element);
            JsonVariant variant;
            variant.set(number);
            this->timeout = variant;
        }
    }
    if (list->getList().size() > 4) {
        TLVAMQP *element = list->getList()[4];
        if (!element->isNull()) {
            int number = AMQPUnwrapper::unwrapBool(element);
            JsonVariant variant;
            variant.set(number);
            this->dynamic = new variant(number);
        }
    }
    if (list->getList().size() > 5) {
        TLVAMQP *element = list->getList()[5];
        if (!element->isNull()) {
            if (this->dynamic != NULL) {
                if ((bool) this->dynamic) {
                    this->dynamicNodeProperties = AMQPUnwrapper::unwrapMap(element);
                } else {
                    printf("AMQPSource::fill::dynamicNodeProperties");
                }
            } else {
                printf("AMQPSource::fill::dynamic");
            }
        }
    }
    if (list->getList().size() > 6) {
        TLVAMQP *element = list->getList()[6];
        if (!element->isNull()) {
            AMQPSymbol *symbol = AMQPUnwrapper::unwrapSymbol(element);
            AMQPDistributionMode *mode = new AMQPDistributionMode();
            mode = new AMQPDistributionMode(mode->EnumObject::getValue(symbol->getValue()));
        }
    }
    if (list->getList().size() > 7) {
        TLVAMQP *element = list->getList()[7];
        if (!element->isNull()) {
            this->filter = AMQPUnwrapper::unwrapMap(element);
        }
    }
    if (list->getList().size() > 8) {
        TLVAMQP *element = list->getList()[8];
        if (!element->isNull()) {
            AMQPType *code = new AMQPType(element->getTypeValue());
            if (code->getValue() != AMQP_LIST0_TYPE && code->getValue() != AMQP_LIST8_TYPE && code->getValue() != AMQP_LIST32_TYPE) {
                printf("AMQPSource::fill::wrong_type");
            }
            this->defaultOutcome = AMQPFactory::outcome((AMQPTLVList *)element);
            this->defaultOutcome->fill((AMQPTLVList *)element);
        }
    }
    if (list->getList().size() > 9) {
        TLVAMQP *element = list->getList()[9];
        if (!element->isNull()) {
            this->outcomes = AMQPUnwrapper::unwrapArray(element);
        }
    }
    if (list->getList().size() > 10) {
        TLVAMQP *element = list->getList()[10];
        if (!element->isNull()) {
            this->capabilities = AMQPUnwrapper::unwrapList(element);
        }
    }
}

void AMQPSource::addDynamicNodeProperties(String key, JsonVariant *value)
{
    JsonVariant *keyVariant;
    keyVariant.set(AMQPSimpleType::symbolToVariant(new AMQPSymbol(key)));
    this->dynamicNodeProperties.insert(keyVariant, value);
}

void AMQPSource::addFilter(String key, JsonVariant *value)
{
    JsonVariant *keyVariant;
    keyVariant.set(AMQPSimpleType::symbolToVariant(new AMQPSymbol(key)));
    this->filter.insert(keyVariant, value);
}

void AMQPSource::addOutcomes(list<String> array)
{
    std::list<String *>::iterator it;
    for(it=array.begin(); it!=array.end(); ++it){
        JsonVariant *itemVariant;
        itemVariant.set(AMQPSimpleType::symbolToVariant(new AMQPSymbol(it)));
        this->outcomes.append(itemVariant);
    }
}

void AMQPSource::addCapabilities(list<String> array)
{
    std::list<String *>::iterator it;
    for(it=array.begin(); it!=array.end(); ++it){
        JsonVariant *itemVariant;
        itemVariant.set(AMQPSimpleType::symbolToVariant(new AMQPSymbol(it)));
        this->capabilities.append(itemVariant);
    }
}

String AMQPSource::getAddress() const
{
    return address;
}

void AMQPSource::setAddress(const String &value)
{
    address = value;
}

AMQPTerminusDurability *AMQPSource::getDurable() const
{
    return durable;
}

void AMQPSource::setDurable(AMQPTerminusDurability *value)
{
    durable = value;
}

AMQPTerminusExpiryPolicy *AMQPSource::getExpiryPeriod() const
{
    return expiryPeriod;
}

void AMQPSource::setExpiryPeriod(AMQPTerminusExpiryPolicy *value)
{
    expiryPeriod = value;
}

JsonVariant *AMQPSource::getTimeout() const
{
    return timeout;
}

void AMQPSource::setTimeout(JsonVariant *value)
{
    timeout = value;
}

JsonVariant *AMQPSource::getDynamic() const
{
    return dynamic;
}

void AMQPSource::setDynamic(JsonVariant *value)
{
    dynamic = value;
}

std::map<JsonVariant *, JsonVariant *> AMQPSource::getDynamicNodeProperties() const
{
    return dynamicNodeProperties;
}

void AMQPSource::setDynamicNodeProperties(const std::map<JsonVariant *, JsonVariant *> &value)
{
    dynamicNodeProperties = value;
}

AMQPDistributionMode *AMQPSource::getDistributionMode() const
{
    return distributionMode;
}

void AMQPSource::setDistributionMode(AMQPDistributionMode *value)
{
    distributionMode = value;
}

std::map<JsonVariant *, JsonVariant *> AMQPSource::getFilter() const
{
    return filter;
}

void AMQPSource::setFilter(const std::map<JsonVariant *, JsonVariant *> &value)
{
    filter = value;
}

AMQPOutcome *AMQPSource::getDefaultOutcome() const
{
    return defaultOutcome;
}

void AMQPSource::setDefaultOutcome(AMQPOutcome *value)
{
    defaultOutcome = value;
}

std::list<JsonVariant *> AMQPSource::getOutcomes() const
{
    return outcomes;
}

void AMQPSource::setOutcomes(const std::list<JsonVariant *> &value)
{
    outcomes = value;
}

std::list<JsonVariant *> AMQPSource::getCapabilities() const
{
    return capabilities;
}

void AMQPSource::setCapabilities(const std::list<JsonVariant *> &value)
{
    capabilities = value;
}
