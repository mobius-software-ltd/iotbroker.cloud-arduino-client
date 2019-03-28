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

#ifndef AMQPATTACH_H
#define AMQPATTACH_H

#include <map>
#include <list>
#include "iot-protocols/amqp/classes/headerapi/amqpheader.h"
#include "iot-protocols/amqp/classes/enums/amqprolecode.h"
#include "iot-protocols/amqp/classes/enums/amqpsendcode.h"
#include "iot-protocols/amqp/classes/enums/amqpreceiversettlemode.h"
#include "iot-protocols/amqp/classes/terminus/amqpsource.h"
#include "iot-protocols/amqp/classes/terminus/amqptarget.h"
#include "iot-protocols/amqp/classes/wrappers/amqpsymbol.h"

class AMQPAttach : public AMQPHeader
{
private:
    String name;
    JsonJsonVariant *handle;
    AMQPRoleCode *role;
    AMQPSendCode *sendCodes;
    AMQPReceiverSettleMode *receivedCodes;
    AMQPSource *source;
    AMQPTarget *target;
    map<JsonJsonVariant *, JsonJsonVariant *> unsettled;
    JsonJsonVariant *incompleteUnsettled;
    JsonJsonVariant *initialDeliveryCount;
    JsonJsonVariant *maxMessageSize;
    list<JsonJsonVariant *> offeredCapabilities;
    list<JsonJsonVariant *> desiredCapabilities;
    map<JsonJsonVariant *, JsonJsonVariant *> properties;

public:
    AMQPAttach();

    virtual int getLength();
    virtual int getType();

    virtual AMQPTLVList *arguments();
    virtual void fillArguments(AMQPTLVList *list);

    void addUnsettled(String key, JsonJsonVariant *value);
    void addOfferedCapability(list<String> array);
    void addDesiredCapability(list<String> array);
    void addProperty(String key, JsonJsonVariant *value);

    String getName() const;
    void setName(const String &value);

    JsonJsonVariant *getHandle() const;
    void setHandle(JsonJsonVariant *value);

    AMQPRoleCode *getRole() const;
    void setRole(AMQPRoleCode *value);

    AMQPSendCode *getSendCodes() const;
    void setSendCodes(AMQPSendCode *value);

    AMQPReceiverSettleMode *getReceivedCodes() const;
    void setReceivedCodes(AMQPReceiverSettleMode *value);

    AMQPSource *getSource() const;
    void setSource(AMQPSource *value);

    AMQPTarget *getTarget() const;
    void setTarget(AMQPTarget *value);

    map<JsonVariant *, JsonVariant *> getUnsettled() const;
    void setUnsettled(const map<JsonVariant *, JsonVariant *> &value);

    JsonVariant *getIncompleteUnsettled() const;
    void setIncompleteUnsettled(JsonVariant *value);

    JsonVariant *getInitialDeliveryCount() const;
    void setInitialDeliveryCount(JsonVariant *value);

    JsonVariant *getMaxMessageSize() const;
    void setMaxMessageSize(JsonVariant *value);

    list<JsonVariant *> getOfferedCapabilities() const;
    void setOfferedCapabilities(const list<JsonVariant *> &value);

    list<JsonVariant *> getDesiredCapabilities() const;
    void setDesiredCapabilities(const list<JsonVariant *> &value);

    map<JsonVariant *, JsonVariant *> getProperties() const;
    void setProperties(const map<JsonVariant *, JsonVariant *> &value);
};

#endif // AMQPATTACH_H
