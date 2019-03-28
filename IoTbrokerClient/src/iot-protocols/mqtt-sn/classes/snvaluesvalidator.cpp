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

#include "snvaluesvalidator.h"

static list<int> *reservedPacketIDS;
static list<int> *reservedTopicIDS;

SNValuesValidator::SNValuesValidator()
{

}

bool SNValuesValidator::validatePacketID(int packetID)
{
    reservedPacketIDS->push_back(0x0000);
    it = find(reservedPacketIDS.begin(), reservedPacketIDS.end(), packetID);
    return packetID > 0 && (it == reservedPacketIDS.end());
}

bool SNValuesValidator::validateTopicID(int topicID)
{
    reservedTopicIDS->push_back(0x0000);
    reservedTopicIDS->push_back(0xFFFF);
    it = find(reservedTopicIDS.begin(), reservedTopicIDS.end(), topicID);
    return topicID > 0 && (it == reservedTopicIDS.end());
}

bool SNValuesValidator::validateRegistrationTopicID(int topicID)
{
    return topicID >= 0;
}

bool SNValuesValidator::canReadData(unsigned char data[], int left)
{
    return (sizeof data > 0 && left > 0);
}

bool SNValuesValidator::validateClientID(String *clientID)
{
    return (clientID != NULL && strlen(clientID) != 0);
}
