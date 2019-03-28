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

#ifndef AMQPFLOW_H
#define AMQPFLOW_H

#include <map>
#include "iot-protocols/amqp/classes/headerapi/amqpheader.h"

class AMQPFlow : public AMQPHeader
{
private:

    JsonVariant *nextIncomingId;
    JsonVariant *incomingWindow;
    JsonVariant *nextOutgoingId;
    JsonVariant *outgoingWindow;
    JsonVariant *handle;
    JsonVariant *deliveryCount;
    JsonVariant *linkCredit;
    JsonVariant *avaliable;
    JsonVariant *drain;
    JsonVariant *echo;
    map<JsonVariant *, JsonVariant *> properties;

public:
    AMQPFlow();

    virtual int getLength();
    virtual int getType();

    virtual AMQPTLVList *arguments();
    virtual void fillArguments(AMQPTLVList *list);

    void addProperty(String key, JsonVariant *value);

    JsonVariant *getNextIncomingId() const;
    void setNextIncomingId(JsonVariant *value);

    JsonVariant *getIncomingWindow() const;
    void setIncomingWindow(JsonVariant *value);

    JsonVariant *getNextOutgoingId() const;
    void setNextOutgoingId(JsonVariant *value);

    JsonVariant *getOutgoingWindow() const;
    void setOutgoingWindow(JsonVariant *value);

    JsonVariant *getHandle() const;
    void setHandle(JsonVariant *value);

    JsonVariant *getDeliveryCount() const;
    void setDeliveryCount(JsonVariant *value);

    JsonVariant *getLinkCredit() const;
    void setLinkCredit(JsonVariant *value);

    JsonVariant *getAvaliable() const;
    void setAvaliable(JsonVariant *value);

    JsonVariant *getDrain() const;
    void setDrain(JsonVariant *value);

    JsonVariant *getEcho() const;
    void setEcho(JsonVariant *value);

    map<JsonVariant *, JsonVariant *> getProperties() const;

    void setProperties(const map<JsonVariant *, JsonVariant *> &value);
};

#endif // AMQPFLOW_H
