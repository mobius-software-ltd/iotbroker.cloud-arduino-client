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

#include "amqpsaslinit.h"
#include "iot-protocols/amqp/classes/constructors/amqpdescribedconstructor.h"
#include "iot-protocols/amqp/classes/headerapi/amqpwrapper.h"
#include "iot-protocols/amqp/classes/headerapi/amqpunwrapper.h"

AMQPSASLInit::AMQPSASLInit() : AMQPHeader(new AMQPHeaderCode(AMQP_INIT_HEADER_CODE))
{
    this->mechanism = NULL;
    this->typeValue = 1;
}

int AMQPSASLInit::getLength()
{
    int length = 8;
    AMQPTLVList *arguments = this->arguments();
    length += arguments->getLength();
    return length;
}

int AMQPSASLInit::getType()
{
    return AMQP_INIT_HEADER_CODE;
}

AMQPTLVList *AMQPSASLInit::arguments()
{
    AMQPTLVList *list = new AMQPTLVList();

    if (this->mechanism == NULL) {
        printf("AMQPSASLInit::arguments::mechanism");
        return new AMQPTLVList();
    }

    list->addElementWithIndex(0, AMQPWrapper::wrapSymbol(this->mechanism));

    if (this->initialResponse.getSize() != 0) {
        list->addElementWithIndex(1, AMQPWrapper::wrapBinary(this->initialResponse.getByteArray()));
    }
    if (!this->hostName.isNull() and this->hostName != "") {
        list->addElementWithIndex(2, AMQPWrapper::wrapString(this->hostName));
    }

    unsigned char * data = malloc(sizeof(char));
    data[0] = (char) 0x41;

    AMQPType *type = new AMQPType(AMQP_SMALL_ULONG_TYPE);
    AMQPTLVFixed *fixed = new AMQPTLVFixed(type, data);

    AMQPType *constructorType = new AMQPType(list->getTypeValue());
    AMQPDescribedConstructor *constructor = new AMQPDescribedConstructor(constructorType, fixed);

    list->setConstructor(constructor);
    return list;
}

void AMQPSASLInit::fillArguments(AMQPTLVList *list)
{
    int size = list->getList().size();

    if (size == 0) {
        printf("AMQPSASLInit::fillArguments::size == 0");
        return;
    }
    if (size > 3) {
        printf("AMQPSASLInit::fillArguments::wrong_size");
        return;
    }

    if (size > 0) {
        TLVAMQP *element = list->getList()[0];
        if (element->isNull()) {
            printf("AMQPSASLInit::fillArguments::mechanism");
            return;
        }
        this->mechanism = AMQPUnwrapper::unwrapSymbol(element);
    }
    if (size > 1) {
        TLVAMQP *element = list->getList()[1];
        if (!element->isNull()) {
            this->initialResponse = AMQPUnwrapper::unwrapBinary(element);
        }
    }
    if (size > 2) {
        TLVAMQP *element = list->getList()[2];
        if (!element->isNull()) {
            this->hostName = AMQPUnwrapper::unwrapString(element);
        }
    }
}


AMQPSymbol *AMQPSASLInit::getMechanism() const
{
    return mechanism;
}

void AMQPSASLInit::setMechanism(AMQPSymbol *value)
{
    mechanism = value;
}

unsigned char * AMQPSASLInit::getInitialResponse() const
{
    return initialResponse;
}

void AMQPSASLInit::setInitialResponse(const unsigned char &value)
{
    initialResponse = value;
}

String AMQPSASLInit::getHostName() const
{
    return hostName;
}

void AMQPSASLInit::setHostName(const String &value)
{
    hostName = value;
}
