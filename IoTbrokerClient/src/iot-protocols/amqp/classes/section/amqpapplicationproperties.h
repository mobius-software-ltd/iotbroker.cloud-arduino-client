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

#ifndef AMQPAPPLICATIONPROPERTIES_H
#define AMQPAPPLICATIONPROPERTIES_H

#include "iot-protocols/amqp/classes/section/amqpsection.h"
#include <map>
#include <cstdlib>

class AMQPApplicationProperties : public AMQPSection
{
private:

    map<JsonVariant *, JsonVariant *> properties;

public:
    AMQPApplicationProperties();

    virtual TLVAMQP *getValue();
    virtual AMQPSectionCode *getCode();

    virtual void fill(TLVAMQP *value);

    void addProperty(String key, JsonVariant *value);
};

#endif // AMQPAPPLICATIONPROPERTIES_H
