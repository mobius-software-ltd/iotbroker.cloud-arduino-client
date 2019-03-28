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

#include "amqptlvlist.h"
#include "iot-protocols/amqp/classes/tlv/fixed/amqptlvnull.h"
#include "iot-protocols/amqp/classes/tlv/compound/amqptlvmap.h"
#include "iot-protocols/amqp/classes/tlv/array/amqptlvarray.h"

AMQPTLVList::AMQPTLVList() : TLVAMQP(new AMQPSimpleConstructor(new AMQPType(AMQP_LIST0_TYPE)))
{
    this->list = NULL;
    this->width = 0;
    this->count = 0;
    this->size = 0;
}

AMQPTLVList::AMQPTLVList(AMQPType *type, std::vector<TLVAMQP *> value) : TLVAMQP(new AMQPSimpleConstructor(type))
{
    this->list = value;
    this->width = type->getValue() == AMQP_LIST8_TYPE ? 1 : 4;
    this->size += this->width;
    foreach (TLVAMQP *item, this->list) {
        this->size += item->getLength();
    }
    this->count = this->list.count();
}

void AMQPTLVList::addElement(TLVAMQP *element)
{
    if (this->size == 0) {
        this->constructor->setType(new AMQPType(AMQP_LIST8_TYPE));
        this->width = 1;
        this->size += 1;
    }
    this->list.push_back(element);
    this->count += 1;
    this->size += element->getLength();
    this->update();
}

void AMQPTLVList::setElementWithIndex(int index, TLVAMQP *element)
{
    this->size -= this->list[index]->getLength();
    this->list[index] = element;
    this->size += element->getLength();
    this->update();
}

void AMQPTLVList::addElementWithIndex(int index, TLVAMQP *element)
{
    int diff = (int)(index - this->list.size());
    do {
        this->addElement(new AMQPTLVNull());
    } while (diff-- > 0);
    this->setElementWithIndex(index, element);
}

void AMQPTLVList::addToListWithIndex(int index, int elementIndex, TLVAMQP *element)
{
    if (this->count <= index) {
        this->addElementWithIndex(index, new AMQPTLVList());
    }
    TLVAMQP *list = this->list[index];
    if (list->isNull()) {
        this->setElementWithIndex(index, new AMQPTLVList());
    }
    ((AMQPTLVList *)this->list[index])->addElementWithIndex(elementIndex, element);
    this->size += element->getLength();
    this->update();
}

void AMQPTLVList::addToMapWithIndex(int index, TLVAMQP *key, TLVAMQP *value)
{
    if (this->count <= index) {
        this->addElementWithIndex(index, new AMQPTLVMap());
    }
    TLVAMQP *map = this->list[index];
    if (map->isNull()) {
        this->setElementWithIndex(index, new AMQPTLVMap());
    }
    ((AMQPTLVMap *)this->list[index])->putElement(key, value);
    this->size += key->getLength() + value->getLength();
    this->update();
}

void AMQPTLVList::addToArrayWithIndex(int index, TLVAMQP *element)
{
    if (this->count <= index) {
        this->addElementWithIndex(index, new AMQPTLVArray());
    }
    TLVAMQP *array = this->list[index];
    if (array->isNull()) {
        this->setElementWithIndex(index, new AMQPTLVArray());
    }
    ((AMQPTLVArray *)this->list[index])->addElement(element);
    this->size += element->getLength();
    this->update();
}

unsigned char * AMQPTLVList::getData()
{
    unsigned char * sizeData;

    if (this->width == 1) {
        sizeData = malloc(sizeof(char));
        sizeData[0] = this->size;
    } else {
        sizeData = malloc(sizeof(int));
        add_int(&sizeData[0], this->size);
    }

    unsigned char * countBytes;
    if (this->width == 1) {
        countBytes = malloc(sizeof(char));
        countBytes[0] = this->count;
    } else {
        countBytes = malloc(sizeof(int));
        add_int(&countBytes[0], this->count);
    }

    unsigned char *  valueData;
    foreach (TLVAMQP *item, this->list) {
        valueData = malloc(sizeof(item->getData()) * sizeof(char));
        memcpy(&valueData[0], &item->getData()[0], sizeof(item->getData()));
    }

    unsigned char * bytes;
    if (this->size > 0) {
        bytes = malloc((sizeof(valueData) + sizeof(countBytes) + sizeof(sizeData) + sizeof(this->constructor->getData())) * sizeof(char));
        int i = 0;
        memcpy(&bytes[i], &this->constructor->getData()[0], sizeof(this->constructor->getData()));
        i += sizeof(this->constructor->getData());
        memcpy(&bytes[i], &sizeData[0], sizeof(sizeData));
        i += sizeof(sizeData);
        memcpy(&bytes[i], &countBytes[0], sizeof(countBytes));
        i += sizeof(countBytes);
        memcpy(&bytes[i], &valueData[0], sizeof(valueData));
        i += sizeof(valueData);
    } else {
        bytes = malloc(sizeof(this->constructor->getData()) * sizeof(char));
        memcpy(&bytes[0], &this->constructor->getData()[0], sizeof(this->constructor->getData()));
    }

    return bytes;
}

int AMQPTLVList::getLength()
{
    return this->constructor->getLength() + this->width + this->size;
}

unsigned char * AMQPTLVList::getValue()
{
    unsigned char * bytes;
    bytes = malloc(sizeof(char));
    return bytes;
}

String AMQPTLVList::description()
{
    String result;
    foreach(TLVAMQP *item, this->list) {
        result.append(item->description());
        result.append("\n");
    }
    return result;
}

int AMQPTLVList::getWidth() const
{
    return width;
}

int AMQPTLVList::getSize() const
{
    return size;
}

int AMQPTLVList::getCount() const
{
    return count;
}

std::vector<TLVAMQP *> AMQPTLVList::getList() const
{
    return list;
}

void AMQPTLVList::update()
{
    if (this->width == 1 && this->size > 255) {
        this->constructor->setType(new AMQPType(AMQP_LIST32_TYPE));
        this->width = 4;
        this->size += 3;
    }
}
