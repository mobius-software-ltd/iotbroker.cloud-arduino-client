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

#ifndef AMQPSECTIONCODE_H
#define AMQPSECTIONCODE_H

#include <map>
#include "iot-protocols/amqp/classes/enums/enumobject.h"

enum AMQPSectionCodes
{
    AMQP_HEADER_SECTION_CODE                    = 0x70,
    AMQP_DELIVERY_ANNOTATIONS_SECTION_CODE      = 0x71,
    AMQP_MESSAGE_ANNOTATIONS_SECTION_CODE       = 0x72,
    AMQP_PROPERTIES_SECTION_CODE                = 0x73,
    AMQP_APPLICATION_PROPERTIES_SECTION_CODE    = 0x74,
    AMQP_DATA_SECTION_CODE                      = 0x75,
    AMQP_SEQUENCE_SECTION_CODE                  = 0x76,
    AMQP_VALUE_SECTION_CODE                     = 0x77,
    AMQP_FOOTER_SECTION_CODE                    = 0x78,
};

static String const AMQP_HEADER_SECTION_CODE_STRING = "header";
static String const AMQP_DELIVERY_ANNOTATIONS_SECTION_CODE_STRING = "delivery-annotations";
static String const AMQP_MESSAGE_ANNOTATIONS_SECTION_CODE_STRING = "message-annotations";
static String const AMQP_PROPERTIES_SECTION_CODE_STRING = "properties";
static String const AMQP_APPLICATION_PROPERTIES_SECTION_CODE_STRING = "application-properties";
static String const AMQP_DATA_SECTION_CODE_STRING = "data";
static String const AMQP_SEQUENCE_SECTION_CODE_STRING = "amqp-sequence";
static String const AMQP_VALUE_SECTION_CODE_STRING = "amqp-value";
static String const AMQP_FOOTER_SECTION_CODE_STRING = "footer";

class AMQPSectionCode : public EnumObject
{
private:

    int value;

public:
    AMQPSectionCode();
    AMQPSectionCode(int value);

    int getValue();
    String getName();
};

#endif // AMQPSECTIONCODE_H
