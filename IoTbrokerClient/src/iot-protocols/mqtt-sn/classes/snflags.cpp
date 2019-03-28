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

#include "snflags.h"

SNFlags::SNFlags()
{

}

SNFlags::SNFlags(bool isDup, QoS *qos, bool isRetain, bool will, bool cleanSession, SNTopicTypes topicType)
{
    this->isDup = isDup;
    this->qos = qos;
    this->isRetain = isRetain;
    this->will = will;
    this->cleanSession = cleanSession;
    this->topicType = topicType;
}

SNFlags *SNFlags::decode(unsigned char flagsByte, SNMessageType type)
{
    list<SNFlag> flags;

    flags.append(SN_DUPLICATE_FLAG);
    flags.append(SN_QOS_LEVEL_ONE_FLAG);
    flags.append(SN_QOS_2_FLAG);
    flags.append(SN_QOS_1_FLAG);
    flags.append(SN_RETAIN_FLAG);
    flags.append(SN_WILL_FLAG);
    flags.append(SN_CLEAN_SESSION_FLAG);
    flags.append(SN_RESERVED_TOPIC_FLAG);
    flags.append(SN_SHORT_TOPIC_FLAG);
    flags.append(SN_ID_TOPIC_FLAG);

    list<SNFlag> bitmask;

    foreach (SNFlag flag, flags) {
        if ((flagsByte & flag) == flag) {
            bitmask.append(flag);
        }
    }

    return SNFlags::validateAndCreate(bitmask, type);
}

SNFlags *SNFlags::validateAndCreate(list<SNFlag> bitMask, SNMessageType type)
{
    it = find(bitmask.begin(), bitmask.end(), SN_RESERVED_TOPIC_FLAG);

    if (it != bitmask.end()) {
        printf("Error. Reserved flag set to true in SNFlags");
    }

    bool dup = bitMask.contains(SN_DUPLICATE_FLAG);
    bool retain = bitMask.contains(SN_RETAIN_FLAG);
    bool will = bitMask.contains(SN_WILL_FLAG);
    bool cleanSession = bitMask.contains(SN_CLEAN_SESSION_FLAG);

    QoS *qos = NULL;
    qos = new QoS(AT_MOST_ONCE);

    it = find(bitmask.begin(), bitmask.end(), SN_QOS_LEVEL_ONE_FLAG);
    if (it != bitmask.end()) {
        qos = new QoS(LEVEL_ONE);
    it = find(bitmask.begin(), bitmask.end(), SN_QOS_2_FLAG);
    if (it != bitmask.end()) {
        qos = new QoS(EXACTLY_ONCE);
    }
    it = find(bitmask.begin(), bitmask.end(), SN_QOS_1_FLAG);
    if (it != bitmask.end()) {
        qos = new QoS(AT_LEAST_ONCE);
    }

    SNTopicTypes topicType = SN_UNKNOWN_TOPIC_TYPE;
    topicType = SN_NAMED_TOPIC_TYPE;
    it = find(bitmask.begin(), bitmask.end(), SN_SHORT_TOPIC_FLAG);
    if (it != bitmask.end()) {
        topicType = SN_SHORT_TOPIC_TYPE;
    } else
    it = find(bitmask.begin(), bitmask.end(), SN_ID_TOPIC_FLAG);
    if (it != bitmask.end()) {
        topicType = SN_ID_TOPIC_TYPE;
    }

    switch(type) {
        case SN_CONNECT:
        {
            if (dup == true) {
                printf("Error. SNFlags. Invalid encoding: dup flag = " + type);
            }
            if (qos->getValue() != AT_MOST_ONCE) {
                printf("Error. SNFlags. Invalid encoding: qos flag = " + type);
            }
            if (retain == true) {
                printf("Error. SNFlags. Invalid encoding: retain flag = " + type);
            }
            if (topicType != SN_NAMED_TOPIC_TYPE) {
                printf("Error. SNFlags. Invalid encoding: topicType = " + topicType);
            }
        } break;

        case SN_WILLTOPIC:
        {
            if (dup == true) {
                printf("Error. SNFlags. Invalid encoding: dup flag = " + type);
            }
            if (qos == NULL) {
                printf("Error. SNFlags. Invalid encoding: qos flag = " + type);
            }
            if (will == true) {
                printf("Error. SNFlags. Invalid encoding: will flag = " + type);
            }
            if (cleanSession == true) {
                printf("Error. SNFlags. Invalid encoding: cleanSession flag = " + type);
            }
            if (topicType != SN_NAMED_TOPIC_TYPE) {
                printf("Error. SNFlags. Invalid encoding: topicType = " + topicType);
            }
        } break;

        case SN_PUBLISH:
        {
            if (qos == NULL) {
                printf("Error. SNFlags. Invalid encoding: qos flag = " + type);
            }
            if (topicType == SN_UNKNOWN_TOPIC_TYPE) {
                printf("Error. SNFlags. Invalid encoding: topicType = " + topicType);
            }
            if (will == true) {
                printf("Error. SNFlags. Invalid encoding: will flag = " + type);
            }
            if (cleanSession == true) {
                printf("Error. SNFlags. Invalid encoding: cleanSession flag = " + type);
            }
            if (dup && (qos->getValue() == AT_MOST_ONCE || qos->getValue() == LEVEL_ONE)) {
                printf("Error. SNFlags. Invalid encoding: dup flag with invalid qos = " + qos->getValue());
            }
        } break;

        case SN_SUBSCRIBE:
        {
            if (qos == NULL) {
                printf("Error. SNFlags. Invalid encoding: qos flag = " + type);
            }
            if (qos->getValue() == LEVEL_ONE) {
                printf("Error. SNFlags. Invalid encoding: qos = " + qos->getValue());
            }
            if (retain == true) {
                printf("Error. SNFlags. Invalid encoding: retain flag = " + type);
            }
            if (will == true) {
                printf("Error. SNFlags. Invalid encoding: will flag = " + type);
            }
            if (cleanSession == true) {
                printf("Error. SNFlags. Invalid encoding: cleanSession flag = " + type);
            }
            if (topicType == SN_UNKNOWN_TOPIC_TYPE) {
                printf("Error. SNFlags. Invalid encoding: topicType = " + topicType);
            }
        }

        case SN_SUBACK:
        {
            if (dup == true) {
                printf("Error. SNFlags. Invalid encoding: dup flag = " + type);
            }
            if (qos == NULL) {
                printf("Error. SNFlags. Invalid encoding: qos flag = " + type);
            }
            if (retain == true) {
                printf("Error. SNFlags. Invalid encoding: retain flag = " + type);
            }
            if (will == true) {
                printf("Error. SNFlags. Invalid encoding: will flag = " + type);
            }
            if (cleanSession == true) {
                printf("Error. SNFlags. Invalid encoding: cleanSession flag = " + type);
            }
            if (topicType != SN_NAMED_TOPIC_TYPE) {
                printf("Error. SNFlags. Invalid encoding: topicType = " + topicType);
            }
        } break;

        case SN_UNSUBSCRIBE:
        {
            if (dup == true) {
                printf("Error. SNFlags. Invalid encoding: dup flag = " + type);
            }
            if (qos->getValue() != AT_MOST_ONCE) {
                printf("Error. SNFlags. Invalid encoding: qos = " + qos->getValue());
            }
            if (retain == true) {
                printf("Error. SNFlags. Invalid encoding: retain flag = " + type);
            }
            if (will == true) {
                printf("Error. SNFlags. Invalid encoding: will flag = " + type);
            }
            if (cleanSession == true) {
                printf("Error. SNFlags. Invalid encoding: cleanSession flag = " + type);
            }
            if (topicType == SN_UNKNOWN_TOPIC_TYPE) {
                printf("Error. SNFlags. Invalid encoding: topicType = " + topicType);
            }
        } break;

        case SN_WILLTOPICUPD:
        {
            if (dup == true) {
                printf("Error. SNFlags. Invalid encoding: dup flag = " + type);
            }
            if (qos == NULL) {
                printf("Error. SNFlags. Invalid encoding: qos flag = " + type);
            }
            if (will == true) {
                printf("Error. SNFlags. Invalid encoding: will flag = " + type);
            }
            if (cleanSession == true) {
                printf("Error. SNFlags. Invalid encoding: cleanSession flag = " + type);
            }
            if (topicType != SN_NAMED_TOPIC_TYPE) {
                printf("Error. SNFlags. Invalid encoding: topicType = " + type);
            }
        } break;

        default: break;
    }

    return new SNFlags(dup, qos, retain, will, cleanSession, topicType);
}

unsigned char SNFlags::encode(bool isDup, QoS *qos, bool isRetain, bool will, bool cleanSession, SNTopicTypes topicType)
{
    unsigned char flagsByte = 0;

    if (isDup == true) {
        flagsByte += SN_DUPLICATE_FLAG;
    }
    if (qos != NULL) {
        flagsByte += qos->getValue() << 5;
    }
    if (isRetain == true) {
        flagsByte += SN_RETAIN_FLAG;
    }
    if (will == true) {
        flagsByte += SN_WILL_FLAG;
    }
    if (cleanSession == true) {
        flagsByte += SN_CLEAN_SESSION_FLAG;
    }
    if (topicType != SN_UNKNOWN_TOPIC_TYPE) {
        flagsByte += topicType;
    }
    return flagsByte;
}

bool SNFlags::getIsDup() const
{
    return isDup;
}

void SNFlags::setIsDup(bool value)
{
    isDup = value;
}

QoS *SNFlags::getQos() const
{
    return qos;
}

void SNFlags::setQos(QoS *value)
{
    qos = value;
}

bool SNFlags::getIsRetain() const
{
    return isRetain;
}

void SNFlags::setIsRetain(bool value)
{
    isRetain = value;
}

bool SNFlags::getWill() const
{
    return will;
}

void SNFlags::setWill(bool value)
{
    will = value;
}

bool SNFlags::getCleanSession() const
{
    return cleanSession;
}

void SNFlags::setCleanSession(bool value)
{
    cleanSession = value;
}

SNTopicTypes SNFlags::getTopicType() const
{
    return topicType;
}

void SNFlags::setTopicType(const SNTopicTypes &value)
{
    topicType = value;
}
