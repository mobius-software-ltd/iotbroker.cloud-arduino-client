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

#ifndef CONNECT_H
#define CONNECT_H

#include "iot-protocols/classes/message.h"
#include "iot-protocols/mqtt/classes/will.h"

/**
 * @brief The Connect class
 */

class Connect : public Message
{
private:
    String username;
    String password;
    String clientID;

    unsigned char protocolLevel;
    bool cleanSession;
    int keepAlive;

    Will *will;

public:
    Connect();
    Connect(String username, String password, String clientID, bool cleanSession, int keepAlive, Will *will);

    virtual int getLength();
    virtual int getType();
    virtual IotEnumProtocol *getProtocol();

    int getProtocolLevel();
    void setProtocolLevel(int protocolLevel);

    bool isCleanSession();
    void setCleanSession(bool cleanSession);

    bool isWillFlag();
    Will *getWill();
    void setWill(Will *will);

    int getKeepAlive();
    void setKeepAlive(int keepAlive);

    String getClientID();
    void setClientID(String clientID);

    bool isUsernameFlag();
    String getUsername();
    void setUsername(String username);

    bool isPasswordFlag();
    String getPassword();
    void setPassword(String password);
};

#endif // CONNECT_H
