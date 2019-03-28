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

#include "amqpend.h"
#include "iot-protocols/amqp/classes/constructors/amqpdescribedconstructor.h"
#include "iot-protocols/amqp/classes/tlv/fixed/amqptlvfixed.h"
#include "iot-protocols/amqp/classes/tlv/fixed/amqptlvnull.h"

AMQPEnd::AMQPEnd() : AMQPHeader(new AMQPHeaderCode(AMQP_END_HEADER_CODE))
{
    this->error = NULL;
}

int AMQPEnd::getLength()
{
    int length = 8;
    AMQPTLVList *arguments = this->arguments();
    length += arguments->getLength();
    return length;
}

int AMQPEnd::getType()
{
    return AMQP_END_HEADER_CODE;
}

AMQPTLVList *AMQPEnd::arguments()
{
    AMQPTLVList *list = new AMQPTLVList();

    if (this->error != NULL) {
        list->addElementWithIndex(0, this->error->getList());
    } else {
        list->addElementWithIndex(0, new AMQPTLVNull());
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

void AMQPEnd::fillArguments(AMQPTLVList *list)
{
    if (list->getList().count() > 0) {
        TLVAMQP *element = list->getList().at(0);
        if (!element->isNull()) {
            if (element->getTypeValue() != AMQP_LIST0_TYPE && element->getTypeValue() != AMQP_LIST8_TYPE && element->getTypeValue() != AMQP_LIST32_TYPE) {
                printf("AMQPEnd::fillArguments");
                return;
            }
            this->error = new AMQPError();
            this->error->fill((AMQPTLVList *)element);
        }
    }
}

AMQPError *AMQPEnd::getError() const
{
    return error;
}

void AMQPEnd::setError(AMQPError *value)
{
    error = value;
}
