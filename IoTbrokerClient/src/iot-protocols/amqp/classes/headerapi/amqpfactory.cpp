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

#include "amqpfactory.h"
#include "iot-protocols/amqp/classes/tlv/api/amqptlvfactory.h"
#include "iot-protocols/amqp/classes/enums/amqpstatecode.h"

AMQPFactory::AMQPFactory()
{

}

AMQPHeader *AMQPFactory::amqp(unsigned char *data)
{
    TLVAMQP *list = AMQPTLVFactory::tlvByData(data);

    if (list->getTypeValue() != AMQP_LIST0_TYPE && list->getTypeValue() != AMQP_LIST8_TYPE && list->getTypeValue() != AMQP_LIST32_TYPE) {
        printf("AMQPFactory::amqp::wrong_type");
        return NULL;
    }

    AMQPHeader *header = NULL;

    int byteCode = list->getConstructor()->getDescriptorCode();
    AMQPHeaderCode *code = new AMQPHeaderCode(byteCode);

    switch(code->getValue()) {
        case AMQP_OPEN_HEADER_CODE:         header = new AMQPOpen();        break;
        case AMQP_BEGIN_HEADER_CODE:        header = new AMQPBegin();       break;
        case AMQP_ATTACH_HEADER_CODE:       header = new AMQPAttach();      break;
        case AMQP_FLOW_HEADER_CODE:         header = new AMQPFlow();        break;
        case AMQP_TRANSFER_HEADER_CODE:     header = new AMQPTransfer();    break;
        case AMQP_DISPOSITION_HEADER_CODE:  header = new AMQPDisposition(); break;
        case AMQP_DETACH_HEADER_CODE:       header = new AMQPDetach();      break;
        case AMQP_END_HEADER_CODE:          header = new AMQPEnd();         break;
        case AMQP_CLOSE_HEADER_CODE:        header = new AMQPClose();       break;
        default:                            printf("AMQPFactory::amqp::wrong_message"); break;
    }

    header->fillArguments((AMQPTLVList *)list);
    return header;
}

AMQPHeader *AMQPFactory::sasl(ByteArray *data)
{
    TLVAMQP *list = AMQPTLVFactory::tlvByData(data);

    if (list->getTypeValue() != AMQP_LIST0_TYPE && list->getTypeValue() != AMQP_LIST8_TYPE && list->getTypeValue() != AMQP_LIST32_TYPE) {
        printf("AMQPFactory::sasl::wrong_type");
        return NULL;
    }

    AMQPHeader *header = NULL;

    int byteCode = list->getConstructor()->getDescriptorCode();
    AMQPHeaderCode *code = new AMQPHeaderCode(byteCode);

    switch(code->getValue()) {
        case AMQP_MECHANISMS_HEADER_CODE:   header = new AMQPSASLMechanisms();  break;
        case AMQP_INIT_HEADER_CODE:         header = new AMQPSASLInit();        break;
        case AMQP_CHALLENGE_HEADER_CODE:    header = new AMQPSASLChallenge();   break;
        case AMQP_RESPONSE_HEADER_CODE:     header = new AMQPSASLResponse();    break;
        case AMQP_OUTCOME_HEADER_CODE:      header = new AMQPSASLOutcome();     break;
    }

    header->fillArguments((AMQPTLVList *)list);
    return header;
}

AMQPSection *AMQPFactory::section(ByteArray *data)
{
    TLVAMQP *value = AMQPTLVFactory::tlvByData(data);
    AMQPSection *section = NULL;

    int byteCode = value->getConstructor()->getDescriptorCode();
    AMQPSectionCode *code = new AMQPSectionCode(byteCode);

    switch(code->getValue()) {
        case AMQP_HEADER_SECTION_CODE:                  section = new AMQPMessageHeader();          break;
        case AMQP_DELIVERY_ANNOTATIONS_SECTION_CODE:    section = new AMQPDeliveryAnnotation();     break;
        case AMQP_MESSAGE_ANNOTATIONS_SECTION_CODE:     section = new AMQPMessageAnnotations();     break;
        case AMQP_PROPERTIES_SECTION_CODE:              section = new AMQPProperties();             break;
        case AMQP_APPLICATION_PROPERTIES_SECTION_CODE:  section = new AMQPApplicationProperties();  break;
        case AMQP_DATA_SECTION_CODE:                    section = new AMQPData();                   break;
        case AMQP_SEQUENCE_SECTION_CODE:                section = new AMQPSequence();               break;
        case AMQP_VALUE_SECTION_CODE:                   section = new AMQPValue();                  break;
        case AMQP_FOOTER_SECTION_CODE:                  section = new AMQPFooter();                 break;
    }
    section->fill(value);
    return section;
}

AMQPState *AMQPFactory::state(AMQPTLVList *list)
{
    AMQPState *state = NULL;

    int byteCode = list->getConstructor()->getDescriptorCode();
    AMQPStateCode *code = new AMQPStateCode(byteCode);

    switch(code->getValue()) {
        case AMQP_ACCEPTED_STATE_CODE:  state = new AMQPAccepted(); break;
        case AMQP_REJECTED_STATE_CODE:  state = new AMQPRejected(); break;
        case AMQP_RELEASED_STATE_CODE:  state = new AMQPReleased(); break;
        case AMQP_MODIFIED_STATE_CODE:  state = new AMQPModified(); break;
        case AMQP_RECEIVED_STATE_CODE:  state = new AMQPReceived(); break;
    }

    return state;
}

AMQPOutcome *AMQPFactory::outcome(AMQPTLVList *list)
{
    AMQPOutcome *outcome = NULL;

    int byteCode = list->getConstructor()->getDescriptorCode();
    AMQPStateCode *code = new AMQPStateCode(byteCode);

    switch(code->getValue()) {
        case AMQP_ACCEPTED_STATE_CODE:  outcome = new AMQPAccepted();   break;
        case AMQP_REJECTED_STATE_CODE:  outcome = new AMQPRejected();   break;
        case AMQP_RELEASED_STATE_CODE:  outcome = new AMQPReleased();   break;
        case AMQP_MODIFIED_STATE_CODE:  outcome = new AMQPModified();   break;
    }

    return outcome;
}
