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

#ifndef TLVAMQP_H
#define TLVAMQP_H

#include "iot-protocols/amqp/classes/enums/amqptype.h"
#include "iot-protocols/amqp/classes/constructors/amqpsimpleconstructor.h"

class TLVAMQP : public QObject
{
protected:

    AMQPType *type;
    AMQPSimpleConstructor *constructor;
    unsigned char * value;

public:
    TLVAMQP(AMQPSimpleConstructor *constructor);

    virtual bool isNull();
    virtual unsigned char * getData() = 0;
    virtual int getLength() = 0;
    virtual unsigned char * getValue() = 0;

    virtual String description() = 0;

    AMQPSimpleConstructor *getConstructor() const;
    void setConstructor(AMQPSimpleConstructor *constr);

    AMQPTypes getTypeValue();
    void setTypeValue(AMQPTypes value);
};

#endif // TLVAMQP_H
