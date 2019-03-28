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

#include "snparser.h"
#include "iot-protocols/mqtt-sn/classes/snflags.h"
#include "iot-protocols/mqtt-sn/classes/sncontrols.h"
#include "iot-protocols/mqtt-sn/classes/snvaluesvalidator.h"
#include "iot-protocols/mqtt-sn/classes/topics/snfulltopic.h"
#include "iot-protocols/mqtt-sn/classes/topics/snidentifiertopic.h"
#include "iot-protocols/mqtt-sn/classes/topics/snshorttopic.h"

static unsigned char const threeOctetLengthSuffix = 0x01;


unsigned char * SNParser::encode(Message *message)
{
    int length = message->getLength();

    unsigned char * data = NULL;
    data = malloc(sizeof(char) * length)

    unsigned short string_length = 0;
    int i = 0;

    if (length <= 255) {
        data[i++] = (char) length;
    } else {
        data[i++] = threeOctetLengthSuffix;
        i += addshort(&data[i], length);
    }

    SNMessageType type = (SNMessageType)message->getType();
    data[i++] = type;

    switch(type) {

        case SN_ADVERTISE:
        {
            SNAdvertise *advertise = (SNAdvertise *)message;
            data[i++] = advertise->getGwId();
            addshort(&data[i], advertise->getDuration());
        } break;

        case SN_SEARCHGW:
        {
            SNSearchGW *searchGw = (SNSearchGW *)message;
            data[i] = searchGw->getRadius();
        } break;

        case SN_GWINFO:
        {
            SNGWInfo *gwInfo = (SNGWInfo *)message;
            data[i++] = gwInfo->getGwID();
            if (gwInfo->getGwAddress().length() != 0) {
                string_length = strlen(gwInfo->getGwAddress());
                if (string_length != 0) {
                  memcpy(&data[i], gwInfo->getGwAddress(), string_length);
                }
            }
        } break;

        case SN_CONNECT:
        {
            SNConnect *connect = (SNConnect *)message;
            char connectFlagsByte = SNFlags::encode(false, NULL, false, connect->getWillPresent(), connect->getCleanSession(), SN_UNKNOWN_TOPIC_TYPE);
            data[i++] = connectFlagsByte;
            data[i++] = connect->getProtocolID();

            i += add_short(&data[i], connect->getDuration());
        	  string_length = strlen(connect->getClientID());
          	if (string_length != 0) {
          		 memcpy(&data[i], connect->getClientID(), string_length);
          		 i += string_length;
             }
        } break;

        case SN_CONNACK:
        case SN_WILLTOPICRESP:
        case SN_WILLMSGRESP:
        {
            SNResponseMessage *responseMessage = (SNResponseMessage *)message;
            data[i] = responseMessage->getReturnCode();
        } break;

        case SN_WILLTOPIC:
        {
            SNWillTopic *willTopic = (SNWillTopic *)message;
            if (willTopic->getTopic() != NULL) {
                char willTopicFlagsByte = SNFlags::encode(false, willTopic->getTopic()->getQoS(), willTopic->getIsRetain(), false, false, willTopic->getTopic()->getType());
                data[i++] = willTopicFlagsByte;

                string_length = strlen(willTopic->getTopic()->encode());
    	    		  if (string_length != 0) {
      	    			 memcpy(&data[i], willTopic->getTopic()->encode(), string_length);
      	    			 i += string_length;
                 }
            }
        } break;

        case SN_WILLMSG:
        {
            SNWillMsg *willMsg = (SNWillMsg *)message;

            string_length = strlen(willMsg->getContent());
            if (string_length != 0) {
               memcpy(&data[i], willMsg->getContent(), string_length);
               i += string_length;
             }
        } break;

        case SN_REGISTER:
        {
            SNRegister *registerSN = (SNRegister *)message;
            i += add_short(&data[i], registerSN->getTopicID());
            i += add_short(&data[i], registerSN->getPacketID());
            string_length = strlen(registerSN->getTopicName());
            if (string_length != 0) {
               memcpy(&data[i], registerSN->getTopicName(), string_length);
               i += string_length;
             }
        } break;

        case SN_REGACK:
        {
            SNRegack *regack = (SNRegack *)message;
            i += add_short(&data[i], regack->getTopicID());
            i += add_short(&data[i], regack->getPacketID());
            data[i] = regack->getCode();
        } break;

        case SN_PUBLISH:
        {
            SNPublish *publish = (SNPublish *)message;
            char publishFlagsByte = SNFlags::encode(publish->getIsDup(), publish->getTopic()->getQoS(), publish->getIsRetain(), false, false, publish->getTopic()->getType());
            data[i++] = publishFlagsByte;
  	    		string_length = strlen(publish->getTopic()->encode());
  	    		if (string_length != 0) {
  	    			 memcpy(&data[i], publish->getTopic()->encode(), string_length);
  	    			 i += string_length;
  	    		}
            i += add_short(&data[i], publish->getPacketID());
            string_length = strlen(publish->getContent());
  	    		if (string_length != 0) {
  	    			 memcpy(&data[i], publish->getContent(), string_length);
  	    			 i += string_length;
  	    		}
        } break;

        case SN_PUBACK:
        {
            SNPuback *puback = (SNPuback *)message;
            i += add_short(&data[i], puback->getTopicID());
            i += add_short(&data[i], puback->getPacketID());
            data[i] = puback->getCode();
        } break;

        case SN_PUBREC:
        case SN_PUBREL:
        case SN_PUBCOMP:
        case SN_UNSUBACK:
        {
            CountableMessage *contableMessage = (CountableMessage *)message;
            add_short(&data[i], contableMessage->getPacketID());
        } break;

        case SN_SUBSCRIBE:
        {
            SNSubscribe *subscribe = (SNSubscribe *)message;
            char subscribeFlags = SNFlags::encode(subscribe->getIsDup(), subscribe->getTopic()->getQoS(), false, false, false, subscribe->getTopic()->getType());
            data[i++] = subscribeFlags;
            i += add_short(&data[i], subscribe->getPacketID());
            string_length = strlen(subscribe->getTopic()->encode());
  	    		if (string_length != 0) {
  	    			 memcpy(&data[i], subscribe->getTopic()->encode(), string_length);
  	    			 i += string_length;
  	    		}
        } break;

        case SN_SUBACK:
        {
            SNSuback *suback = (SNSuback *)message;
            char subackByte = SNFlags::encode(false, suback->getQos(), false, false, false, SN_UNKNOWN_TOPIC_TYPE);
            data[i++] = subackByte;
            i += add_short(&data[i], suback->getTopicID());
            i += add_short(&data[i], suback->getPacketID());
            data[i] = suback->getCode();
        } break;

        case SN_UNSUBSCRIBE:
        {
            SNUnsubscribe *unsubscribe = (SNUnsubscribe *)message;
            char unsubscribeFlags = SNFlags::encode(false, NULL, false, false, false, unsubscribe->getTopic()->getType());
            data[i++] = unsubscribeFlags;
            i += add_short(&data[i], unsubscribe->getPacketID());
            string_length = strlen(unsubscribe->getTopic()->encode());
  	    		if (string_length != 0) {
  	    			 memcpy(&data[i], unsubscribe->getTopic()->encode(), string_length);
  	    			 i += string_length;
  	    		}
        } break;

        case SN_PINGREQ:
        {
            if (length > 2) {
                SNPingreq *pingreq = (SNPingreq *)message;

                string_length = strlen(pingreq->getClientID());
      	    		if (string_length != 0) {
      	    			 memcpy(&data[i], pingreq->getClientID(), string_length);
      	    		}
                i += string_length;
          }
        } break;

        case SN_WILLTOPICREQ:
        case SN_WILLMSGREQ:
        case SN_PINGRESP:
        {
        } break;

        case SN_DISCONNECT:
        {
            if (length > 2) {
                SNDisconnect *disconnect = (SNDisconnect *)message;
                i += add_short(&data[i], disconnect->getDuration());
            }
        } break;

        case SN_WILLTOPICUPD:
        {
            SNWillTopicUpd *willTopicUpd = (SNWillTopicUpd *)message;
            if (willTopicUpd->getTopic() != NULL) {
                char willTopicUpdByte = SNFlags::encode(false, willTopicUpd->getTopic()->getQoS(), willTopicUpd->getIsRetain(), false, false, SN_UNKNOWN_TOPIC_TYPE);
                data[++] = willTopicUpdByte;
                string_length = strlen(willTopicUpd->getTopic()->encode());
      	    		if (string_length != 0) {
      	    			 memcpy(&data[i], willTopicUpd->getTopic()->encode(), string_length);
      	    			 i += string_length;
      	    		}
            }
        } break;

        case SN_WILLMSGUPD:
        {
            SNWillMsgUpd *willMsgUpd = (SNWillMsgUpd *)message;
            string_length = strlen(willMsgUpd->getContent());
            if (string_length != 0) {
               memcpy(&data[i], willMsgUpd->getContent(), string_length);
            }

            //data->writeRawData(willMsgUpd->getContent());
        } break;

        case SN_ENCAPSULATED:
        {
            SNEncapsulated *encapsulated = (SNEncapsulated *)message;
            data[i++] = SNControls::encode(encapsulated->getRadius());

            string_length = strlen(encapsulated->getWirelessNodeID());
            if (string_length != 0) {
               memcpy(&data[i], encapsulated->getWirelessNodeID(), string_length);
               i += string_length;
            }

            unsigned char * buffer = NULL;
            buffer = malloc(sizeof(char) * encapsulated->getMessage()->getLength());
            buffer = SNParser::encode(encapsulated->getMessage());
            string_length = strlen(buffer);
            if (string_length != 0) {
               memcpy(&data[i], buffer, string_length);
               i += string_length;
            }
        } break;

    }

    if (type != SN_ENCAPSULATED && message->getLength() != data->getSize()) {
        printf("invalid message encoding: expected length = " + message->getLength() + " actual = " + data->getSize());
    }

    return data;
}

Message *SNParser::decode(unsigned char * buffer)
{
    Message *message = NULL;

    int i = 0;
    int messageLength = 0;
  	short first_length_byte = (short)(0x00FF & (short)buffer[i++]);
  	if (first_length_byte == THREE_OCTET_LENGTH_SUFFIX) {
  		add_short(&buffer[i], messageLength);
  		i+=2;
  	}
  	else {
  		messageLength = first_length_byte;
    }

    int bytes_left = length - i;

    short typeByte = buffer[i++];
    SNMessageType type = (SNMessageType)typeByte;

    bytes_left--;
    switch(type) {

        case SN_ADVERTISE:
        {
            int advertiseGwID = buffer[i++];
            int advertiseDuration = get_short(buffer, i);
            message = new SNAdvertise(advertiseGwID, advertiseDuration);
        } break;

        case SN_SEARCHGW:
        {
            SNRadius radius = (SNRadius)buffer[i++];
            message = new SNSearchGW(radius);
        } break;

        case SN_GWINFO:
        {
            int gwInfoGWID = buffer[i++];
            bytesLeft--;
            string gwInfoGwAddress;
            if (bytesLeft > 0) {
                gwInfoGwAddress = get_string(&buffer[i], bytesLeft);
            }
            message = new SNGWInfo(gwInfoGWID, gwInfoGwAddress);
        } break;

        case SN_CONNECT:
        {
            SNFlags *flags = SNFlags::decode(buffer[i++], type);
            bytesLeft--;

            int protocolID = buffer[i++];
            bytesLeft--;

            if (protocolID != MQTT_SN_PROTOCOL_ID) {
                printf("Invalid protocolID = " + protocolID);
            }

            int connectDuration = get_short(buffer, i);
            i +=2;

            bytesLeft -= 2;

            if (!SNValuesValidator::canReadData(*buffer, bytesLeft)) {
                printf("Type = "+type+". clientID can't be empty");
            }

            String clientId = get_string(&buffer[i], bytes_left);
            message = new SNConnect(flags->getCleanSession(), connectDuration, clientId, flags->getWill());
        } break;

        case SN_CONNACK:
        {
            SNReturnCode code = (SNReturnCode)buffer[i];
            message = new SNConnack(code);
        } break;

        case SN_WILLTOPICREQ:
        {
            message = new SNWillTopicReq();
        } break;

        case SN_WILLTOPIC:
        {
            bool willTopicRetain = false;
            SNFullTopic *willTopic = NULL;
            if (bytesLeft > 0) {
                SNFlags *willTopicFlags = SNFlags::decode(buffer[i++], type);
                bytesLeft--;
                willTopicRetain = willTopicFlags->getIsRetain();
                if (!SNValuesValidator::canReadData(*buffer, bytesLeft)) {
                    printf("invalid topic encoding. Type = "+type);
                }
                String willTopicString = get_string(&buffer[i], bytesLeft);
                willTopic = new SNFullTopic(willTopicString, willTopicFlags->getQos());
            }
            message = new SNWillTopic(willTopic, willTopicRetain);
        } break;

        case SN_WILLMSGREQ:
        {
            message = new SNWillMsgReq();
        } break;

        case SN_WILLMSG:
        {
            if (!SNValuesValidator::canReadData(*buffer, bytesLeft)) {
                printf("content must not be empty. Type = "+type);
            }
            String willMSGContentString = get_string(&buffer[i], bytesLeft);
            message = new SNWillMsg(willMSGContentString);
        } break;

        case SN_REGISTER:
        {
            int registerTopicId = get_short(buffer, i);
            i += 2;
            if (!SNValuesValidator::validateRegistrationTopicID(registerTopicId)) {
                printf(registerTopicId+" is invalid topicID value. Type = "+type);
            }
            bytesLeft -= 2;
            int registerPacketId = get_short(buffer, i);
            i += 2;
            if (!SNValuesValidator::validatePacketID(registerPacketId)) {
                printf(registerPacketId+" is invalid packetID. Type = "+type);
            }
            bytesLeft -= 2;
            if (!SNValuesValidator::canReadData(*buffer, bytesLeft)) {
                printf("must contain a valid topic. Type = "+type);
            }
            String registerTopicName = get_string(&buffer[i], bytesLeft);
            message = new SNRegister(registerTopicId, registerPacketId, registerTopicName);
        } break;

        case SN_REGACK:
        {

            int regackTopicId = get_short(buffer, i);
            i += 2;
            if (!SNValuesValidator::validateRegistrationTopicID(regackTopicId)) {
                printf(regackTopicId+" is invalid topicID value. Type = "+type);
            }
            int regackPacketId = get_short(buffer, i);
            i += 2;
            if (!SNValuesValidator::validatePacketID(regackPacketId)) {
                printf(regackPacketId+" is invalid packetID. Type = "+type);
            }
            SNReturnCode code = (SNReturnCode)buffer[i];
            message = new SNRegack(regackTopicId, regackPacketId, code);
        } break;

        case SN_PUBLISH:
        {
            SNFlags *publishFlags = SNFlags::decode(buffer[i++], type);
            bytesLeft--;
            int publishTopicID = get_short(buffer, i);
            i += 2;
            bytesLeft -= 2;
            int publishPacketID = get_short(buffer, i);
            i += 2;
            bytesLeft -= 2;

            if (publishFlags->getQos()->getValue() != AT_MOST_ONCE && publishPacketID == 0) {
                printf("invalid PUBLISH QoS-0. Type = "+type);
            }

            Topic *publishTopic = NULL;

            if (publishFlags->getTopicType() == SN_SHORT_TOPIC_TYPE) {
                publishTopic = new SNShortTopic(publishTopicID, publishFlags->getQos());
            } else {
                if (!SNValuesValidator::validateTopicID(publishTopicID)) {
                    printf(publishTopicID+" is invalid topicID value. Type = "+type);
                }
                publishTopic = new SNIdentifierTopic(publishTopicID, publishFlags->getQos());
            }

            char *content = NULL;
            if (bytesLeft > 0) {
                String content = get_string(&buffer[i], bytesLeft);
            }
            message = new SNPublish(publishPacketID, publishTopic, content, publishFlags->getIsDup(), publishFlags->getIsRetain());
        } break;

        case SN_PUBACK:
        {
            int pubackTopicID = get_short(buffer, i);
            i += 2;
            if (!SNValuesValidator::validateTopicID(pubackTopicID)) {
                printf(pubackTopicID+" is invalid topicID value. Type = "+type);
            }
            int pubackPacketID = get_short(buffer, i);
            i += 2;
            if (!SNValuesValidator::validatePacketID(pubackPacketID)) {
                printf(pubackPacketID+" is invalid packetID value. Type = "+type);
            }
            SNReturnCode returnCode = (SNReturnCode)buffer[i]];
            message = new SNPuback(pubackTopicID, pubackPacketID, returnCode);
        } break;

        case SN_PUBCOMP:
        {
            int pubcompPacketID = get_short(buffer, i);
            i += 2;
            if (!SNValuesValidator::validatePacketID(pubcompPacketID)) {
                printf(pubcompPacketID+" is invalid packetID value. Type = "+type);
            }
            message = new SNPubcomp(pubcompPacketID);;
        } break;

        case SN_PUBREC:
        {
            int pubrecPacketID = get_short(buffer, i);
            i += 2;
            if (!SNValuesValidator::validatePacketID(pubrecPacketID)) {
                printf(pubrecPacketID+" is invalid packetID value. Type = "+type);
            }
            message = new SNPubrec(pubrecPacketID);
        } break;

        case SN_PUBREL:
        {
            int pubrelPacketID = get_short(buffer, i);
            i += 2;
            if (!SNValuesValidator::validatePacketID(pubrelPacketID)) {
                printf(pubrelPacketID+" is invalid packetID value. Type = "+type);
            }
            message = new SNPubrel(pubrelPacketID);
        } break;

        case SN_SUBSCRIBE:
        {
            SNFlags *subscribeFlags = SNFlags::decode(buffer[i++], type);
            bytesLeft--;
            int subscribePacketID = get_short(buffer, i);
            i += 2;
            if (subscribePacketID == 0) {
                printf(subscribePacketID+" is invalid packetID value. Type = "+type);
            }
            bytesLeft -= 2;
            if (!SNValuesValidator::canReadData(*buffer, bytesLeft) || bytesLeft < 2) {
                printf("invalid topic encoding. Type = "+type);
            }

            Topic *topic = NULL;

            switch(subscribeFlags->getTopicType()) {
                case SN_NAMED_TOPIC_TYPE:
                {
                    String subscribeTopicName = get_string(&buffer[i], bytesLeft);
                    topic = new SNFullTopic(subscribeTopicName, subscribeFlags->getQos());
                } break;
                case SN_ID_TOPIC_TYPE:
                {
                    int subscribeTopicID = get_short(buffer, i);
                    i += 2;
                    if (!SNValuesValidator::validateTopicID(subscribeTopicID)) {
                        printf(subscribePacketID+" is invalid topicID value. Type = "+type);
                    }
                    topic = new SNIdentifierTopic(subscribeTopicID, subscribeFlags->getQos());
                } break;
                case SN_SHORT_TOPIC_TYPE:
                {
                    String subscribeTopicShortName = get_string(&buffer[i], bytesLeft);
                    topic = new SNShortTopic(subscribeTopicShortName, subscribeFlags->getQos());
                } break;
                default: break;
            }
            message = new SNSubscribe(subscribePacketID, topic, subscribeFlags->getQos());
        } break;

        case SN_SUBACK:
        {
            SNFlags *subackFlags = SNFlags::decode(buffer[i++], type);
            int subackTopicID = get_short(buffer, i);
            i += 2;
            if (!SNValuesValidator::validateTopicID(subackTopicID)) {
                printf(subackTopicID+" is invalid topicID value. Type = "+type);
            }

            int subackPacketID = get_short(buffer, i);
            i += 2;
            if (!SNValuesValidator::validatePacketID(subackPacketID)) {
                printf(subackPacketID+" is invalid packetID value. Type = "+type);
            }

            SNReturnCode code = (SNReturnCode)buffer[i];
            message = new SNSuback(subackTopicID, subackPacketID, code, subackFlags->getQos());
        } break;

        case SN_UNSUBSCRIBE:
        {
            SNFlags *unsubscribeFlags = SNFlags::decode(buffer[i++], type);
            bytesLeft--;
            int unsubscribePacketId = get_short(buffer, i);
            i += 2;
            if (!SNValuesValidator::validatePacketID(unsubscribePacketId)) {
                printf(unsubscribePacketId+" is invalid packetID value. Type = "+type);
            }
            bytesLeft--;

            Topic *topic = NULL;

            switch(unsubscribeFlags->getTopicType()) {
                case SN_NAMED_TOPIC_TYPE:
                {
                    String unsubscribeTopicName = get_string(&buffer[i], bytesLeft);
                    topic = new SNFullTopic(unsubscribeTopicName, unsubscribeFlags->getQos());
                } break;
                case SN_ID_TOPIC_TYPE:
                {
                    int unsubscribeTopicID = get_short(buffer, i);
                    i += 2;
                    if (!SNValuesValidator::validateTopicID(unsubscribeTopicID)) {
                        printf(unsubscribeTopicID+" is invalid topicID value. Type = "+type);
                    }
                    topic = new SNIdentifierTopic(unsubscribeTopicID, unsubscribeFlags->getQos());
                } break;
                case SN_SHORT_TOPIC_TYPE:
                {
                    String unsubscribeTopicShortName = get_string(&buffer[i], bytesLeft);
                    topic = new SNShortTopic(unsubscribeTopicShortName, unsubscribeFlags->getQos());
                } break;
                default: break;
            }
            message = new SNUnsubscribe(unsubscribePacketId, topic);
        } break;

        case SN_UNSUBACK:
        {
            int unsubackPacketID = get_short(buffer, i);
            i += 2;
            if (!SNValuesValidator::validatePacketID(unsubackPacketID)) {
                printf(unsubackPacketID+" is invalid packetID value. Type = "+type);
            }
            message = new SNUnsuback(unsubackPacketID);
        } break;

        case SN_PINGREQ:
        {
            String pingreqClientID;
            if (bytesLeft > 0) {
                pingreqClientID = get_string(&buffer[i], bytesLeft);
            }
            message = new SNPingreq(pingreqClientID);
        } break;

        case SN_PINGRESP:
        {
            message = new SNPingresp();
        } break;

        case SN_DISCONNECT:
        {
            int duration = 0;
            if (bytesLeft > 1) {
                duration = get_short(buffer, i);
                i += 2;
            }
            message = new SNDisconnect(duration);
        } break;

        case SN_WILLTOPICUPD:
        {
            SNFullTopic *topic = NULL;
            bool willTopicUpdateRetain = false;
            if (bytesLeft > 0) {
                SNFlags *willFlags = SNFlags::decode(buffer[i++], type);
                willTopicUpdateRetain = willFlags->getIsRetain();
                bytesLeft--;
                String willTopicValue = get_string(&buffer[i], bytesLeft);
                topic = new SNFullTopic(willTopicValue, willFlags->getQos());
            }
            message = new SNWillTopicUpd(topic, willTopicUpdateRetain);
        } break;

        case SN_WILLTOPICRESP:
        {
            SNReturnCode code = (SNReturnCode)buffer[i];
            message = new SNWillTopicResp(code);
        } break;

        case SN_WILLMSGUPD:
        {
            if (!SNValuesValidator::canReadData(*buffer, bytesLeft)) {
                printf("must contain content data. Type = "+type);
            }
            String content = get_string(&buffer[i], bytesLeft);
            message = new SNWillMsgUpd(content);
        } break;

        case SN_WILLMSGRESP:
        {
            SNReturnCode code = (SNReturnCode)buffer[i];
            message = new SNWillMsgResp(code);
        } break;

        case SN_ENCAPSULATED:
        {

            SNControls *control = SNControls::decode(buffer[i++]);
            bytesLeft--;

            String wirelessNodeId = get_string(&buffer[i], bytesLeft);

            Message *encapsulatedMessage = SNParser::decode(buffer);
            message = new SNEncapsulated(control->getRadius(), wirelessNodeId, encapsulatedMessage);
        } break;

    }

    if (buffer->getSize() < 0) {
        printf("not all bytes have been read from buffer");
    }

    return message;
}
