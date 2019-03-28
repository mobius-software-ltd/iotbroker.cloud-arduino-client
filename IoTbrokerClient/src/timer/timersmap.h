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

#ifndef TIMERSMAP_H
#define TIMERSMAP_H

#include "timer/timertask.h"
#include "iot-protocols/mqtt/messages/connect.h"
#include "iot-protocols/mqtt-sn/messages/snregister.h"
#include "iot-protocols/coap/messages/coapmessage.h"

static int const MAX_VALUE = 65535;
static int const FIRST_ID = 1;
static int const MESSAGE_RESEND_PERIOD = 3000;
static int const TIMEOUT_VALUE = 20000;

#include <map>
#include <list>
#include <iterator>
/**
 * @brief The TimersMap class
 */

class IotProtocol;

class TimersMap
{
private:
    map<int, TimerTask *> *timersMap;

    TimerTask *connect;
    TimerTask *ping;
    TimerTask *reg;

    int count;

    IotProtocol *iotProtocol;

public:
    TimersMap(IotProtocol *iotProtocol);

    void goConnectTimer(Message *connect);
    void stopConnectTimer();

    void goPingTimer(int keepalive);
    void stopPingTimer();

    int goRegisterTimer(Message *reg);
    void stopRegisterTimer();

    int goCoAPMessageTimer(Message *message, bool oneSend);

    void goMessageTimer(Message *message);

    Message *removeTimer(int id);
    Message *stopTimer(int id);

    void stopAllTimers();

    int getNewPacketID();
};

#endif // TIMERSMAP_H
