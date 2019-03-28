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

#ifndef COAPMESSAGE_H
#define COAPMESSAGE_H

#include "iot-protocols/classes/message.h"
#include "iot-protocols/coap/classes/coapenums.h"
#include "iot-protocols/coap/classes/coapoption.h"
#include <list>
#include <algorithm>

class CoAPMessage : public Message
{

    int version;
    CoAPTypes type;
    long token;
    CoAPCode code;
    short messageID;
    unsigned char *  payload;
    list<CoapOption> options;

public:
    CoAPMessage();
    CoAPMessage(int version, CoAPTypes type, CoAPCode code, short messageId, long token, list<CoapOption> options, unsigned char * payload);
    CoAPMessage(CoAPCode code, bool confirmableFlag, String payload);

    virtual int getLength();
    virtual int getType();
    virtual IotEnumProtocol *getProtocol();

    void addOption(CoAPOptionDefinitions type, unsigned char * data);
    void addOption(CoAPOptionDefinitions type, String str);
    void addOption(CoapOption option);

    CoapOption getOption(CoAPOptionDefinitions type);

    int getVersion() const;
    void setVersion(int value);
    void setType(const CoAPTypes &value);
    long getToken() const;
    void setToken(const long &value);
    CoAPCode getCode() const;
    void setCode(const CoAPCode &value);
    short getMessageID() const;
    void setMessageID(short value);
    unsigned char * getPayload() const;
    void setPayload(const unsigned char * &value);
    list<CoapOption> getOptions();

    String toString();
};

#endif // COAPMESSAGE_H
