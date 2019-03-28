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

#include "sndisconnect.h"

SNDisconnect::SNDisconnect()
{

}

SNDisconnect::SNDisconnect(int duration)
{
    this->duration = duration;
}

int SNDisconnect::getLength()
{
    int length = 2;
    if (this->duration > 0) {
        length += 2;
    }
    return length;
}

int SNDisconnect::getType()
{
    return SN_DISCONNECT;
}

IotEnumProtocol *SNDisconnect::getProtocol()
{
    return new IotEnumProtocol(MQTT_SN_PROTOCOL);
}

int SNDisconnect::getDuration() const
{
    return duration;
}

void SNDisconnect::setDuration(int value)
{
    duration = value;
}
