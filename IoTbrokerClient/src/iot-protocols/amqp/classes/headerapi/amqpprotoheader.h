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

#ifndef AMQPPROTOHEADER_H
#define AMQPPROTOHEADER_H

#include "iot-protocols/amqp/classes/headerapi/amqpheader.h"

enum AMQPProtocolIds {

    AMQPProtocolId        = 0,
    AMQPProtocolIdTLS     = 2,
    AMQPProtocolIdSASL    = 3,
};

static String const AMQPProtocolName = "AMQP";

class AMQPProtoHeader : public AMQPHeader
{

private:

    AMQPProtocolIds protocolId;
    int versionMajor;
    int versionMinor;
    int versionRevision;

public:
    AMQPProtoHeader();
    AMQPProtoHeader(AMQPProtocolIds protocolId);

    virtual int getLength();
    virtual int getType();

    virtual AMQPTLVList *arguments();
    virtual void fillArguments(AMQPTLVList *list);

    unsigned char * getBytes();

    AMQPProtocolIds getProtocolId() const;
    void setProtocolId(const AMQPProtocolIds &value);

    int getVersionMajor() const;
    void setVersionMajor(int value);

    int getVersionMinor() const;
    void setVersionMinor(int value);

    int getVersionRevision() const;
    void setVersionRevision(int value);

};

#endif // AMQPPROTOHEADER_H
