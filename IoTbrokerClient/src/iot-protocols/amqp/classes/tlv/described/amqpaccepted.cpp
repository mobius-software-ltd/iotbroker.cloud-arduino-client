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

#include "amqpaccepted.h"
#include "iot-protocols/amqp/classes/constructors/amqpdescribedconstructor.h"
#include "iot-protocols/amqp/classes/tlv/fixed/amqptlvfixed.h"

AMQPAccepted::AMQPAccepted()
{

}

void AMQPAccepted::fill(AMQPTLVList *list)
{

}

AMQPTLVList *AMQPAccepted::getList()
{
    AMQPTLVList *tlvList = new AMQPTLVList();
    AMQPType *type = new AMQPType(AMQP_SMALL_ULONG_TYPE);

    unsigned char * data;
    data = malloc(sizeof(char));
    data[0] = (char) 0x24;

    AMQPDescribedConstructor *constructor = new AMQPDescribedConstructor(new AMQPType(tlvList->getTypeValue()), new AMQPTLVFixed(type, data));

    tlvList->setConstructor(constructor);
    return tlvList;
}
