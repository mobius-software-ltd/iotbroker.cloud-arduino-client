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

#include "amqpapplicationproperties.h"
#include "iot-protocols/amqp/classes/headerapi/amqpwrapper.h"
#include "iot-protocols/amqp/classes/headerapi/amqpunwrapper.h"
#include "iot-protocols/amqp/classes/constructors/amqpdescribedconstructor.h"

AMQPApplicationProperties::AMQPApplicationProperties()
{
    this->properties = map<JsonVariant *, JsonVariant *>();
}

TLVAMQP *AMQPApplicationProperties::getValue()
{
    AMQPTLVMap *map = new AMQPTLVMap();

    if (this->properties.size() != 0) {
        map = (AMQPTLVMap *)AMQPWrapper::wrapMap(this->properties);
    }

    unsigned char * data = NULL;
    data = malloc(sizeof(char));
    data[0] = (char) 0x74;

    AMQPType *type = new AMQPType(AMQP_SMALL_ULONG_TYPE);
    AMQPTLVFixed *fixed = new AMQPTLVFixed(type, data);

    AMQPType *constructorType = new AMQPType(map->getTypeValue());
    AMQPDescribedConstructor *constructor = new AMQPDescribedConstructor(constructorType, fixed);

    map->setConstructor(constructor);
    return map;
}

AMQPSectionCode *AMQPApplicationProperties::getCode()
{
    return new AMQPSectionCode(AMQP_APPLICATION_PROPERTIES_SECTION_CODE);
}

void AMQPApplicationProperties::fill(TLVAMQP *value)
{
    if (value->isNull()) {
        this->properties = AMQPUnwrapper::unwrapMap(value);
    }
}

void AMQPApplicationProperties::addProperty(String key, JsonVariant *value)
{
    JsonVariant *symbolVariant;
    symbolVariant.set(AMQPSimpleType::symbolToVariant(new AMQPSymbol(key)));
    this->properties.insert(symbolVariant, value);
}
