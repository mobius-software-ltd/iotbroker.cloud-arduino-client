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

#include "amqpreceiversettlemode.h"

AMQPReceiverSettleMode::AMQPReceiverSettleMode()
{
    this->map = std::map<int, String>();
    this->map.insert(std::pair<int, String>(AMQP_FIRST_RECEIVER_SETTLE_MODE, AMQP_FIRST_RECEIVER_SETTLE_MODE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_SECOND_RECEIVER_SETTLE_MODE, AMQP_SECOND_RECEIVER_SETTLE_MODE_STRING));
}

AMQPReceiverSettleMode::AMQPReceiverSettleMode(int value) : AMQPReceiverSettleMode()
{
    this->value = value;
}

int AMQPReceiverSettleMode::getValue()
{
    return this->value;
}

String AMQPReceiverSettleMode::getName()
{
    return EnumObject::getName(this->value);
}
