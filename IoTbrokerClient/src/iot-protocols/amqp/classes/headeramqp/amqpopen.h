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

#ifndef AMQPOPEN_H
#define AMQPOPEN_H

#include <map>
#include <list>
#include "iot-protocols/amqp/classes/headerapi/amqpheader.h"

class AMQPOpen : public AMQPHeader
{
private:

    String containerId;
    String hostname;
    JsonVariant *maxFrameSize;
    JsonVariant *channelMax;
    JsonVariant *idleTimeout;
    list<JsonVariant *> outgoingLocales;
    list<JsonVariant *> incomingLocales;
    list<JsonVariant *> offeredCapabilities;
    list<JsonVariant *> desiredCapabilities;
    map<JsonVariant *, JsonVariant *> properties;

public:
    AMQPOpen();

    virtual int getLength();
    virtual int getType();

    virtual AMQPTLVList *arguments();
    virtual void fillArguments(AMQPTLVList *list);

    void addOutgoingLocale(list<String> array);
    void addIncomingLocale(list<String> array);
    void addOfferedCapability(list<String> array);
    void addDesiredCapability(list<String> array);
    void addProperty(String key, JsonVariant *value);

    String getContainerId() const;
    void setContainerId(const String &value);

    String getHostname() const;
    void setHostname(const String &value);

    JsonVariant *getMaxFrameSize() const;
    void setMaxFrameSize(JsonVariant *value);

    JsonVariant *getChannelMax() const;
    void setChannelMax(JsonVariant *value);

    JsonVariant *getIdleTimeout() const;
    void setIdleTimeout(JsonVariant *value);

    list<JsonVariant *> getOutgoingLocales() const;
    void setOutgoingLocales(const list<JsonVariant *> &value);

    list<JsonVariant *> getIncomingLocales() const;
    void setIncomingLocales(const list<JsonVariant *> &value);

    list<JsonVariant *> getOfferedCapabilities() const;
    void setOfferedCapabilities(const list<JsonVariant *> &value);

    list<JsonVariant *> getDesiredCapabilities() const;
    void setDesiredCapabilities(const list<JsonVariant *> &value);

    map<JsonVariant *, JsonVariant *> getProperties() const;
    void setProperties(const map<JsonVariant *, JsonVariant *> &value);
};

#endif // AMQPOPEN_H
