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

#include "amqpmodified.h"
#include "iot-protocols/amqp/classes/headerapi/amqpunwrapper.h"
#include "iot-protocols/amqp/classes/headerapi/amqpwrapper.h"
#include "iot-protocols/amqp/classes/constructors/amqpdescribedconstructor.h"

AMQPModified::AMQPModified()
{
    this->messageAnnotations = map<JsonVariant *, JsonVariant *>();
}

void AMQPModified::fill(AMQPTLVList *list)
{
    if (list->getList().size() > 0) {
        TLVAMQP *element = list->getList()[0];
        if (!element->isNull()) {
            JsonVariant variant;
            variant.set(AMQPUnwrapper::unwrapBool(element));
            this->deliveryFailed = variant;
        }
    }
    if (list->getList().size() > 1) {
        TLVAMQP *element = list->getList()[1];
        if (!element->isNull()) {
            JsonVariant variant;
            variant.set(AMQPUnwrapper::unwrapBool(element));
            this->undeliverableHere = variant;
        }
    }
    if (list->getList().size() > 2) {
        TLVAMQP *element = list->getList()[2];
        if (!element->isNull()) {
            this->messageAnnotations = AMQPUnwrapper::unwrapMap(element);
        }
    }
}

AMQPTLVList *AMQPModified::getList()
{
    AMQPTLVList *list = new AMQPTLVList();

    if (this->deliveryFailed != NULL) {
        list->addElementWithIndex(0, AMQPWrapper::wrapBool(this->deliveryFailed));
    }
    if (this->undeliverableHere != NULL) {
        list->addElementWithIndex(1, AMQPWrapper::wrapBool(this->undeliverableHere));
    }
    if (this->messageAnnotations.count() != 0) {
        list->addElementWithIndex(2, AMQPWrapper::wrapMap(this->messageAnnotations));
    }

    unsigned char * data;
    data = malloc(sizeof(char));
    data[0] = (char) 0x27;

    AMQPType *type = new AMQPType(AMQP_SMALL_ULONG_TYPE);
    AMQPTLVFixed *fixed = new AMQPTLVFixed(type, data);

    AMQPType *constructorType = new AMQPType(list->getTypeValue());
    AMQPDescribedConstructor *constructor = new AMQPDescribedConstructor(constructorType, fixed);

    list->setConstructor(constructor);

    return list;
}

void AMQPModified::addMessageAnnotation(String key, JsonVariant *value)
{
    if (strlen(key) < 2) {
        return;
    }

    String suffix = key.mid(0, 2);
    if (!suffix.compareTo("x-")) {
        printf("AMQPModified::addMessageAnnotation");
        return;
    }

    JsonVariant keyVariant;
    keyVariant.set(AMQPSimpleType::symbolToVariant(new AMQPSymbol(key)));
    this->messageAnnotations.insert(keyVariant, value);
}

JsonVariant *AMQPModified::getDeliveryFailed() const
{
    return deliveryFailed;
}

void AMQPModified::setDeliveryFailed(JsonVariant *value)
{
    deliveryFailed = value;
}

JsonVariant *AMQPModified::getUndeliverableHere() const
{
    return undeliverableHere;
}

void AMQPModified::setUndeliverableHere(JsonVariant *value)
{
    undeliverableHere = value;
}

map<JsonVariant *, JsonVariant *> AMQPModified::getMessageAnnotations() const
{
    return messageAnnotations;
}

void AMQPModified::setMessageAnnotations(const map<JsonVariant *, JsonVariant *> &value)
{
    messageAnnotations = value;
}
