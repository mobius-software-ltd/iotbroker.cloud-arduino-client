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

#include "amqpparser.h"

AMQPParser::AMQPParser()
{

}

int AMQPParser::next(unsigned char * buffer)
{
    int i = 0;

    int length = get_int(buffer, i);
    i += 4;

    if (length == 1095586128) {
        int protocolId = buffer[i++];
        int versionMajor = buffer[i++];
        int versionMinor = buffer[i++];
        int versionRevision = buffer[i];
        if ((protocolId == AMQPProtocolId || protocolId == AMQPProtocolIdTLS || protocolId == AMQPProtocolIdSASL) &&
                versionMajor == 1 && versionMinor == 0 && versionRevision == 0) {
            return 8;
        } else {
            return -1;
        }
    }
    return length;
}

AMQPHeader *AMQPParser::decode(ByteArray buffer)
{
    int i = 0;
    String protocolName;
    protocolName = get_string(&buffer[i], 4);
    i += 4;
    if (protocolName == AMQPProtocolName) {
        AMQPProtoHeader *protoHeader = new AMQPProtoHeader();
        protoHeader->setProtocolId((AMQPProtocolIds)buffer[i++]);
        protoHeader->setVersionMajor(buffer[i++]);
        protoHeader->setVersionMinor(buffer[i++]);
        protoHeader->setVersionRevision(buffer[i++]);
        return protoHeader;
    }

    int length = get_int(buffer, i) & 0xffffffffL;
    i += 4;
    int doff = buffer[i++] & 0xff;
    int type = buffer[i++] & 0xff;
    int channel = get_short(buffer, i) & 0xffff;
    i += 2;

    if (length == 8 && doff == 2 && (type == 0 || type == 1) && channel == 0) {
        if (sizeof(buffer) - i == 0) {
            return new AMQPPing();
        } else {
            printf("Received malformed ping-header with invalid length");
            return NULL;
        }
    }

    if (length == 1095586128 && (doff == 3 || doff == 0) && type == 1 && channel == 0) {
        if (sizeof(buffer) - i == 0) {
            return new AMQPPing();
        } else {
            printf("Received malformed protocol-header with invalid length");
            return NULL;
        }
    }

    if (length != (sizeof(buffer) - i) + 8) {
        printf("Received malformed header with invalid length");
        return NULL;
    }

    AMQPHeader *header = NULL;

    if (type == 0) {
        header = AMQPFactory::amqp(&buffer);
    } else if (type == 1) {
        header = AMQPFactory::sasl(&buffer);
    } else {
        printf("Received malformed header with invalid type");
        return NULL;
    }

    if (header->getCode()->getValue() == AMQP_TRANSFER_HEADER_CODE) {
        while ((sizeof(buffer) - i) > 0) {
            list<AMQPSection *> sections;
            sections.push_back(AMQPFactory::section(&buffer));
            ((AMQPTransfer *)header)->addSections(sections);
        }
    }

    return header;
}

unsigned char * AMQPParser::encode(AMQPHeader *header)
{
    unsigned char * data = NULL;
    int i = 0;
    int string_length = 0;

    if (header->getCode()->getValue() == AMQP_PROTOCOL_HEADER_CODE_STRING) {
        string_length = strlen(AMQPProtocolName);
        buf = malloc(string_length * sizeof(char));
        memcpy(&buf[i], AMQPProtocolName, string_length);
        i += string_length;
        data[i++] = ((AMQPProtoHeader *)header)->getProtocolId();
        data[i++] = ((AMQPProtoHeader *)header)->getVersionMajor();
        data[i++] = ((AMQPProtoHeader *)header)->getVersionMinor();
        data[i++] = ((AMQPProtoHeader *)header)->getVersionRevision();
        return data;
    }

    if (header->getCode()->getValue() == AMQP_PING_HEADER_CODE_STRING) {
        int ping_length = 8;
        buf = malloc(ping_length * sizeof(char));
        i += add_int(&data[i], 8);
        data[i++] = header->getDoff();
        data[i++] = header->getType();
        add_short(&buf[i], header->getChannel());
        return data;
    }

    int frame_length = 8;
    data = malloc((frame_length + header->arguments()->getLength()) * sizeof(char));

    i += add_int(&data[i], header->getLength());
    data[i++] = header->getDoff();
    data[i++] = header->getTypeValue();
    i += add_short(&buf[i], header->getChannel());

    string_length = strlen(header->arguments()->getData());
    memcpy(&data[i], header->arguments()->getData(), string_length);
    i += string_length;

    if (header->getCode()->getValue() == AMQP_TRANSFER_HEADER_CODE) {
      vector<AMQPSection *> sections;
      map<AMQPSectionCode *, AMQPSection *> sectionsMap = (AMQPTransfer *)header)->getSections();
      for(map<AMQPSectionCode  *, AMQPSection *>::iterator it = sections.begin(); it != sections.end(); ++it) {
          sections.push_back(it->second);
      }
      foreach (AMQPSection *item, sections) {
          string_length = sizeof(item->getValue()->getData());
          memcpy(&data[i], item->getValue()->getData(), string_length);
          i += string_length;
      }
    }

    return data;
}
