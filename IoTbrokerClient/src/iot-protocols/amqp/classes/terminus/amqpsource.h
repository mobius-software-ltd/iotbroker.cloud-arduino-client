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

#ifndef AMQPSOURCE_H
#define AMQPSOURCE_H

#include <StandardCplusplus.h>
#include <map>
#include <list>
#include <cstdlib>
#include "iot-protocols/amqp/classes/enums/amqpterminusdurability.h"
#include "iot-protocols/amqp/classes/enums/amqpterminusexpirypolicy.h"
#include "iot-protocols/amqp/classes/enums/amqpdistributionmode.h"
#include "iot-protocols/amqp/classes/wrappers/amqpsymbol.h"
#include "iot-protocols/amqp/classes/tlv/described/amqpoutcome.h"

class AMQPSource
{
private:

    String address;
    AMQPTerminusDurability *durable;
    AMQPTerminusExpiryPolicy *expiryPeriod;
    JsonVariant *timeout;
    JsonVariant *dynamic;
    std::map<JsonVariant *, JsonVariant *> dynamicNodeProperties;
    AMQPDistributionMode *distributionMode;
    std::map<JsonVariant *, JsonVariant *> filter;
    AMQPOutcome *defaultOutcome;
    std::list<JsonVariant *> outcomes;
    std::list<JsonVariant *> capabilities;

public:
    AMQPSource();

    AMQPTLVList *getList();
    void fill(AMQPTLVList *list);

    void addDynamicNodeProperties(String key, JsonVariant *value);
    void addFilter(String key, JsonVariant *value);
    void addOutcomes(std::list<String> array);
    void addCapabilities(std::list<String> array);

    String getAddress() const;
    void setAddress(const String &value);
    AMQPTerminusDurability *getDurable() const;
    void setDurable(AMQPTerminusDurability *value);
    AMQPTerminusExpiryPolicy *getExpiryPeriod() const;
    void setExpiryPeriod(AMQPTerminusExpiryPolicy *value);
    JsonVariant *getTimeout() const;
    void setTimeout(JsonVariant *value);
    JsonVariant *getDynamic() const;
    void setDynamic(JsonVariant *value);
    std::map<JsonVariant *, JsonVariant *> getDynamicNodeProperties() const;
    void setDynamicNodeProperties(const std::map<JsonVariant *, JsonVariant *> &value);
    AMQPDistributionMode *getDistributionMode() const;
    void setDistributionMode(AMQPDistributionMode *value);
    std::map<JsonVariant *, JsonVariant *> getFilter() const;
    void setFilter(const std::map<JsonVariant *, JsonVariant *> &value);
    AMQPOutcome *getDefaultOutcome() const;
    void setDefaultOutcome(AMQPOutcome *value);
    std::list<JsonVariant *> getOutcomes() const;
    void setOutcomes(const std::list<JsonVariant *> &value);
    std::list<JsonVariant *> getCapabilities() const;
    void setCapabilities(const std::list<JsonVariant *> &value);
};

#endif // AMQPSOURCE_H
