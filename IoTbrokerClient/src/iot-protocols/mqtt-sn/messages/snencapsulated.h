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

#ifndef SNENCAPSULATED_H
#define SNENCAPSULATED_H

#include "iot-protocols/classes/message.h"
#include "iot-protocols/mqtt-sn/classes/mqttsnenums.h"

class SNEncapsulated : public Message
{

private:

    SNRadius radius;
    String wirelessNodeID;
    Message *message;

public:
    SNEncapsulated();
    SNEncapsulated(SNRadius radius, String nodeID, Message *message);

    virtual int getLength();
    virtual int getType();
    virtual IotEnumProtocol *getProtocol();

    SNRadius getRadius() const;
    void setRadius(const SNRadius &value);

    String getWirelessNodeID() const;
    void setWirelessNodeID(const String &value);

    Message *getMessage() const;
    void setMessage(Message *value);
};

#endif // SNENCAPSULATED_H
