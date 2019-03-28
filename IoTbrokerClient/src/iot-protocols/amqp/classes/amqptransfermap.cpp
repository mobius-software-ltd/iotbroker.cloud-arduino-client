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

#include "amqptransfermap.h"
#include "iot-protocols/amqp/classes/amqpsimpletype.h"

AMQPTransferMap::AMQPTransferMap()
{
    this->index = 0;
    this->transfers = map<int, AMQPTransfer *>();
}

AMQPTransfer *AMQPTransferMap::addTransfer(AMQPTransfer *item)
{
    int number = this->index;

    item->setDeliveryId(AMQPSimpleType::intToVariant(number));
    this->transfers.insert(std::pair<int, AMQPTransfer *>(this->index,item));

    this->newIndex();

    return item;
}

AMQPTransfer *AMQPTransferMap::removeTransferByDeliveryId(int Id)
{
    AMQPTransfer *item = this->transfers[Id];

    if (item != NULL) {
        //this->transfers.remove(Id);
    }
    return item;
}

map<int, AMQPTransfer *> AMQPTransferMap::getTransfers() const
{
    return transfers;
}

void AMQPTransferMap::newIndex()
{
    this->index++;

    if (this->index == 65535) {
        this->index = 1;
    }
}
