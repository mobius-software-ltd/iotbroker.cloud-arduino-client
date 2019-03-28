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

#include "snpubcomp.h"

SNPubcomp::SNPubcomp()
{
    
}

SNPubcomp::SNPubcomp(int packetID)
{
    this->packetID = packetID;
}

int SNPubcomp::getLength()
{
    return 4;
}

int SNPubcomp::getType()
{
    return SN_PUBCOMP;
}

IotEnumProtocol *SNPubcomp::getProtocol()
{
    return new IotEnumProtocol(MQTT_SN_PROTOCOL);
}

int SNPubcomp::getPacketID()
{
    return packetID;
}

void SNPubcomp::setPacketID(int value)
{
    this->packetID = value;
}
