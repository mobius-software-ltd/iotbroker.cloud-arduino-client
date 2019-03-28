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

#ifndef AMQPTRANSFER_H
#define AMQPTRANSFER_H

#include <ArduinoJson.h>
#include <StandardCplusplus.h>
#include <map>
#include <list>
#include "iot-protocols/amqp/classes/headerapi/amqpheader.h"
#include "iot-protocols/amqp/classes/tlv/described/amqpstate.h"
#include "iot-protocols/amqp/classes/wrappers/amqpmessageformat.h"
#include "iot-protocols/amqp/classes/enums/amqpreceiversettlemode.h"
#include "iot-protocols/amqp/classes/enums/amqpsectioncode.h"
#include "iot-protocols/amqp/classes/section/amqpsection.h"

class AMQPTransfer : public AMQPHeader
{
private:
    JsonVariant *handle;
    JsonVariant *deliveryId;
    unsigned char * deliveryTag;
    AMQPMessageFormat *messageFormat;
    JsonVariant *settled;
    JsonVariant *more;
    AMQPReceiverSettleMode *rcvSettleMode;
    AMQPState *state;
    JsonVariant *resume;
    JsonVariant *aborted;
    JsonVariant *batchable;
    std::map<AMQPSectionCode *, AMQPSection *> sections;
public:
    AMQPTransfer();

    virtual int getLength();
    virtual int getType();

    virtual AMQPTLVList *arguments();
    virtual void fillArguments(AMQPTLVList *list);

    AMQPSection *getHeader();
    AMQPSection *getDeliveryAnnotations();
    AMQPSection *getMessageAnnotations();
    AMQPSection *getProperties();
    AMQPSection *getApplicationProperties();
    AMQPSection *getData();
    AMQPSection *getSequence();
    AMQPSection *getValue();
    AMQPSection *getFooter();

    void addSections(std::list<AMQPSection *> array);

    JsonVariant *getHandle() const;
    void setHandle(JsonVariant *value);

    JsonVariant *getDeliveryId() const;
    void setDeliveryId(JsonVariant *value);

    unsigned char * getDeliveryTag() const;
    void setDeliveryTag(const unsigned char &value);

    AMQPMessageFormat *getMessageFormat() const;
    void setMessageFormat(AMQPMessageFormat *value);

    JsonVariant *getSettled() const;
    void setSettled(JsonVariant *value);

    JsonVariant *getMore() const;
    void setMore(JsonVariant *value);

    AMQPReceiverSettleMode *getRcvSettleMode() const;
    void setRcvSettleMode(AMQPReceiverSettleMode *value);

    AMQPState *getState() const;
    void setState(AMQPState *value);

    JsonVariant *getResume() const;
    void setResume(JsonVariant *value);

    JsonVariant *getAborted() const;
    void setAborted(JsonVariant *value);

    JsonVariant *getBatchable() const;
    void setBatchable(JsonVariant *value);

    std::map<AMQPSectionCode *, AMQPSection *> getSections() const;
    void setSections(const std::map<AMQPSectionCode *, AMQPSection *> &value);
};

#endif // AMQPTRANSFER_H
