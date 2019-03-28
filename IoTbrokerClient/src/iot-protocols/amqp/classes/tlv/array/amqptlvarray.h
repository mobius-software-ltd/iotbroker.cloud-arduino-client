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

#ifndef AMQPTLVARRAY_H
#define AMQPTLVARRAY_H

#include <vector>
#include <cstring>
#include <cstdlib>
#include "utils/helpers.h"
#include "iot-protocols/amqp/classes/tlv/api/tlvamqp.h"

class AMQPTLVArray : public TLVAMQP
{
private:

    int width;
    int size;
    int count;

    vector<TLVAMQP *> elements;
    AMQPSimpleConstructor *elementContructor;

public:
    AMQPTLVArray();
    AMQPTLVArray(AMQPType *type, vector<TLVAMQP *>elements);

    virtual bool isNull();
    virtual unsigned char * getData();
    virtual int getLength();
    virtual unsigned char * getValue();

    virtual String description();

    void addElement(TLVAMQP *element);
    int getWidth() const;
    int getSize() const;
    int getCount() const;
    vector<TLVAMQP *> getElements() const;
    AMQPSimpleConstructor *getElementContructor() const;
};

#endif // AMQPTLVARRAY_H
