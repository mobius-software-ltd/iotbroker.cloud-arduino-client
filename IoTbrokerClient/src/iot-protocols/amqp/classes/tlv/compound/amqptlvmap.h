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

#ifndef AMQPTLVMAP_H
#define AMQPTLVMAP_H

#include "iot-protocols/amqp/classes/tlv/api/tlvamqp.h"
#include <cstring>
#include <cstdlib>

class AMQPTLVMap : public TLVAMQP
{
private:

    int width;
    int size;
    int count;

    map<TLVAMQP *, TLVAMQP *> map;

    void update();

public:
    AMQPTLVMap();
    AMQPTLVMap(AMQPType *type, map<TLVAMQP *, TLVAMQP *> map);

    virtual unsigned char * getData();
    virtual int getLength();
    virtual unsigned char * getValue();

    virtual String description();

    void putElement(TLVAMQP *key, TLVAMQP *value);

    int getWidth() const;
    int getSize() const;
    int getCount() const;
    map<TLVAMQP *, TLVAMQP *> getMap() const;
};

#endif // AMQPTLVMAP_H
