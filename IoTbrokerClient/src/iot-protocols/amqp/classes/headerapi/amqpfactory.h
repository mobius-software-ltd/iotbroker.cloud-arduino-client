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

#ifndef AMQPFACTORY_H
#define AMQPFACTORY_H

#include "iot-protocols/amqp/classes/headerapi/amqpheader.h"
#include "iot-protocols/amqp/classes/tlv/described/amqpoutcome.h"
#include "iot-protocols/amqp/classes/tlv/described/amqpstate.h"
#include "iot-protocols/amqp/classes/section/amqpsection.h"
#include "iot-protocols/amqp/classes/headeramqp/amqpattach.h"
#include "iot-protocols/amqp/classes/headeramqp/amqpbegin.h"
#include "iot-protocols/amqp/classes/headeramqp/amqpclose.h"
#include "iot-protocols/amqp/classes/headeramqp/amqpdetach.h"
#include "iot-protocols/amqp/classes/headeramqp/amqpdisposition.h"
#include "iot-protocols/amqp/classes/headeramqp/amqpend.h"
#include "iot-protocols/amqp/classes/headeramqp/amqpflow.h"
#include "iot-protocols/amqp/classes/headeramqp/amqpopen.h"
#include "iot-protocols/amqp/classes/headeramqp/amqptransfer.h"

#include "iot-protocols/amqp/classes/headersasl/amqpsaslchallenge.h"
#include "iot-protocols/amqp/classes/headersasl/amqpsaslinit.h"
#include "iot-protocols/amqp/classes/headersasl/amqpsaslmechanisms.h"
#include "iot-protocols/amqp/classes/headersasl/amqpsasloutcome.h"
#include "iot-protocols/amqp/classes/headersasl/amqpsaslresponse.h"

#include "iot-protocols/amqp/classes/section/amqpapplicationproperties.h"
#include "iot-protocols/amqp/classes/section/amqpdata.h"
#include "iot-protocols/amqp/classes/section/amqpdeliveryannotation.h"
#include "iot-protocols/amqp/classes/section/amqpfooter.h"
#include "iot-protocols/amqp/classes/section/amqpmessageannotations.h"
#include "iot-protocols/amqp/classes/section/amqpmessageheader.h"
#include "iot-protocols/amqp/classes/section/amqpproperties.h"
#include "iot-protocols/amqp/classes/section/amqpsequence.h"
#include "iot-protocols/amqp/classes/section/amqpvalue.h"

#include "iot-protocols/amqp/classes/tlv/described/amqpaccepted.h"
#include "iot-protocols/amqp/classes/tlv/described/amqpmodified.h"
#include "iot-protocols/amqp/classes/tlv/described/amqpreceived.h"
#include "iot-protocols/amqp/classes/tlv/described/amqprejected.h"
#include "iot-protocols/amqp/classes/tlv/described/amqpreleased.h"

class AMQPFactory
{
public:

    AMQPFactory();

    static AMQPHeader *amqp(unsigned char *data);
    static AMQPHeader *sasl(unsigned char *data);
    static AMQPSection *section(unsigned char *data);
    static AMQPState *state(AMQPTLVList *list);
    static AMQPOutcome *outcome(AMQPTLVList *list);
};

#endif // AMQPFACTORY_H
