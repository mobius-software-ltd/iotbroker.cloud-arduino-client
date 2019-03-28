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

#ifndef AMQPDISTRIBUTIONMODE_H
#define AMQPDISTRIBUTIONMODE_H

#include <map>
#include "iot-protocols/amqp/classes/enums/enumobject.h"

enum AMQPDistributionModes
{
    AMQP_MOVE_DISTRIBUTION_MODE = 0,
    AMQP_COPY_DISTRIBUTION_MODE = 1,
};

static String const AMQP_MOVE_DISTRIBUTION_MODE_STRING = "move";
static String const AMQP_COPY_DISTRIBUTION_MODE_STRING = "copy";

class AMQPDistributionMode : public EnumObject
{
private:

    int value;

public:
    AMQPDistributionMode();
    AMQPDistributionMode(int value);

    int getValue();
    String getName();
};

#endif // AMQPDISTRIBUTIONMODE_H
