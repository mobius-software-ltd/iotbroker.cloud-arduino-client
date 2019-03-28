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

#include "amqpvalue.h"
#include "iot-protocols/amqp/classes/headerapi/amqpwrapper.h"
#include "iot-protocols/amqp/classes/headerapi/amqpunwrapper.h"
#include "iot-protocols/amqp/classes/constructors/amqpdescribedconstructor.h"

AMQPValue::AMQPValue()
{

}

TLVAMQP *AMQPValue::getValue()
{
    TLVAMQP *value = this->valueObject != NULL ? AMQPWrapper::wrapObject(this->valueObject) : new AMQPTLVNull();

    unsigned char * data = NULL;
    data = malloc(sizeof(char));
    data[0] = (char) 0x77;
    AMQPType *type = new AMQPType(AMQP_SMALL_ULONG_TYPE);
    AMQPTLVFixed *fixed = new AMQPTLVFixed(type, data);

    AMQPType *constructorType = new AMQPType(value->getTypeValue());
    AMQPDescribedConstructor *constructor = new AMQPDescribedConstructor(constructorType, fixed);

    value->setConstructor(constructor);
    return value;
}

AMQPSectionCode *AMQPValue::getCode()
{
    return new AMQPSectionCode(AMQP_VALUE_SECTION_CODE);
}

void AMQPValue::fill(TLVAMQP *value)
{
    if (value->isNull()) {
        this->valueObject = AMQPUnwrapper::unwrap(value);
    }
}

JsonVariant *AMQPValue::getValueObject() const
{
    return valueObject;
}

void AMQPValue::setValueObject(JsonVariant *value)
{
    valueObject = value;
}
