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

#ifndef SUBACK_H
#define SUBACK_H

#include "iot-protocols/classes/countablemessage.h"
#include <list>

enum SubackCode
{
    ACCEPTED_QOS0 = 0,
    ACCEPTED_QOS1 = 1,
    ACCEPTED_QOS2 = 2,
    FAILURE = 128
};

/**
 * @brief The Suback class
 */

class Suback : public CountableMessage
{
private:
    int packetID;
    list<SubackCode> *returnCodes;

public:
    Suback();
    Suback(int packetID);
    Suback(int packetID, list<SubackCode> *returnCodes);

    virtual int getPacketID();
    virtual void setPacketID(int packetID);

    virtual int getLength();
    virtual int getType();
    virtual IotEnumProtocol *getProtocol();


    list<SubackCode> *getReturnCodes();
    void setReturnCodes(list<SubackCode> *returnCodes);

    bool isValidCode(SubackCode code);
};

#endif // SUBACK_H
