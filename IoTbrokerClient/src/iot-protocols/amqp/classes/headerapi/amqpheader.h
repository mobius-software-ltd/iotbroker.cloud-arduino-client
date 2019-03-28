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

#ifndef AMQPHEADER_H
#define AMQPHEADER_H

#include "iot-protocols/classes/message.h"
#include "iot-protocols/amqp/classes/tlv/compound/amqptlvlist.h"
#include "iot-protocols/amqp/classes/enums/amqpheadercode.h"

class AMQPHeader : public Message
{
protected:

    AMQPHeaderCode *code;

    int doff;
    int typeValue;
    int channel;

public:
    AMQPHeader();
    AMQPHeader(AMQPHeaderCode *code);

    AMQPHeaderCode *getCode() const;

    virtual int getLength();
    virtual int getType();
    virtual IotEnumProtocol *getProtocol();

    virtual AMQPTLVList *arguments() = 0;
    virtual void fillArguments(AMQPTLVList *list) = 0;

    void setCode(AMQPHeaderCode *value);

    int getDoff() const;
    void setDoff(int value);

    int getTypeValue() const;
    void setTypeValue(int value);

    int getChannel() const;
    void setChannel(int value);
};

#endif // AMQPHEADER_H
