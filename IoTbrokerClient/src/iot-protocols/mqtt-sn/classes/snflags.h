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

#ifndef SNFLAGS_H
#define SNFLAGS_H

#include "iot-protocols/mqtt-sn/classes/mqttsnenums.h"
#include "iot-protocols/classes/message.h"
#include "iot-protocols/classes/topic.h"
#include "iot-protocols/classes/qos.h"
#include <list>
#include <algorithm>

enum SNFlag : int
{
    SN_DUPLICATE_FLAG = 128,
    SN_QOS_LEVEL_ONE_FLAG = 96,
    SN_QOS_2_FLAG = 64,
    SN_QOS_1_FLAG = 32,
    SN_RETAIN_FLAG = 16,
    SN_WILL_FLAG = 8,
    SN_CLEAN_SESSION_FLAG = 4,
    SN_RESERVED_TOPIC_FLAG = 3,
    SN_SHORT_TOPIC_FLAG = 2,
    SN_ID_TOPIC_FLAG = 1
};

class SNFlags
{
private:

    bool isDup;
    QoS *qos;
    bool isRetain;
    bool will;
    bool cleanSession;
    SNTopicTypes topicType;

public:
    SNFlags();
    SNFlags(bool isDup, QoS *qos, bool isRetain, bool will, bool cleanSession, SNTopicTypes topicType);

    static SNFlags *decode(unsigned char flagsByte, SNMessageType type);
    static SNFlags *validateAndCreate(list<SNFlag> bitMask, SNMessageType type);
    static unsigned char encode(bool isDup, QoS *qos, bool isRetain, bool will, bool cleanSession, SNTopicTypes topicType);

    bool getIsDup() const;
    void setIsDup(bool value);

    QoS *getQos() const;
    void setQos(QoS *value);

    bool getIsRetain() const;
    void setIsRetain(bool value);

    bool getWill() const;
    void setWill(bool value);

    bool getCleanSession() const;
    void setCleanSession(bool value);

    SNTopicTypes getTopicType() const;
    void setTopicType(const SNTopicTypes &value);
};

#endif // SNFLAGS_H
