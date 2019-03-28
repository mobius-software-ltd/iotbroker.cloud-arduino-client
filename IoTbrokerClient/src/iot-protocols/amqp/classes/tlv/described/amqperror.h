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

#ifndef AMQPERROR_H
#define AMQPERROR_H

#include "iot-protocols/amqp/classes/enums/amqperrorcode.h"
#include "iot-protocols/amqp/classes/wrappers/amqpsymbol.h"
#include "iot-protocols/amqp/classes/tlv/compound/amqptlvlist.h"
#include <ArduinoJson.h>
#include <StandardCplusplus.h>
#include <map>
#include <cstring>
#include <cstdlib>
#include "utils/helpers.h"

class AMQPError
{
private:

    AMQPErrorCode *condition;
    String descriptionString;
    std::map<JsonVariant *, JsonVariant *> info;

public:
    AMQPError();

    void fill(AMQPTLVList *list);
    void addInfo(String key, JsonVariant *value);
    AMQPTLVList *getList();

    AMQPErrorCode *getCondition() const;
    void setCondition(AMQPErrorCode *value);

    String getDescriptionString() const;
    void setDescriptionString(const String &value);

    std::map<JsonVariant *, JsonVariant *> getInfo() const;
};

#endif // AMQPERROR_H
