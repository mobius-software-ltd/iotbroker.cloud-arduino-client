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

#ifndef UNSUBACK_H
#define UNSUBACK_H

#include "iot-protocols/classes/countablemessage.h"

/**
 * @brief The Unsuback class
 */

class Unsuback : public CountableMessage
{
private:
    int packetID;

public:
    Unsuback();
    Unsuback(int packetID);

    virtual int getPacketID();
    virtual void setPacketID(int packetID);

    virtual int getLength();
    virtual int getType();
    virtual IotEnumProtocol *getProtocol();

};

#endif // UNSUBACK_H
