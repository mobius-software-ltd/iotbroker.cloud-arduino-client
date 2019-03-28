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

#ifndef AMQPLONGID_H
#define AMQPLONGID_H

#include "iot-protocols/amqp/classes/wrappers/messageID/amqpmessageid.h"
#include "utils/UUID.h"

class AMQPLongID : public AMQPMessageID
{
private:

    JsonVariant iD;

public:
    AMQPLongID(JsonVariant iD);

    virtual String getString();
    virtual unsigned char * getBinary();
    virtual JsonVariant getLongValue();
    virtual String getUUID();

    JsonVariant getID() const;
};

#endif // AMQPLONGID_H
