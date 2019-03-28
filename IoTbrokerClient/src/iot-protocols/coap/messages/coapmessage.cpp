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

#include "coapmessage.h"

CoAPMessage::CoAPMessage()
{
    this->version = 1;
    this->messageID = 0;
    this->token = -1;
    std::list<CoapOption> this->options;
}

CoAPMessage::CoAPMessage(int version, CoAPTypes type, CoAPCode code, short messageId, long token, QList<CoapOption> options, unsigned char * payload)
{
    this->version = version;
    this->type = type;
    this->code = code;
    this->messageID = messageId;
    this->token = token;
    this->options = options;
    this->payload = payload;
}

CoAPMessage::CoAPMessage(CoAPCode code, bool confirmableFlag, String payload) : CoAPMessage()
{
    this->code = code;
    this->type = (confirmableFlag == true) ? COAP_CONFIRMABLE_TYPE : COAP_NONCONFIRMABLE_TYPE;
    this->payload = payload;
}

int CoAPMessage::getLength()
{
    return 0;
}

int CoAPMessage::getType()
{
    return this->type;
}

IotEnumProtocol *CoAPMessage::getProtocol()
{
    return new IotEnumProtocol(COAP_PROTOCOL);
}

void CoAPMessage::addOption(CoAPOptionDefinitions type, unsigned char * data)
{
    CoapOption option = CoapOption(type, sizeof(data), data);
    this->options.push_back(option);
}

void CoAPMessage::addOption(CoAPOptionDefinitions type, String str)
{
    this->addOption(type, str);
}

void CoAPMessage::addOption(CoapOption option)
{
    this->options.push_back(option);
}

CoapOption CoAPMessage::getOption(CoAPOptionDefinitions type)
{
    std::list<CoapOption>::iterator it;
    for (it=this->options.begin(); it!=this->options.end(); ++it) {
        CoapOption option = it;
        if (option.getNumber() == type) {
            return option;
        }
    }
    return CoapOption(0, 0, unsigned char *());
}

list<CoapOption> CoAPMessage::getOptions()
{
    std::sort(this->options.begin(), this->options.end(),CoapOption::numberLessThan);
    return options;
}

String CoAPMessage::toString()
{
    return "version: " + this->version + "\n" +
            "type: " + this->type + "\n" +
            "token: " + this->token + "\n" +
            "code: " + this->code + "\n" +
            "messageID: " + this->messageID + "\n" +
            "payload: " + this->payload + "\n" +
            "options size: " + this->options.size() + "\n";
}


int CoAPMessage::getVersion() const
{
    return version;
}

void CoAPMessage::setVersion(int value)
{
    version = value;
}

void CoAPMessage::setType(const CoAPTypes &value)
{
    type = value;
}

long CoAPMessage::getToken() const
{
    return token;
}

void CoAPMessage::setToken(const long &value)
{
    token = value;
}

CoAPCode CoAPMessage::getCode() const
{
    return code;
}

void CoAPMessage::setCode(const CoAPCode &value)
{
    code = value;
}

short CoAPMessage::getMessageID() const
{
    return messageID;
}

void CoAPMessage::setMessageID(short value)
{
    messageID = value;
}

unsigned char * CoAPMessage::getPayload() const
{
    return payload;
}

void CoAPMessage::setPayload(const unsigned char &value)
{
    payload = value;
}
