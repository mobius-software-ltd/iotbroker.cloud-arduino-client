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

#include "amqpsaslmechanisms.h"
#include "iot-protocols/amqp/classes/constructors/amqpdescribedconstructor.h"
#include "iot-protocols/amqp/classes/headerapi/amqpwrapper.h"
#include "iot-protocols/amqp/classes/headerapi/amqpunwrapper.h"

AMQPSASLMechanisms::AMQPSASLMechanisms() : AMQPHeader(new AMQPHeaderCode(AMQP_MECHANISMS_HEADER_CODE))
{
    this->mechanisms = NULL;
    this->typeValue = 1;
}

int AMQPSASLMechanisms::getLength()
{
    int length = 8;
    AMQPTLVList *arguments = this->arguments();
    length += arguments->getLength();
    return length;
}

int AMQPSASLMechanisms::getType()
{
    return AMQP_MECHANISMS_HEADER_CODE;
}

AMQPTLVList *AMQPSASLMechanisms::arguments()
{
    AMQPTLVList *list = new AMQPTLVList();

    if (this->mechanisms.count() == 0) {
        printf("AMQPSASLMechanisms::arguments::mechanisms");
        return new AMQPTLVList();
    }

    list->addElementWithIndex(0, AMQPWrapper::wrapArray(this->mechanisms));

    unsigned char * data = malloc(sizeof(char));
    data[0] = (char) 0x40;

    AMQPType *type = new AMQPType(AMQP_SMALL_ULONG_TYPE);
    AMQPTLVFixed *fixed = new AMQPTLVFixed(type, data);

    AMQPType *constructorType = new AMQPType(list->getTypeValue());
    AMQPDescribedConstructor *constructor = new AMQPDescribedConstructor(constructorType, fixed);

    list->setConstructor(constructor);
    return list;
}

void AMQPSASLMechanisms::fillArguments(AMQPTLVList *list)
{
    if (list->getList().size() > 0) {
        TLVAMQP *element = list->getList().at(0);
        if (!element->isNull()) {
            this->mechanisms = AMQPUnwrapper::unwrapArray(element);
        }
    }
}

void AMQPSASLMechanisms::addMechanism(String value)
{
    JsonVariant *variant = AMQPSimpleType::symbolToVariant(new AMQPSymbol(value));
    this->mechanisms.append(variant);
}



list<JsonVariant *> AMQPSASLMechanisms::getMechanisms() const
{
    return mechanisms;
}

void AMQPSASLMechanisms::setMechanisms(const list<JsonVariant *> &value)
{
    mechanisms = value;
}
