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

#ifndef SNWILLTOPICUPD_H
#define SNWILLTOPICUPD_H

#include "iot-protocols/mqtt-sn/classes/topics/snfulltopic.h"
#include "iot-protocols/classes/message.h"
#include "iot-protocols/mqtt-sn/classes/mqttsnenums.h"

class SNWillTopicUpd : public Message
{
private:

    SNFullTopic *topic;
    bool isRetain;

public:
    SNWillTopicUpd();
    SNWillTopicUpd(SNFullTopic *topic, bool isRetain);

    virtual int getLength();
    virtual int getType();
    virtual IotEnumProtocol *getProtocol();

    SNFullTopic *getTopic() const;
    void setTopic(SNFullTopic *value);

    bool getIsRetain() const;
    void setIsRetain(bool value);
};

#endif // SNWILLTOPICUPD_H
