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

#ifndef AMQPBEGIN_H
#define AMQPBEGIN_H

#include <ArduinoJson.h>
#include <StandardCplusplus.h>
#include <map>
#include <list>
#include "iot-protocols/amqp/classes/headerapi/amqpheader.h"
#include "iot-protocols/amqp/classes/wrappers/amqpsymbol.h"

class AMQPBegin : public AMQPHeader
{
private:

    JsonVariant *remoteChannel;
    JsonVariant *nextOutgoingID;
    JsonVariant *incomingWindow;
    JsonVariant *outgoingWindow;
    JsonVariant *handleMax;
    std::list<JsonVariant *> offeredCapabilities;
    std::list<JsonVariant *> desiredCapabilities;
    std::map<JsonVariant *, JsonVariant *> properties;

public:
    AMQPBegin();

    virtual int getLength();
    virtual int getType();

    virtual AMQPTLVList *arguments();
    virtual void fillArguments(AMQPTLVList *list);

    void addOfferedCapability(std::list<String> list);
    void addDesiredCapability(std::list<String> list);
    void addProperty(String key, JsonVariant *value);

    JsonVariant *getRemoteChannel() const;
    void setRemoteChannel(JsonVariant *value);

    JsonVariant *getNextOutgoingID() const;
    void setNextOutgoingID(JsonVariant *value);

    JsonVariant *getIncomingWindow() const;
    void setIncomingWindow(JsonVariant *value);

    JsonVariant *getOutgoingWindow() const;
    void setOutgoingWindow(JsonVariant *value);

    JsonVariant *getHandleMax() const;
    void setHandleMax(JsonVariant *value);

    std::list<JsonVariant *> getOfferedCapabilities() const;
    void setOfferedCapabilities(const std::list<JsonVariant *> &value);

    std::list<JsonVariant *> getDesiredCapabilities() const;
    void setDesiredCapabilities(const std::list<JsonVariant *> &value);

    std::map<JsonVariant *, JsonVariant *> getProperties() const;
    void setProperties(const std::map<JsonVariant *, JsonVariant *> &value);
};

#endif // AMQPBEGIN_H
