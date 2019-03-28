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

#ifndef PARSER_H
#define PARSER_H

#include <cstring>
#include <cstdlib>
#include <list>
#include "utils/helpers.h"
#include "classes/lengthdetails.h"

#include "iot-protocols/classes/message.h"
#include "iot-protocols/mqtt/messages/connect.h"
#include "iot-protocols/mqtt/messages/connack.h"
#include "iot-protocols/mqtt/messages/disconnect.h"
#include "iot-protocols/mqtt/messages/pingreq.h"
#include "iot-protocols/mqtt/messages/pingresp.h"
#include "iot-protocols/mqtt/messages/publish.h"
#include "iot-protocols/mqtt/messages/puback.h"
#include "iot-protocols/mqtt/messages/pubcomp.h"
#include "iot-protocols/mqtt/messages/pubrec.h"
#include "iot-protocols/mqtt/messages/pubrel.h"
#include "iot-protocols/mqtt/messages/subscribe.h"
#include "iot-protocols/mqtt/messages/suback.h"
#include "iot-protocols/mqtt/messages/unsubscribe.h"
#include "iot-protocols/mqtt/messages/unsuback.h"

/**
 * @brief The Parser class
 */

class Parser
{
private:
    unsigned char * getBufferByLength(int length);
public:
    unsigned char * next(unsigned char &bytes);
    unsigned char * encode(Message *message);
    Message *decode(unsigned char *bytes);
};

#endif // PARSER_H
