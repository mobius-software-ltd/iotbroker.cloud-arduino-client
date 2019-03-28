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

#include "amqpsectioncode.h"

AMQPSectionCode::AMQPSectionCode()
{
    this->map = std::map<int, String>();
    this->map.insert(std::pair<int, String>(AMQP_HEADER_SECTION_CODE, AMQP_HEADER_SECTION_CODE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_DELIVERY_ANNOTATIONS_SECTION_CODE, AMQP_DELIVERY_ANNOTATIONS_SECTION_CODE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_MESSAGE_ANNOTATIONS_SECTION_CODE, AMQP_MESSAGE_ANNOTATIONS_SECTION_CODE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_PROPERTIES_SECTION_CODE, AMQP_PROPERTIES_SECTION_CODE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_APPLICATION_PROPERTIES_SECTION_CODE, AMQP_APPLICATION_PROPERTIES_SECTION_CODE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_DATA_SECTION_CODE, AMQP_DATA_SECTION_CODE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_SEQUENCE_SECTION_CODE, AMQP_SEQUENCE_SECTION_CODE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_VALUE_SECTION_CODE, AMQP_VALUE_SECTION_CODE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_FOOTER_SECTION_CODE, AMQP_FOOTER_SECTION_CODE_STRING));
}

AMQPSectionCode::AMQPSectionCode(int value) : AMQPSectionCode()
{
    this->value = value;
}

int AMQPSectionCode::getValue()
{
    return this->value;
}

String AMQPSectionCode::getName()
{
    return EnumObject::getName(this->value);
}
