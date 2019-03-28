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

#include "amqpdata.h"
#include "iot-protocols/amqp/classes/constructors/amqpdescribedconstructor.h"
#include "iot-protocols/amqp/classes/tlv/fixed/amqptlvfixed.h"
#include "iot-protocols/amqp/classes/tlv/fixed/amqptlvnull.h"
#include "iot-protocols/amqp/classes/headerapi/amqpwrapper.h"
#include "iot-protocols/amqp/classes/headerapi/amqpunwrapper.h"
#include "iot-protocols/amqp/classes/headerapi/amqpfactory.h"

AMQPData::AMQPData()
{
    this->data = NULL;
}

TLVAMQP *AMQPData::getValue()
{
    TLVAMQP *bin = NULL;

    if (!this->data == NULL) {
        bin = AMQPWrapper::wrapBinary(this->data);
    } else {
        bin = new AMQPTLVNull();
    }

    unsigned char * data = NULL;
    data = malloc(sizeof(char));
    data[0] = (char) 0x75;

    AMQPType *type = new AMQPType(AMQP_SMALL_ULONG_TYPE);
    AMQPTLVFixed *fixed = new AMQPTLVFixed(type, data);

    AMQPType *constructorType = new AMQPType(bin->getTypeValue());
    AMQPDescribedConstructor *constructor = new AMQPDescribedConstructor(constructorType, fixed);

    bin->setConstructor(constructor);
    return bin;
}

AMQPSectionCode *AMQPData::getCode()
{
    return new AMQPSectionCode(AMQP_DATA_SECTION_CODE);
}

void AMQPData::fill(TLVAMQP *value)
{
    if (!value->isNull()) {
        this->data = AMQPUnwrapper::unwrapBinary(value);
    }
}

unsigned char * AMQPData::getData() const
{
    return data;
}

void AMQPData::setData(const unsigned char &value)
{
    data = value;
}
