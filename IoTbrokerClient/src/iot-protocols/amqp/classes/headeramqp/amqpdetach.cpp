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

#include "amqpdetach.h"
#include "iot-protocols/amqp/classes/constructors/amqpdescribedconstructor.h"
#include "iot-protocols/amqp/classes/tlv/fixed/amqptlvfixed.h"
#include "iot-protocols/amqp/classes/tlv/fixed/amqptlvnull.h"
#include "iot-protocols/amqp/classes/headerapi/amqpwrapper.h"
#include "iot-protocols/amqp/classes/headerapi/amqpunwrapper.h"

AMQPDetach::AMQPDetach() : AMQPHeader(new AMQPHeaderCode(AMQP_DETACH_HEADER_CODE))
{
    this->handle = NULL;
    this->closed = NULL;
    this->error = NULL;
}

int AMQPDetach::getLength()
{
    int length = 8;
    AMQPTLVList *arguments = this->arguments();
    length += arguments->getLength();
    return length;
}

int AMQPDetach::getType()
{
    return AMQP_DETACH_HEADER_CODE;
}

AMQPTLVList *AMQPDetach::arguments()
{
    AMQPTLVList *list = new AMQPTLVList();

    if (this->handle == NULL) {
        printf("AMQPDetach::arguments");
        return new AMQPTLVList();
    }
    list->addElementWithIndex(0, AMQPWrapper::wrapUInt(AMQPSimpleType::variantToUInt(this->handle)));

    if (this->closed != NULL) {
        list->addElementWithIndex(1, AMQPWrapper::wrapBool(AMQPSimpleType::variantToBool(this->closed)));
    }
    if (this->error != NULL) {
        list->addElementWithIndex(2, this->error->getList());
    }

    unsigned char * data = (unsigned char *) malloc(sizeof(unsigned char *));
    data[0] = this->code->getValue();
    AMQPType *type = new AMQPType(AMQP_SMALL_ULONG_TYPE);
    AMQPTLVFixed *fixed = new AMQPTLVFixed(type, data);

    AMQPType *constructorType = new AMQPType(list->getTypeValue());
    AMQPDescribedConstructor *constructor = new AMQPDescribedConstructor(constructorType, fixed);

    list->setConstructor(constructor);
    return list;
}

void AMQPDetach::fillArguments(AMQPTLVList *list)
{
    int size = list->getList().size();

    if (size == 0) {
        printf("AMQPDetach::fillArguments::size == 0");
        return;
    }
    if (size > 3) {
        printf("AMQPDetach::fillArguments::wrong size");
        return;
    }
    if (size > 0) {
        TLVAMQP *element = list->getList()[0];
        if (element->isNull()) {
            printf("AMQPDetach::fillArguments::handle");
            return;
        }
        this->handle = AMQPSimpleType::UIntToVariant(AMQPUnwrapper::unwrapUInt(element));
    }
    if (size > 1) {
        TLVAMQP *element = list->getList()[1];
        if (!element->isNull()) {
            this->closed = AMQPSimpleType::boolToVariant(AMQPUnwrapper::unwrapBool(element));
        }
    }
    if (size > 2) {
        TLVAMQP *element = list->getList()[2];
        if (!element->isNull()) {
            if (element->getTypeValue() != AMQP_LIST0_TYPE && element->getTypeValue() != AMQP_LIST8_TYPE && element->getTypeValue() != AMQP_LIST32_TYPE) {
                printf("AMQPDetach::fillArguments::wrong element type");
                return;
            }
            this->error = new AMQPError();
            this->error->fill((AMQPTLVList *)element);
        }
    }
}

JsonVariant *AMQPDetach::getHandle() const
{
    return handle;
}

void AMQPDetach::setHandle(JsonVariant *value)
{
    handle = value;
}

JsonVariant *AMQPDetach::getClosed() const
{
    return closed;
}

void AMQPDetach::setClosed(JsonVariant *value)
{
    closed = value;
}

AMQPError *AMQPDetach::getError() const
{
    return error;
}

void AMQPDetach::setError(AMQPError *value)
{
    error = value;
}
