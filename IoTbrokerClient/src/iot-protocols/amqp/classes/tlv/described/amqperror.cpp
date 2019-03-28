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

#include "amqperror.h"
#include "iot-protocols/amqp/classes/headerapi/amqpunwrapper.h"
#include "iot-protocols/amqp/classes/headerapi/amqpwrapper.h"
#include "iot-protocols/amqp/classes/constructors/amqpdescribedconstructor.h"

AMQPError::AMQPError()
{
    this->condition = new AMQPErrorCode();
    this->descriptionString;
    this->info = map<JsonVariant *, JsonVariant *>();
}

void AMQPError::fill(AMQPTLVList *list)
{
    if (list->getList().size() > 0) {
        TLVAMQP *element = list->getList()[0];
        if (!element->isNull()) {
            String name = AMQPUnwrapper::unwrapSymbol(element)->getValue();
            this->condition = new AMQPErrorCode(this->condition->EnumObject::getValue(name));
        }
    }

    if (list->getList().size() > 1) {
        TLVAMQP *element = list->getList()[1];
        if (!element->isNull()) {
            this->descriptionString = AMQPUnwrapper::unwrapString(element);
        }
    }

    if (list->getList().size() > 2) {
        TLVAMQP *element = list->getList()[2];
        if (!element->isNull()) {
            this->info = AMQPUnwrapper::unwrapMap(element);
        }
    }
}

void AMQPError::addInfo(String key, JsonVariant *value)
{
    JsonVariant *keyVariant;
    keyVariant.set(AMQPSimpleType::symbolToVariant(new AMQPSymbol(key)));
    this->info.insert(keyVariant, value);
}

AMQPTLVList *AMQPError::getList()
{
    AMQPTLVList *list = new AMQPTLVList();

    if (this->condition != NULL) {
        JsonVariant *symbol;
        symbol.set(AMQPSimpleType::symbolToVariant(new AMQPSymbol(this->condition->getName())));
        list->addElementWithIndex(0, AMQPWrapper::wrapObject(symbol));
    }
    if (!this->descriptionString.isNull()) {
        list->addElementWithIndex(1, AMQPWrapper::wrapString(this->descriptionString));
    }
    if (this->info.count() != 0) {
        list->addElementWithIndex(2, AMQPWrapper::wrapMap(this->info));
    }

    AMQPType *type = new AMQPType(AMQP_SMALL_ULONG_TYPE);

    unsigned char * data;
    data = malloc(sizeof(char));
    data[0] = (char) 0x1D;

    AMQPTLVFixed *fixed = new AMQPTLVFixed(type, data);
    AMQPType *constructorType = new AMQPType(list->getTypeValue());
    AMQPDescribedConstructor *constructor = new AMQPDescribedConstructor(constructorType, fixed);
    list->setConstructor(constructor);

    return list;
}

AMQPErrorCode *AMQPError::getCondition() const
{
    return condition;
}

void AMQPError::setCondition(AMQPErrorCode *value)
{
    condition = value;
}

String AMQPError::getDescriptionString() const
{
    return descriptionString;
}

void AMQPError::setDescriptionString(const String &value)
{
    descriptionString = value;
}

map<JsonVariant *, JsonVariant *> AMQPError::getInfo() const
{
    return info;
}
