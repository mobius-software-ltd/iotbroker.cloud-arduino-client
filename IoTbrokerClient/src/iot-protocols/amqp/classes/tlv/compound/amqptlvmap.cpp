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

#include "amqptlvmap.h"

AMQPTLVMap::AMQPTLVMap() : TLVAMQP(new AMQPSimpleConstructor(new AMQPType(AMQP_MAP8_TYPE)))
{
    this->map = map<TLVAMQP *, TLVAMQP *>();
    this->width = 1;
    this->size = 1;
    this->count = 0;
}

AMQPTLVMap::AMQPTLVMap(AMQPType *type, map<TLVAMQP *, TLVAMQP *> map) : TLVAMQP(new AMQPSimpleConstructor(type))
{
    this->map = map;
    this->width = (type->getValue() == AMQP_MAP8_TYPE) ? 1 : 4;
    this->size += this->width;

    for(map<TLVAMQP *, TLVAMQP *>::iterator it = map.begin(); it != map.end(); ++it) {
        this->size += it->first->getLength();
        this->size += it->second->getLength();
    }
    this->count = this->map.count();
}

void AMQPTLVMap::putElement(TLVAMQP *key, TLVAMQP *value)
{
    this->map.insert(std::pair<TLVAMQP *, TLVAMQP *>(key, value));
    this->size += key->getLength() + value->getLength();
    this->count += 1;
    this->update();
}

String AMQPTLVMap::description()
{
    String result;

    for(map<TLVAMQP *, TLVAMQP *>::iterator it = this.map.begin(); it != this.map.end(); ++it) {
        result.append(it->first->description());
        result.append(" : ");
        result.append(it->second->description());
        result.append(" \n ");
    }
    return result;
}

unsigned char * AMQPTLVMap::getData()
{
    unsigned char * sizeData;

    if (this->width == 1) {
        sizeData = malloc(sizeof(char));
        sizeData[0] = this->size;
    } else {
        sizeData = malloc(sizeof(int));
        add_int(&sizeData[0], this->size);
    }

    unsigned char * countData;
    if (this->width == 1) {
        countData = malloc(sizeof(char));
        countData[0] = this->count * 2;
    } else {
        countData = malloc(sizeof(int));
        add_int(&countData[0], this->count * 2);
    }

    unsigned char * valueData;
    for(map<TLVAMQP *, TLVAMQP *>::iterator it = this.map.begin(); it != this.map.end(); ++it) {
        TLVAMQP *value = it.second;
        valueData.writeRawData(it.first->getData());
        valueData.writeRawData(value->getData());
    }

    unsigned char * bytes;
    if (this->size > 0) {
        bytes = malloc((sizeof(valueData) + sizeof(countData) + sizeof(sizeData) + sizeof(this->constructor->getData())) * sizeof(char));
        int i = 0;
        memcpy(&bytes[i], &this->constructor->getData()[0], sizeof(this->constructor->getData()));
        i += sizeof(this->constructor->getData());
        memcpy(&bytes[i], &sizeData[0], sizeof(sizeData));
        i += sizeof(sizeData);
        memcpy(&bytes[i], &countBytes[0], sizeof(countData));
        i += sizeof(countBytes);
        memcpy(&bytes[i], &valueData[0], sizeof(valueData));
        i += sizeof(valueData);
    }else {
        bytes = malloc(sizeof(this->constructor->getData()) * sizeof(char));
        memcpy(&bytes[0], &this->constructor->getData()[0], sizeof(this->constructor->getData()));
    }
    return bytes;
}

int AMQPTLVMap::getLength()
{
    return this->constructor->getLength() + this->width + this->size;
}

unsigned char * AMQPTLVMap::getValue()
{
    unsigned char * bytes;
    bytes = malloc(sizeof(char));
    return bytes;
}

int AMQPTLVMap::getWidth() const
{
    return width;
}

int AMQPTLVMap::getSize() const
{
    return size;
}

int AMQPTLVMap::getCount() const
{
    return count;
}

map<TLVAMQP *, TLVAMQP *> AMQPTLVMap::getMap() const
{
    return map;
}

void AMQPTLVMap::update()
{
    if (this->width == 1 && this->size > 255) {
        this->constructor->setType(new AMQPType(AMQP_MAP32_TYPE));
        this->width = 4;
        this->size + 3;
    }
}
