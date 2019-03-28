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

#include "coapparser.h"

CoAPParser::CoAPParser()
{

}

Message *CoAPParser::decode(unsigned char * buf)
{
    CoAPMessage *message = new CoAPMessage();

    int i = 0;
    int firstByte = buf[i++];

    int version = firstByte >> 6;
    if (version != 1) {
        printf("COAP: Invalid version: " + version);
    }
    message->setVersion(version);

    int typeValue = (firstByte >> 4) & 3;
    message->setType((CoAPTypes)typeValue);

    int tokenLength = firstByte & 0xf;
    if (tokenLength > 8) {
        printf("COAP: Invalid token length: " + tokenLength);
    }

    int codeByte = buf[i++];
    int codeValue = (codeByte >> 5) * 100;
    codeValue += codeByte & 0x1F;
    CoAPCode code = (CoAPCode)codeValue;

    message->setCode(code);
    message->setMessageID(get_short(buf, i));
    i += 2;

    if (tokenLength > 0) {
        char * token = malloc (sizeof (token)*(token_length+1));
        memcpy(token, &buf[i], token_length);
        token[token_length] = '\0';
        message->setToken(token);
        i+=token_length;
    }

    int number = 0;

    while (i < sizeof(buf)) {
        unsigned char nextByte = buf[i++];
        if (nextByte == 0xFF) {
            break;
        }
        int delta = (nextByte >> 4) & 15;

        if (delta == 13) {
            delta = ((unsigned char)buf[i++]) + 13;
        } else if (delta == 14) {
            delta = get_short(buf, i) + 269;
            i += 2;
        } else if (delta > 14) {
            printf("COAP: Invalid option delta value: " + delta);
        }

        number += delta;

        int optionLength = nextByte & 15;
        if (optionLength == 13) {
            optionLength = ((unsigned char)buf[i++]) + 13;
        } else if (optionLength == 14) {
            optionLength = get_short(buf, i) + 269;
            i += 2;
        } else if (optionLength > 14) {
            printf("COAP: Invalid option delta value: " + optionLengt);
        }

        String optionValue;
        if (optionLength > 0) {
            optionValue = get_string(&buf[i], optionLength);
            i += optionLength;
        }

        message->addOption(CoapOption(number, optionLength, optionValue));
    }

    if (i < sizeof(buf)) {
        int size = sizeof(buf) - i;
        message->setPayload(get_string(&buf[i], size));
    }

    return message;
}

unsigned char * CoAPParser::encode(Message *m)
{
    CoAPMessage *message = (CoAPMessage *)m;
    int i = 0;
    unsigned char * buf = malloc(sizeof(char) * 256);
    unsigned short string_length = 0;

    char firstByte = 0;

    firstByte += (unsigned char) message->getVersion() << 6;
    firstByte += (unsigned char) message->getType() << 4;

    string_length = strlen(message->getToken());
    if (message->getToken() != - 1) {
        firstByte += (unsigned char) string_length;
    }

    buf[i++] = firstByte;

    int codeMsb = (message->getCode() / 100);
    int codeLsb = (unsigned char) (message->getCode() % 100);
    int codeByte = ((codeMsb << 5) + codeLsb);

    buf[i++] = codeByte;

    i += add_short(&buf[i], message->getMessageID());

    if (message->getToken() != - 1) {
        memcpy(&buf[i], message->getToken(), string_length);
        i += string_length;
    }

    int previousNumber = 0;
    std::list<CoapOption>::iterator it;
    list<CoapOption> listOptions = message->getOptions();
    for (it=listOptions.begin(); it!=listOptions.end(); ++it) {
        CoapOption option = it;
        int delta = option.getNumber() - previousNumber;
        int nextByte = 0;

        int extendedDelta = -1;
        if (delta < 13) {
            nextByte += delta << 4;
        } else {
            extendedDelta = delta;
            if (delta < 0xFF) {
                nextByte = 13 << 4;
            } else {
                nextByte = 14 << 4;
            }
        }

        int extendedLength = -1;
        if (option.getLength() < 13) {
            nextByte += option.getLength();
        } else {
            extendedLength = option.getLength();
            if (option.getLength() < 0xFF) {
                nextByte += 13;
            } else {
                nextByte += 14;
            }
        }

        buf[i++] = (unsigned char) nextByte;

        if (extendedDelta != -1) {
            if (extendedDelta < 0xFF) {
                buf[i++] = (unsigned char)(extendedDelta - 13);
            } else {
                i += add_short(&buf[i], extendedDelta - 269);
            }
        }

        if (extendedLength != -1) {
            if (extendedLength < 0xFF) {
                buf[i++] = (unsigned char)(extendedLength - 13);
            } else {
                i += add_short(&buf[i], extendedLength - 269);
            }
        }

        string_length = option->getLength();
        memcpy(&buf[i], option.getValue(), string_length);
        i+=string_length;
        previousNumber = option.getNumber();
    }

    buf[i++] = (unsigned char) 0xFF;

    if (!message->getPayload().isEmpty()) {
        string_length = strlen(message->getPayload());
        if (message->getPayload() != NULL && string_length > 0) {
        		memcpy(&buf[i], message->getPayload(), string_length);
        		i+=string_length;
        }
    }

    return buf;
}
