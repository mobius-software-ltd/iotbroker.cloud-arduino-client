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

#ifndef AMQPMESSAGEHEADER_H
#define AMQPMESSAGEHEADER_H

#include <cstdlib>
#include "iot-protocols/amqp/classes/section/amqpsection.h"

class AMQPMessageHeader : public AMQPSection
{
private:

    JsonVariant *durable;
    JsonVariant *priority;
    JsonVariant *milliseconds;
    JsonVariant *firstAquirer;
    JsonVariant *deliveryCount;

public:
    AMQPMessageHeader();

    virtual TLVAMQP *getValue();
    virtual AMQPSectionCode *getCode();

    virtual void fill(TLVAMQP *value);

    JsonVariant *getDurable() const;
    void setDurable(JsonVariant *value);
    JsonVariant *getPriority() const;
    void setPriority(JsonVariant *value);
    JsonVariant *getMilliseconds() const;
    void setMilliseconds(JsonVariant *value);
    JsonVariant *getFirstAquirer() const;
    void setFirstAquirer(JsonVariant *value);
    JsonVariant *getDeliveryCount() const;
    void setDeliveryCount(JsonVariant *value);
};

#endif // AMQPMESSAGEHEADER_H
