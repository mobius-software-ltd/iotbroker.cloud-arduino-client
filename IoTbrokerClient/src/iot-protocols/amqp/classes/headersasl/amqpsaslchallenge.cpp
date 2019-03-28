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

#include "amqpsaslchallenge.h"
#include "iot-protocols/amqp/classes/constructors/amqpdescribedconstructor.h"
#include "iot-protocols/amqp/classes/headerapi/amqpwrapper.h"
#include "iot-protocols/amqp/classes/headerapi/amqpunwrapper.h"

AMQPSASLChallenge::AMQPSASLChallenge() : AMQPHeader(new AMQPHeaderCode(AMQP_CHALLENGE_HEADER_CODE))
{
    this->typeValue = 1;
}

int AMQPSASLChallenge::getLength()
{
    int length = 8;
    AMQPTLVList *arguments = this->arguments();
    length += arguments->getLength();
    return length;
}

int AMQPSASLChallenge::getType()
{
    return AMQP_CHALLENGE_HEADER_CODE;
}

AMQPTLVList *AMQPSASLChallenge::arguments()
{
    AMQPTLVList *list = new AMQPTLVList();

    if (this->challenge == NULL) {
        printf("AMQPSASLChallenge::arguments::challenge");
        return new AMQPTLVList();
    }

    list->addElementWithIndex(0, AMQPWrapper::wrapBinary(this->challenge));

    unsigned char * data = malloc(sizeof(char));
    data[0] = (char) 0x42;

    AMQPType *type = new AMQPType(AMQP_SMALL_ULONG_TYPE);
    AMQPTLVFixed *fixed = new AMQPTLVFixed(type, data);

    AMQPType *constructorType = new AMQPType(list->getTypeValue());
    AMQPDescribedConstructor *constructor = new AMQPDescribedConstructor(constructorType, fixed);

    list->setConstructor(constructor);
    return list;
}

void AMQPSASLChallenge::fillArguments(AMQPTLVList *list)
{
    int size = list->getList().size();

    if (size == 0) {
        printf("AMQPSASLChallenge::fillArguments::size == 0");
        return;
    }
    if (size > 1) {
        printf("AMQPSASLChallenge::fillArguments::wrong_size");
        return;
    }
    if (size > 0) {
        TLVAMQP *element = list->getList()[0];
        if (element->isNull() or element == NULL) {
            printf("AMQPSASLChallenge::fillArguments::challenge");
            return;
        }
        this->challenge = AMQPUnwrapper::unwrapBinary(element);
    }
}

unsigned char * AMQPSASLChallenge::getChallenge() const
{
    return challenge;
}

void AMQPSASLChallenge::setChallenge(const unsigned char &value)
{
    challenge = value;
}
