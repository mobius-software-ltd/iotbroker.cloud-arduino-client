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

#include "timertask.h"
//#include "iot-protocols/iotprotocol.h"
#include "iot-protocols/mqtt/classes/mqttenums.h"
#include "iot-protocols/mqtt/messages/connect.h"
#include "iot-protocols/mqtt-sn/messages/snconnect.h"
#include "iot-protocols/mqtt/messages/publish.h"
#include "iot-protocols/mqtt-sn/messages/snpublish.h"

int const CONNECT_REPEAT_TIMES = 5;

TimerTask::TimerTask(Message *message, IotProtocol *iotProtocol, int period)
{
    this->message = message;
    this->iotProtocol = iotProtocol;
    this->period = period;
    this->status = false;
    this->connectCount = 0;

    Timer timer([]()
    {
        this->start(false);
    });

    this->timer = timer;
    this->timer.setSingleShot(false);
    this->timer->setInterval(Timer::Interval(period));
    this->start();
}

int TimerTask::getPeriod()
{
    return this->period;
}

Message *TimerTask::getMessage()
{
    return this->message;
}

void TimerTask::start()
{
    this->startSlot();
    this->timer.start();
}

void TimerTask::start(bool withDelay)
{
    if (withDelay == false) {
        this->startSlot();
    }
}

void TimerTask::startSlot()
{
    if (dynamic_cast<SNConnect*>( message ) || dynamic_cast<Connect*>( message )) {
        this->connectCount += 1;
        if (this->connectCount >= CONNECT_REPEAT_TIMES) {
            this->iotProtocol->timeoutMethod();
            this->connectCount = 0;
            this->stop();
            return;
        }
    }

    if (this->iotProtocol->getIsConnect() == true) {
        if (this->status == true) {
            if (dynamic_cast<Publish*>( message )) {
                Publish *publish = (Publish *)message;
                publish->setDup(true);
            }
            if (dynamic_cast<SNPublish*>( message )) {
                SNPublish *publish = (SNPublish *)message;
                publish->setIsDup(true);
            }
        }
        this->iotProtocol->send(this->message);
        this->status = true;
    }
}

void TimerTask::stop()
{
    this->timer.stop();
    this->status = false;
}
