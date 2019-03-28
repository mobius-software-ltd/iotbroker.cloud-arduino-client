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

#ifndef SNCONNECT_H
#define SNCONNECT_H

#include "iot-protocols/classes/message.h"
#include "iot-protocols/mqtt-sn/classes/mqttsnenums.h"

static int MQTT_SN_PROTOCOL_ID = 1;

class SNConnect : public Message
{

private:

    bool willPresent;
    bool cleanSession;
    int protocolID;
    int duration;
    String clientID;

public:
    SNConnect();
    SNConnect(bool cleanSession, int duration, String clientID, bool willPresent);

    virtual int getLength();
    virtual int getType();
    virtual IotEnumProtocol *getProtocol();

    bool getWillPresent() const;
    void setWillPresent(bool value);

    bool getCleanSession() const;
    void setCleanSession(bool value);

    int getProtocolID() const;
    void setProtocolID(int value);

    int getDuration() const;
    void setDuration(int value);

    String getClientID() const;
    void setClientID(const String &value);
};

#endif // SNCONNECT_H
