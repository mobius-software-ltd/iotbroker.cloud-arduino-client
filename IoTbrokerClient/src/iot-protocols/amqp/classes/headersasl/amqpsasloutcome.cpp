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

#include "amqpsasloutcome.h"
#include "iot-protocols/amqp/classes/constructors/amqpdescribedconstructor.h"
#include "iot-protocols/amqp/classes/headerapi/amqpwrapper.h"
#include "iot-protocols/amqp/classes/headerapi/amqpunwrapper.h"

AMQPSASLOutcome::AMQPSASLOutcome() : AMQPHeader(new AMQPHeaderCode(AMQP_OUTCOME_HEADER_CODE))
{
    this->outcomeCode = NULL;
    this->typeValue = 1;
}

int AMQPSASLOutcome::getLength()
{
    int length = 8;
    AMQPTLVList *arguments = this->arguments();
    length += arguments->getLength();
    return length;
}

int AMQPSASLOutcome::getType()
{
    return AMQP_OUTCOME_HEADER_CODE;
}

AMQPTLVList *AMQPSASLOutcome::arguments()
{
    AMQPTLVList *list = new AMQPTLVList();

    if (this->outcomeCode == NULL) {
        printf("AMQPSASLOutcome::arguments::mechanism");
        return new AMQPTLVList();
    }
    list->addElementWithIndex(0, AMQPWrapper::wrapUByte(this->outcomeCode->getValue()));

    if (!this->additionalData.getByteArray().isNull()) {
        list->addElementWithIndex(1, AMQPWrapper::wrapBinary(this->additionalData));
    }

    unsigned char * data = malloc(sizeof(char));
    data[0] = (char) 0x44;

    AMQPType *type = new AMQPType(AMQP_SMALL_ULONG_TYPE);
    AMQPTLVFixed *fixed = new AMQPTLVFixed(type, data);

    AMQPType *constructorType = new AMQPType(list->getTypeValue());
    AMQPDescribedConstructor *constructor = new AMQPDescribedConstructor(constructorType, fixed);

    list->setConstructor(constructor);
    return list;
}

void AMQPSASLOutcome::fillArguments(AMQPTLVList *list)
{
    int size = list->getList().size();

    if (size == 0) {
        printf("AMQPSASLOutcome::fillArguments::size == 0");
        return;
    }
    if (size > 2) {
        printf("AMQPSASLOutcome::fillArguments::wrong_size");
        return;
    }
    if (size > 0) {
        TLVAMQP *element = list->getList()[0];
        if (element->isNull()) {
            printf("AMQPSASLOutcome::fillArguments::outcomeCode");
            return;
        }
        this->outcomeCode = new AMQPSASLCode(AMQPUnwrapper::unwrapUByte(element));
    }
    if (size > 1) {
        TLVAMQP *element = list->getList()[1];
        if (!element->isNull()) {
            this->additionalData = ByteArray(AMQPUnwrapper::unwrapBinary(element));
        }
    }
}

AMQPSASLCode *AMQPSASLOutcome::getOutcomeCode() const
{
    return outcomeCode;
}

void AMQPSASLOutcome::setOutcomeCode(AMQPSASLCode *value)
{
    outcomeCode = value;
}

unsigned char * AMQPSASLOutcome::getAdditionalData() const
{
    return additionalData;
}

void AMQPSASLOutcome::setAdditionalData(const unsigned char &value)
{
    additionalData = value;
}
