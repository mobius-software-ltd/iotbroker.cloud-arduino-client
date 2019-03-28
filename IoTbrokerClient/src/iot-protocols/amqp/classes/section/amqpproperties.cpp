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

#include "amqpproperties.h"
#include "iot-protocols/amqp/classes/headerapi/amqpwrapper.h"
#include "iot-protocols/amqp/classes/headerapi/amqpunwrapper.h"
#include "iot-protocols/amqp/classes/constructors/amqpdescribedconstructor.h"
#include "iot-protocols/amqp/classes/wrappers/messageID/amqpbinaryid.h"
#include "iot-protocols/amqp/classes/wrappers/messageID/amqplongid.h"
#include "iot-protocols/amqp/classes/wrappers/messageID/amqpmessageid.h"
#include "iot-protocols/amqp/classes/wrappers/messageID/amqpstringid.h"
#include "iot-protocols/amqp/classes/wrappers/messageID/amqpuuid.h"

AMQPProperties::AMQPProperties()
{

}

TLVAMQP *AMQPProperties::getValue()
{
    AMQPTLVList *list = new AMQPTLVList();

    if (this->messageId != NULL) {
        JsonVariant *object = NULL;
        if (this->messageId->getBinary() != NULL) {
            object = AMQPSimpleType::binaryToVariant(this->messageId->getBinary());
        } else if (this->messageId->getLongValue() != NULL) {
            object = AMQPSimpleType::longToVariant(this->messageId->getLongValue());
        } else if (this->messageId->getString() != NULL) {
            object = AMQPSimpleType::stringToVariant(this->messageId->getString());
        } else if (this->messageId->getUUID() != NULL) {
            object = AMQPSimpleType::uuidToVariant(this->messageId->getUUID());
        }
        list->addElementWithIndex(0, AMQPWrapper::wrapObject(object));
    }
    if (this->userId != NULL) {
        list->addElementWithIndex(1, AMQPWrapper::wrapBinary(this->userId));
    }
    if (this->to != NULL) {
        list->addElementWithIndex(2, AMQPWrapper::wrapString(this->to));
    }
    if (this->subject != NULL) {
        list->addElementWithIndex(3, AMQPWrapper::wrapString(this->subject));
    }
    if (this->replyTo != NULL) {
        list->addElementWithIndex(4, AMQPWrapper::wrapString(this->replyTo));
    }
    if (this->correlationID != NULL) {
        list->addElementWithIndex(5, AMQPWrapper::wrapBinary(this->correlationID));
    }
    if (this->contentType != NULL) {
        list->addElementWithIndex(6, AMQPWrapper::wrapString(this->contentType));
    }
    if (this->contentEncoding != NULL) {
        list->addElementWithIndex(7, AMQPWrapper::wrapString(this->contentEncoding));
    }
    if (this->absoluteExpiryTime != NULL) {
        list->addElementWithIndex(8, AMQPWrapper::wrapTimestamp(this->absoluteExpiryTime));
    }
    if (this->creationTime != NULL) {
        list->addElementWithIndex(9, AMQPWrapper::wrapTimestamp(this->creationTime));
    }
    if (this->groupId != NULL) {
        list->addElementWithIndex(10, AMQPWrapper::wrapString(this->groupId));
    }
    if (this->groupSequence != NULL) {
        list->addElementWithIndex(11, AMQPWrapper::wrapUInt(AMQPSimpleType::variantToUInt(this->groupSequence)));
    }
    if (this->replyToGroupId != NULL) {
        list->addElementWithIndex(12, AMQPWrapper::wrapString(this->replyToGroupId));
    }

    unsigned char * data = NULL;
    data = malloc(sizeof(char));
    data[0] = (char) 0x73;
    AMQPType *type = new AMQPType(AMQP_SMALL_ULONG_TYPE);
    AMQPTLVFixed *fixed = new AMQPTLVFixed(type, data);

    AMQPType *constructorType = new AMQPType(list->getTypeValue());
    AMQPDescribedConstructor *constructor = new AMQPDescribedConstructor(constructorType, fixed);

    list->setConstructor(constructor);
    return list;
}

AMQPSectionCode *AMQPProperties::getCode()
{
    return new AMQPSectionCode(AMQP_PROPERTIES_SECTION_CODE);
}

void AMQPProperties::fill(TLVAMQP *value)
{
    AMQPTLVList *list = new AMQPTLVList();

    if (list->getList().size() > 0) {
        TLVAMQP *element = list->getList()[0];
        if (!element->isNull()) {
            switch (element->getTypeValue()) {
                case AMQP_ULONG0_TYPE:
                case AMQP_SMALL_ULONG_TYPE:
                case AMQP_ULONG_TYPE:
                {
                    long long value = AMQPUnwrapper::unwrapLong(element);
                    JsonVariant variant;
                    variant.set(value);
                    this->messageId = new AMQPLongID(variant);
                } break;
                case AMQP_STRING8_TYPE:
                case AMQP_STRING32_TYPE:
                {
                    this->messageId = new AMQPStringID(AMQPUnwrapper::unwrapString(element));
                } break;
                case AMQP_BINARY8_TYPE:
                case AMQP_BINARY32_TYPE:
                {
                    this->messageId = new AMQPBinaryID(AMQPUnwrapper::unwrapBinary(element));
                } break;
                case AMQP_UUID_TYPE:
                {
                    this->messageId = new AMQPUUID(AMQPUnwrapper::unwrapUUID(element));
                } break;
                default: break;
            }
        }
    }
    if (list->getList().size() > 1) {
        TLVAMQP *element = list->getList()[1];
        if (!element->isNull()) {
            this->userId = AMQPUnwrapper::unwrapBinary(element);
        }
    }
    if (list->getList().size() > 2) {
        TLVAMQP *element = list->getList()[2];
        if (!element->isNull()) {
            this->to = AMQPUnwrapper::unwrapString(element);
        }
    }
    if (list->getList().size() > 3) {
        TLVAMQP *element = list->getList()[3];
        if (!element->isNull()) {
            this->subject = AMQPUnwrapper::unwrapString(element);
        }
    }
    if (list->getList().size() > 4) {
        TLVAMQP *element = list->getList()[4];
        if (!element->isNull()) {
            this->replyTo = AMQPUnwrapper::unwrapString(element);
        }
    }
    if (list->getList().size() > 5) {
        TLVAMQP *element = list->getList()[5];
        if (!element->isNull()) {
            this->correlationID = AMQPUnwrapper::unwrapBinary(element);
        }
    }
    if (list->getList().size() > 6) {
        TLVAMQP *element = list->getList()[6];
        if (!element->isNull()) {
            this->contentType = AMQPUnwrapper::unwrapString(element);
        }
    }
    if (list->getList().size() > 7) {
        TLVAMQP *element = list->getList()[7];
        if (!element->isNull()) {
            this->contentEncoding = AMQPUnwrapper::unwrapString(element);
        }
    }
    if (list->getList().size() > 8) {
        TLVAMQP *element = list->getList()[8];
        if (!element->isNull()) {
            this->absoluteExpiryTime = AMQPUnwrapper::unwrapTimestamp(element);
        }
    }
    if (list->getList().size() > 9) {
        TLVAMQP *element = list->getList()[9];
        if (!element->isNull()) {
            this->creationTime = AMQPUnwrapper::unwrapTimestamp(element);
        }
    }
    if (list->getList().size() > 10) {
        TLVAMQP *element = list->getList()[10];
        if (!element->isNull()) {
            this->groupId = AMQPUnwrapper::unwrapUInt(element);
        }
    }
    if (list->getList().size() > 11) {
        TLVAMQP *element = list->getList()[11];
        if (!element->isNull()) {
            this->groupSequence = AMQPSimpleType::UIntToVariant(AMQPUnwrapper::unwrapUInt(element));
        }
    }
    if (list->getList().size() > 12) {
        TLVAMQP *element = list->getList()[12];
        if (!element->isNull()) {
            this->replyToGroupId = AMQPUnwrapper::unwrapString(element);
        }
    }
}

AMQPMessageID *AMQPProperties::getMessageId() const
{
    return messageId;
}

void AMQPProperties::setMessageId(AMQPMessageID *value)
{
    messageId = value;
}

unsigned char * AMQPProperties::getUserId() const
{
    return userId;
}

void AMQPProperties::setUserId(const unsigned char &value)
{
    userId = value;
}

String AMQPProperties::getTo() const
{
    return to;
}

void AMQPProperties::setTo(const String &value)
{
    to = value;
}

String AMQPProperties::getSubject() const
{
    return subject;
}

void AMQPProperties::setSubject(const String &value)
{
    subject = value;
}

String AMQPProperties::getReplyTo() const
{
    return replyTo;
}

void AMQPProperties::setReplyTo(const String &value)
{
    replyTo = value;
}

unsigned char * AMQPProperties::getCorrelationID() const
{
    return correlationID;
}

void AMQPProperties::setCorrelationID(const unsigned char &value)
{
    correlationID = value;
}

String AMQPProperties::getContentType() const
{
    return contentType;
}

void AMQPProperties::setContentType(const String &value)
{
    contentType = value;
}

String AMQPProperties::getContentEncoding() const
{
    return contentEncoding;
}

void AMQPProperties::setContentEncoding(const String &value)
{
    contentEncoding = value;
}

time_t AMQPProperties::getAbsoluteExpiryTime() const
{
    return absoluteExpiryTime;
}

void AMQPProperties::setAbsoluteExpiryTime(const time_t &value)
{
    absoluteExpiryTime = value;
}

time_t AMQPProperties::getCreationTime() const
{
    return creationTime;
}

void AMQPProperties::setCreationTime(const time_t &value)
{
    creationTime = value;
}

String AMQPProperties::getGroupId() const
{
    return groupId;
}

void AMQPProperties::setGroupId(const String &value)
{
    groupId = value;
}

JsonVariant *AMQPProperties::getGroupSequence() const
{
    return groupSequence;
}

void AMQPProperties::setGroupSequence(JsonVariant *value)
{
    groupSequence = value;
}

String AMQPProperties::getReplyToGroupId() const
{
    return replyToGroupId;
}

void AMQPProperties::setReplyToGroupId(const String &value)
{
    replyToGroupId = value;
}
