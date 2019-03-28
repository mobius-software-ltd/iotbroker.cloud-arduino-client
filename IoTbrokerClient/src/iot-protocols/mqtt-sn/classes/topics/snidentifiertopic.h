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

#ifndef SNIDENTIFIERTOPIC_H
#define SNIDENTIFIERTOPIC_H

#include "iot-protocols/classes/topic.h"

class SNIdentifierTopic : public Topic
{

private:

    int value;
    QoS *qos;

public:
    SNIdentifierTopic();
    SNIdentifierTopic(int, QoS *);

    virtual SNTopicTypes getType();
    virtual QoS *getQoS();
    virtual unsigned char * encode();
    virtual int getLength();
};

#endif // SNIDENTIFIERTOPIC_H
