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

#ifndef AMQPPROPERTIES_H
#define AMQPPROPERTIES_H

#include "iot-protocols/amqp/classes/section/amqpsection.h"
#include "iot-protocols/amqp/classes/wrappers/messageID/amqpmessageid.h"
#include <chrono>
#include <ctime>
#include <cstdlib>

class AMQPProperties : public AMQPSection
{
private:

    AMQPMessageID *messageId;
    unsigned char * userId;
    String to;
    String subject;
    String replyTo;
    unsigned char * correlationID;
    String contentType;
    String contentEncoding;
    time_t absoluteExpiryTime;
    time_t creationTime;
    String groupId;
    JsonVariant *groupSequence;
    String replyToGroupId;

public:
    AMQPProperties();

    virtual TLVAMQP *getValue();
    virtual AMQPSectionCode *getCode();

    virtual void fill(TLVAMQP *value);

    AMQPMessageID *getMessageId() const;
    void setMessageId(AMQPMessageID *value);

    unsigned char * getUserId() const;
    void setUserId(const unsigned char &value);

    String getTo() const;
    void setTo(const String &value);

    String getSubject() const;
    void setSubject(const String &value);

    String getReplyTo() const;
    void setReplyTo(const String &value);

    unsigned char * getCorrelationID() const;
    void setCorrelationID(const unsigned char &value);

    String getContentType() const;
    void setContentType(const String &value);

    String getContentEncoding() const;
    void setContentEncoding(const String &value);

    time_t getAbsoluteExpiryTime() const;
    void setAbsoluteExpiryTime(const time_t &value);

    time_t getCreationTime() const;
    void setCreationTime(const time_t &value);

    String getGroupId() const;
    void setGroupId(const String &value);

    JsonVariant *getGroupSequence() const;
    void setGroupSequence(JsonVariant *value);

    String getReplyToGroupId() const;
    void setReplyToGroupId(const String &value);
};

#endif // AMQPPROPERTIES_H
