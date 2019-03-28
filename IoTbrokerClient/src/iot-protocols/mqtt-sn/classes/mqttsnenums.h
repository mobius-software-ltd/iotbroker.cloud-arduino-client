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

#ifndef MQTTSNENUMS_H
#define MQTTSNENUMS_H

enum SNMessageType
{
    SN_ADVERTISE        = 0,
    SN_SEARCHGW         = 1,
    SN_GWINFO           = 2,
    SN_CONNECT          = 4,
    SN_CONNACK          = 5,
    SN_WILLTOPICREQ     = 6,
    SN_WILLTOPIC        = 7,
    SN_WILLMSGREQ       = 8,
    SN_WILLMSG          = 9,
    SN_REGISTER         = 10,
    SN_REGACK           = 11,
    SN_PUBLISH          = 12,
    SN_PUBACK           = 13,
    SN_PUBCOMP          = 14,
    SN_PUBREC           = 15,
    SN_PUBREL           = 16,
    SN_SUBSCRIBE        = 18,
    SN_SUBACK           = 19,
    SN_UNSUBSCRIBE      = 20,
    SN_UNSUBACK         = 21,
    SN_PINGREQ          = 22,
    SN_PINGRESP         = 23,
    SN_DISCONNECT       = 24,
    SN_WILLTOPICUPD     = 26,
    SN_WILLTOPICRESP    = 27,
    SN_WILLMSGUPD       = 28,
    SN_WILLMSGRESP      = 29,
    SN_ENCAPSULATED     = 254,
};

enum SNRadius : int
{
    SN_BROADCAST_RADIUS = 0,
    SN_RADIUS_1 = 1,
    SN_RADIUS_2 = 2,
    SN_RADIUS_3 = 3,
};

enum SNReturnCode
{
    SN_ACCEPTED_RETURN_CODE = 0,
    SN_CONGESTION_RETURN_CODE = 1,
    SN_INVALID_TOPIC_ID_RETURN_CODE = 2,
    SN_NOT_SUPPORTED_RETURN_CODE = 3,
};

#endif // MQTTSNENUMS_H
