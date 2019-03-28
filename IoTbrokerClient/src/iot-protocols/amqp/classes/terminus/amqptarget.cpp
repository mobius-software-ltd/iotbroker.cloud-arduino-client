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

#include "amqptarget.h"
#include "iot-protocols/amqp/classes/wrappers/amqpsymbol.h"
#include "iot-protocols/amqp/classes/constructors/amqpdescribedconstructor.h"
#include "iot-protocols/amqp/classes/tlv/api/amqptlvfactory.h"
#include "iot-protocols/amqp/classes/tlv/fixed/amqptlvfixed.h"
#include "iot-protocols/amqp/classes/headerapi/amqpwrapper.h"
#include "iot-protocols/amqp/classes/headerapi/amqpunwrapper.h"
#include "iot-protocols/amqp/classes/headerapi/amqpfactory.h"

AMQPTarget::AMQPTarget()
{
    this->expiryPeriod = NULL;
    this->dynamicNodeProperties = NULL;
    this->capabilities = NULL;
}

AMQPTLVList *AMQPTarget::getlist()
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
            if ((bool) this->dynamic) {
                list->addElementWithIndex(5, AMQPWrapper::wrapMap(this->dynamicNodeProperties));
            } else {
                printf("AMQPTarget::getList::dynamic");
            }
        } else {
            printf("AMQPTarget::getList::dynamicNodeProperties");
        }
    }

    if (this->capabilities.count() != 0) {
        list->addElementWithIndex(6, AMQPWrapper::wrapList(this->capabilities));
    }
    unsigned char * data = NULL;
    data = malloc(sizeof(char));
    data[0] = (char) 0x29;
    AMQPType *type = new AMQPType(AMQP_SMALL_ULONG_TYPE);
    AMQPTLVFixed *fixed = new AMQPTLVFixed(type, data);

    AMQPType *constructorType = new AMQPType(list->getTypeValue());
    AMQPDescribedConstructor *constructor = new AMQPDescribedConstructor(constructorType, fixed);

    list->setConstructor(constructor);

    return list;
}

void AMQPTarget::fill(AMQPTLVList *list)
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
            AMQPTerminusExpiryPolicy *expiryPolicy = new AMQPTerminusExpiryPolicy();
            expiryPolicy = new AMQPTerminusExpiryPolicy(expiryPolicy->EnumObject::getValue(symbol->getValue()));
            this->expiryPeriod = expiryPolicy;
        }
    }
    if (list->getList().size() > 3) {
        TLVAMQP *element = list->getList()[3];
        if (!element->isNull()) {
            JsonVariant variant;
            variant.set((unsigned int)AMQPUnwrapper::unwrapUInt(element));
            this->timeout = variant;
        }
    }
    if (list->getList().size() > 4) {
        TLVAMQP *element = list->getList()[4];
        if (!element->isNull()) {
            JsonVariant variant;
            variant.set(AMQPUnwrapper::unwrapBool(element));
            this->dynamic = variant;
        }
    }
    if (list->getList().size() > 5) {
        TLVAMQP *element = list->getList()[5];
        if (!element->isNull()) {
            if (this->dynamic != NULL) {
                if ((bool)this->dynamic) {
                    this->dynamicNodeProperties = AMQPUnwrapper::unwrapMap(element);
                } else {
                    printf("AMQPTarget::fill::dynamic");
                }
            } else {
                printf("AMQPTarget::fill::dynamicNodeProperties");
            }
        }
    }
    if (list->getList().size() > 6) {
        TLVAMQP *element = list->getList()[6];
        if (!element->isNull()) {
            this->capabilities = AMQPUnwrapper::unwrapList(element);
        }
    }
}

void AMQPTarget::addDynamicNodeProperties(String key, JsonVariant *value)
{
    JsonVariant *keyVariant;
    keyVariant.set(AMQPSimpleType::symbolToVariant(new AMQPSymbol(key)));
    this->dynamicNodeProperties.insert(keyVariant, value);
}

void AMQPTarget::addCapabilities(list<String> array)
{
    foreach (String item, array) {
        JsonVariant *itemVariant;
        itemVariant.set(AMQPSimpleType::symbolToVariant(new AMQPSymbol(item)));
        this->capabilities.push_back(itemVariant);
    }
}

String AMQPTarget::getAddress() const
{
    return address;
}

void AMQPTarget::setAddress(const String &value)
{
    address = value;
}

AMQPTerminusDurability *AMQPTarget::getDurable() const
{
    return durable;
}

void AMQPTarget::setDurable(AMQPTerminusDurability *value)
{
    durable = value;
}

AMQPTerminusExpiryPolicy *AMQPTarget::getExpiryPeriod() const
{
    return expiryPeriod;
}

void AMQPTarget::setExpiryPeriod(AMQPTerminusExpiryPolicy *value)
{
    expiryPeriod = value;
}

JsonVariant *AMQPTarget::getTimeout() const
{
    return timeout;
}

void AMQPTarget::setTimeout(JsonVariant *value)
{
    timeout = value;
}

JsonVariant *AMQPTarget::getDynamic() const
{
    return dynamic;
}

void AMQPTarget::setDynamic(JsonVariant *value)
{
    dynamic = value;
}

map<JsonVariant *, JsonVariant *> AMQPTarget::getDynamicNodeProperties() const
{
    return dynamicNodeProperties;
}

void AMQPTarget::setDynamicNodeProperties(const map<JsonVariant *, JsonVariant *> &value)
{
    dynamicNodeProperties = value;
}

list<JsonVariant *> AMQPTarget::getCapabilities() const
{
    return capabilities;
}

void AMQPTarget::setCapabilities(const list<JsonVariant *> &value)
{
    capabilities = value;
}
