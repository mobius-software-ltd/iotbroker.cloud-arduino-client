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

#include "amqptlvarray.h"

AMQPTLVArray::AMQPTLVArray() : TLVAMQP(new AMQPSimpleConstructor(new AMQPType(AMQP_ARRAY8_TYPE)))
{
    this->elements = NULL;
    this->width = 1;
    this->count = 0;
    this->size = 0;
}

AMQPTLVArray::AMQPTLVArray(AMQPType *type, vector<TLVAMQP *>elements) : TLVAMQP(new AMQPSimpleConstructor(type))
{
    this->elements = elements;
    this->width = type->getValue() == AMQP_ARRAY8_TYPE ? 1 : 4;
    this->size += this->width;

    foreach (TLVAMQP *element, this->elements) {
        this->size += element->getLength() - element->getConstructor()->getLength();
        if (this->elementContructor == NULL && element != NULL) {
            this->elementContructor = element->getConstructor();
        }
    }
    this->size = this->elementContructor->getLength();
    this->count = this->elements.size();
}

void AMQPTLVArray::addElement(TLVAMQP *element)
{
    if (this->elements.count() == 0) {
        this->elementContructor = element->getConstructor();
        this->size += this->width;
        this->size += this->elementContructor->getLength();
    }
    this->elements.push_back(element);
    this->count += 1;
    this->size += element->getLength() - this->elementContructor->getLength();
    if (this->width == 1 && this->size > 255) {
        this->constructor->setType(new AMQPType(AMQP_ARRAY32_TYPE));
        this->width = 4;
        this->size += 3;
    }
}

unsigned char * AMQPTLVArray::getData()
{
    unsigned char * sizeData;
    if (this->width == 1) {
        sizeData = malloc(sizeof(char));
        sizeData[0] = this->size;
    } else if (this->width == 4) {
        sizeData = malloc(sizeof(int));
        add_int(&sizeData[0], this->size);
    }

    unsigned char * countData;
    if (this->width == 1) {
        countData = malloc(sizeof(char));
        countData[0] = this->count;
    } else if (this->width == 4) {
        countData = malloc(sizeof(int));
        add_int(&countData[0], this->count);
    }

    unsigned char * elementConstructorData = this->elementContructor->getData();
    unsigned char *  valueData;
    unsigned char *  tlvData;

    foreach (TLVAMQP *item, this->elements) {
        int valueLength = item->getData().getSize() - elementConstructorData.getSize();
        unsigned char * sub = item->getData().subFrom(elementConstructorData.getSize(), valueLength);
        tlvData = sub;
        valueData = malloc(sizeof(tlvData) * sizeof(char));
        memcpy(&valueData[0], &tlvData[0], sizeof(tlvData));
    }

    unsigned char * bytes;
    if (this->size > 0) {
        bytes = malloc((sizeof(valueData) + sizeof(elementConstructorData) + sizeof(countData) + sizeof(sizeData) + sizeof(this->constructor->getData())) * sizeof(char));
        int i = 0;
        memcpy(&bytes[i], &this->constructor->getData()[0], sizeof(this->constructor->getData()));
        i += sizeof(this->constructor->getData());
        memcpy(&bytes[i], &sizeData[0], sizeof(sizeData));
        i += sizeof(sizeData);
        memcpy(&bytes[i], &countData[0], sizeof(countData));
        i += sizeof(countData);
        memcpy(&bytes[i], &elementConstructorData[0], sizeof(elementConstructorData));
        i += sizeof(elementConstructorData);
        memcpy(&bytes[i], &valueData[0], sizeof(valueData));
        i += sizeof(valueData);
    } else {
        bytes = malloc(sizeof(this->constructor->getData()) * sizeof(char));
        memcpy(&bytes[0], &this->constructor->getData()[0], sizeof(this->constructor->getData()));
    }

    return bytes;
}

String AMQPTLVArray::description()
{
    String result;

    foreach (TLVAMQP *item, this->elements) {
        result.append(item->description());
        result.append("\n");
    }

    return result;
}

int AMQPTLVArray::getLength()
{
    return this->constructor->getLength() + this->size + this->width;
}

unsigned char * AMQPTLVArray::getValue()
{
    unsigned char * bytes;
    bytes = malloc(sizeof(char));
    return bytes;
}

bool AMQPTLVArray::isNull()
{
    AMQPType *type = this->constructor->getType();
    if (type->getValue() == AMQP_NULL_TYPE) {
        return true;
    }
    if (type->getValue() == AMQP_ARRAY8_TYPE || type->getValue() == AMQP_ARRAY32_TYPE) {
        if (this->elements.count() == 0) {
            return true;
        }
    }
    return false;
}

int AMQPTLVArray::getWidth() const
{
    return width;
}

int AMQPTLVArray::getSize() const
{
    return size;
}

int AMQPTLVArray::getCount() const
{
    return count;
}

vector<TLVAMQP *> AMQPTLVArray::getElements() const
{
    return elements;
}

AMQPSimpleConstructor *AMQPTLVArray::getElementContructor() const
{
    return elementContructor;
}
