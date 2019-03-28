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

#include "parser.h"
#include "iot-protocols/mqtt/classes/mqttenums.h"

unsigned char byteArray[] Parser::next(unsigned char &byteArray[])
{
    unsigned char * buffer = byteArray;

    char fixedHeader = buffer->readChar();
    char messageType = ((fixedHeader >> 4) & 0xf);

    if (messageType == 0) {
        return unsigned char byte[];
    }

    switch (messageType) {
        case MQ_PINGREQ:
        case MQ_PINGRESP:
        case MQ_DISCONNECT: {
            unsigned char * dreturnArray;
            strcat(dreturnArray, buffer + 2);
            strcat(byteArray, buffer +2);
            return dreturnArray;
        }
        break;
        default:
            LengthDetails *length = LengthDetails::decode(buffer);

            if (length->getLength() == 0) {
                return unsigned char byte[];
            }
            int result = length->getLength() + length->getSize() + 1;
            if (result > sizeof byteArray {
                printf(" -! invalid length decoding for %i result length: %i, in buffer: %i", messageType, result, sizeof byteArray);
            }

            unsigned char * returnArray;
            strcat(returnArray, buffer + result + sizeof byteArray);
            strcat(byteArray, buffer + result);
            return returnArray;

            return returnArray;
        break;
    }
    return NULL;
}

unsigned char * Parser::encode(Message *message)
{
    int length = message->getLength();

    unsigned char * buffer = NULL;
    buffer = malloc(sizeof(char) * (length+2))
    unsigned char messageType = message->getType();
    int i = 0;
    unsigned short string_length = 0;
    switch (messageType) {

        case MQ_CONNECT: {

            Connect *connect = (Connect *)message;

            if (connect->isWillFlag() && !connect->getWill()->isValid()) {
                printf("Encode. Connect. Invalid will encoding");
            }

            buffer[i++] = (messageType << 4);
            i = add_packet_length(length, getBufferByLength(length));
            buffer[i++] = 0;

            string_length = strlen(connect->getProtocol()->getName());
		        buf[i++] = string_length;
		        memcpy(&buf[i], PROTOCOL_NAME, string_length);
            i += string_length;

            buffer[i++] = connect->getProtocolLevel();

            char contentFlags = 0;

            if (connect->isCleanSession() == true) {
                contentFlags += 2;
            }
            if (connect->isWillFlag() == true) {
                contentFlags += 4;
                int qosValue = connect->getWill()->getTopic()->getQoS()->getValue();
                contentFlags += qosValue << 3;
                if (connect->getWill()->isRetain() == true) {
                    contentFlags += 0x20;
                }
            }
            if (connect->isPasswordFlag() == true) {
                contentFlags += 0x40;
            }
            if (connect->isUsernameFlag() == true) {
                contentFlags += 0x80;
            }

            buffer[i++] = contentFlags;
            i += add_short(&buffer[i], connect->getKeepAlive());

            unsigned short client_id_length = strlen(connect->getClientID());
		        i += add_short(&buffer[i], client_id_length);
		        memcpy(&buffer[i], connect->getClientID(), client_id_length);
            i += client_id_length;

            if (connect->isWillFlag() == true) {
                string_length = strlen(connect->getWill()->getTopic()->getName());
                if (string_length != 0) {
                  i += add_short(&buffer[i], string_length);
                  memcpy(&buffer[i], connect->getWill()->getTopic()->getName(), string_length);
                  i += string_length;
                }

                string_length = strlen(connect->getWill()->getContent());
                if (string_length != 0) {
                  i += add_short(&buffer[i], string_length);
                  memcpy(&buffer[i], connect->getWill()->getContent(), string_length);
                  i += string_length;
                }
            }

            string_length = strlen(connect->getUsername());
            if (string_length != 0) {
              i += add_short(&buffer[i], string_length);
              memcpy(&buffer[i], connect->getUsername(), string_length);
              i += string_length;
            }

            string_length = strlen(connect->getPassword());
            if (string_length != 0) {
              i += add_short(&buffer[i], string_length);
              memcpy(&buffer[i], connect->getPassword(), string_length);
              i += string_length;
            }
        }
        break;

        case MQ_CONNACK: {

            Connack *connack = (Connack *)message;
            buffer[i++] = (messageType << 4);
            buffer[i++] = (char) message->getLength());
            buffer[i++] = connack->isSessionPresent();
            buffer[i++] = (char) connack->getReturnCode();
        }
        break;

        case MQ_PUBLISH: {

            Publish *publish = (Publish *)message;
            char firstByte = (messageType << 4);
            firstByte |= (publish->isDup() == true)? 8 : 0;
            firstByte |= (publish->getTopic()->getQoS()->getValue() << 1);
            firstByte |= (publish->isRetain() == true)? 1 : 0;

            buffer[i] = firstByte;
            i = add_packet_length(length, getBufferByLength(length));


            string_length = strlen(publish->getTopic()->getName());
            if (string_length != 0) {
              i += add_short(&buffer[i], string_length);
              memcpy(&buffer[i], publish->getTopic()->getName(), string_length);
              i += string_length;
            }

            switch (publish->getTopic()->getQoS()->getValue()) {
                case AT_MOST_ONCE:
                    if (publish->getPacketID() != 0) {
                        printf("Encode. Publish. Publish qos-0 must not contain packetID");
                    }
                break;
                case AT_LEAST_ONCE:
                case EXACTLY_ONCE:
                    if (publish->getPacketID() == 0) {
                        printf("Encode. Publish. Publish qos-1,2 must contain packetID");
                    }
                    i += add_short(&buffer[i], publish->getPacketID());
                break;
            }
            memcpy(&buffer[i], publish->getContent(), strlen(publish->getContent()));
        }
        break;

        case MQ_PUBACK: {

            Puback *puback = (Puback *)message;
            buffer[i++] = messageType << 4;
            buffer[i++] = length;
            if (puback->getPacketID() == 0) {
                printf("Encode. Puback. Puback must contain packetID");
            }
            add_short(&buffer[i], puback->getPacketID());
        }
        break;

        case MQ_PUBREC: {

            Pubrec *pubrec = (Pubrec *)message;
            buffer[i++] = messageType << 4;
            buffer[i++] = length;
            if (pubrec->getPacketID() == 0) {
                printf("Encode. Pubrec. Pubrec must contain packetID");
            }
            add_short(&buffer[i], pubrec->getPacketID());
        }
        break;

        case MQ_PUBREL: {

            Pubrel *pubrel = (Pubrel *)message;
            buffer[i++] = messageType << 4 | 0x2;
            buffer[i++] = length;
            if (pubrel->getPacketID() == 0) {
                printf("Encode. Pubrel. Pubrel must contain packetID");
            }
            add_short(&buffer[i], pubrel->getPacketID());
        }
        break;

        case MQ_PUBCOMP: {

            Pubcomp *pubcomp = (Pubcomp *)message;
            buffer[i++] = messageType << 4;
            buffer[i++] = length;
            if (pubcomp->getPacketID() == 0) {
                printf("Encode. Pubcomp. Pubcomp must contain packetID");
            }
            add_short(&buffer[i], pubcomp->getPacketID());
        }
        break;

        case MQ_SUBSCRIBE: {

            Subscribe *subscribe = (Subscribe *)message;
            buffer[i++] = messageType << 4 | 0x2;
            i = add_packet_length(length, getBufferByLength(length));

            if (subscribe->getPacketID() == 0) {
                printf("Encode. Subscribe. Subscribe must contain packetID");
            }
            i += add_short(&buffer[i], subscribe->getPacketID());

            for (int j = 0; j < subscribe->getTopics()->size(); j++) {
              MQTopic item = subscribe->getTopics()->at(i);
              string_length = strlen(item.getName());
              if (string_length != 0) {
                i += add_short(&buffer[i], string_length);
                memcpy(&buf[i], item.getName(), string_length);
                i += string_length;
              }
              buf[i] = (char) item.getQoS()->getValue();
            }
        }
        break;

        case MQ_SUBACK: {

            Suback *suback = (Suback *)message;
            buffer[i++] = messageType << 4;

            if (suback->getPacketID() == 0) {
                printf("Encode. Suback. Suback must contain packetID");
            }
            i += add_short(&buffer[i], pubrel->getPacketID());

            for (int j = 0; j < suback->getReturnCodes()->size(); j++) {
                SubackCode item = suback->getReturnCodes()->at(j);
                buffer[i++] = writeChar(item);
            }
        }
        break;

        case MQ_UNSUBSCRIBE: {

            Unsubscribe *unsubscribe = (Unsubscribe *)message;
            buffer[i++] = messageType << 4 | 0x2;
            i = add_packet_length(length, getBufferByLength(length));

            if (unsubscribe->getPacketID() == 0) {
                printf("Encode. Unsubscribe. Unsubscribe must contain packetID");
            }
            i += add_short(&buffer[i], unsubscribe->getPacketID());

            for (int j = 0; j < unsubscribe->getTopics()->size(); j++) {
                string item = unsubscribe->getTopics()->at(j);
                string_length = strlen(item);
          			if (string_length != 0) {
            				i += add_short(&buffer[i], string_length);
            				memcpy(&buf[i], item, string_length);
            				i += string_length;
                }
            }
        }
        break;

        case MQ_UNSUBACK: {

            Unsuback *unsuback = (Unsuback *)message;
            buffer[i++] = messageType << 4;
            i = add_packet_length(length, getBufferByLength(length));
            if (unsuback->getPacketID() == 0) {
                printf("Encode. Unsuback. Unsuback must contain packetID");
            }
            add_short(&buffer[i], unsuback->getPacketID());
        }
        break;

        case MQ_DISCONNECT:
        case MQ_PINGREQ:
        case MQ_PINGRESP:
            buffer[i++] = messageType << 4;
            buffer[i] = (char) 0;
        break;

        default: printf("Encode. Type. Wrong message type"); break;
    }
    return buffer;
}

Message *Parser::decode(unsigned char * buf)
{
    Message *message = NULL;
    int i = 0;

    char fixedHeader = buf[i++];
    char messageType = ((fixedHeader >> 4) & 0xf);

    LengthDetails *length = LengthDetails::decode(buf);

    switch (messageType) {

        case MQ_CONNECT: {

            Connect *connect = new Connect();

            i += length->getSize();

            unsigned short protocol_name_size = get_short(buf, i);
        		i += 2;
        		char protocol_name[protocol_name_size];
            memcpy(protocolName, &buf[i], protocol_name_size);
            i += protocol_name_size;

            if (protocolName != connect->getProtocol()->getName()) {
                printf("Decode. Connect. Protocol name is wrong");
            }

            int protocolLevel = buf[i++];
            char contentFlags = buf[i++];

            bool usernameFlag = (((contentFlags >> 7) & 1) == 1) ? true : false;
            bool passwordFlag = (((contentFlags >> 6) & 1) == 1) ? true : false;
            bool willRetainFlag = (((contentFlags >> 5) & 1) == 1) ? true : false;

            int willQoSFlag = (((contentFlags & 0x1f) >> 3) & 3);
            QoS *willQoS = new QoS(willQoSFlag);

            if (willQoS->isValidForMQTT() != true) {
                printf(string("Decode. Connect. Will QoS set to ") + willQoS->getValue());
            }

            bool willFlag = (((contentFlags >> 2) & 1) == 1) ? true : false;

            if (willQoS->getValue() > 0 && !willFlag) {
                printf("Decode. Connect. Will retain set, willFlag not set");
            }

            bool cleanSessionFlag = (((contentFlags >> 1) & 1) == 1) ? true : false;
            bool reservedFlag = ((contentFlags  & 1) == 1) ? true : false;

            if (reservedFlag == true) {
                printf("Decode. Connect. Reserved flag set to true");
            }

            int keepalive = get_short(buf, i);
            i += 2;

            int client_id_lenght = get_short(buf, i);
        		i += 2;
        		char clientID[client_id_lenght];
        		memcpy(clientID, &buf[i], client_id_lenght);
        		i += client_id_lenght;
        		clientID[client_id_lenght] = '\0';

            if (willFlag == true) {
            			if ((length_details->getLength() - i) < 2) {
            				printf("Invalid encoding will/username/password\n");
            			}

            			int will_topic_lenght = get_short(buf, i);
            			i += 2;
            			if ((length_details->getLength() - i) < will_topic_lenght
            					|| will_topic_lenght < 1) {
            				printf("Invalid encoding will/username/password");
            			}
            			char will_topic[will_topic_lenght];
            			memcpy(will_topic, &buf[i], will_topic_lenght);
            			i += will_topic_lenght;
            			will_topic[will_topic_lenght] = '\0';
            			String willTopicName = will_topic;
            			if ((length_details->getLength() - i) < 2) {
            				printf("Invalid encoding will/username/password");
            			}
            			int will_message_lenght = get_short(buf, i);
            			i += 2;
            			if ((length_details->getLength() - i) < will_message_lenght) {
            				printf("Invalid encoding will/username/password");
            			}
            			char willMessageString[will_message_lenght];
            			memcpy(willMessageString, &buf[i], will_message_lenght);
            			i += will_message_lenght;
            			willMessageString[will_message_lenght] = '\0';
            }

            if (user_name_flag) {
            			if ((length_details->getLength() - i) < 2) {
            				printf("Invalid encoding will/username/password");
            				return m;
            			}

            			int username_lenght = get_short(buf, i);
            			i += 2;
            			if ((length_details->getLength() - i) < username_lenght) {
            				printf("Invalid encoding will/username/password");
            				return m;
            			}
            			char username[username_lenght];
            			memcpy(username, &buf[i], username_lenght);
            			i += username_lenght;
            			username[username_lenght] = '\0';
            }

            if (user_pass_flag) {
            			if ((length_details->getLength() - i) < 2) {
            				printf("Invalid encoding will/username/password");
            				return m;
            			}
            			int password_lenght = get_short(buf, i);
            			i += 2;
            			if ((length_details->getLength() - i) < password_lenght) {
            				printf("Invalid encoding will/username/password");
            				return m;
            			}
            			char password[password_lenght];
            			memcpy(password, &buf[i], password_lenght);
            			i += password_lenght;
            			password[password_lenght] = '\0';
            }

            connect->setUsername(username);
            connect->setPassword(password);
            connect->setClientID(clientID);
            connect->setCleanSession(cleanSessionFlag);
            connect->setKeepAlive(keepalive);
            connect->setWill(will);

            if (protocolLevel != 4) {
                connect->setProtocolLevel(protocolLevel);
            }
            message = connect;
        }
        break;

        case MQ_CONNACK: {

            Connack *connack = new Connack();

            char sessionPresentValue = buffer[i++];

            if (sessionPresentValue != 0 && sessionPresentValue != 1) {
                printf("Decode. Connack. Session-present set to " + sessionPresentValue);
            }

            bool isPresent = (sessionPresentValue == 1) ? true : false;
            MQConnackCode connectReturnCode = (MQConnackCode)buffer[i+];

            if (connack->isValidReturnCode(connectReturnCode) != true) {
                printf("Decode. Connack. Invalid connack code");
            }

            connack->setSessionPresent(isPresent);
            connack->setReturnCode(connectReturnCode);

            message = connack;
        }
        break;

        case MQ_PUBLISH: {

            int dataLength = length->getLength();
            fixedHeader &= 0xf;

            bool dup = (((fixedHeader >> 3) & 1) == 1)? true : false;

            QoS *qos = new QoS((fixedHeader & 0x07) >> 1);

            if (qos->isValidForMQTT() == false) {
                printf("Decode. Publish. Invalid QoS value");
            }

            if (dup == true && qos->getValue() == AT_MOST_ONCE) {
                printf("Decode. Publish. QoS-0 dup flag present");
            }

            bool isRetain = ((fixedHeader & 1) == 1) ? true : false;

            int topic_lenght = get_short(buf, i);
        		i += 2;
        		char * topicName = malloc (sizeof (topicName)*(topic_lenght+1));
        		memcpy(topicName, &buf[i], topic_lenght);
        		i += topic_lenght;
            topicName[topic_lenght] = '\0';

            dataLength -= topicName.length() + 2;

            int packetID = 0;

            if (qos->getValue() != AT_MOST_ONCE) {
                packetID = get_short(buf, i);
                i += 2;
                if (packetID < 0 || packetID > 65535) {
                    printf("Decode. Publish. Invalid Publish packetID encoding");
                }
                dataLength -= 2;
            }

            if (data_length > 0) {
            			char * data = malloc (sizeof (data)*(data_length+1));
            			memcpy(data, &buf[i], data_length);
            			data[data_length] = '\0';
            }

            MQTopic *topic = new MQTopic(topicName, qos);
            message = new Publish(packetID, topic, data, isRetain, dup);
        }
        break;

        case MQ_PUBACK: {

            int packetID = get_short(buf, ++i);
            message = new Puback(packetID);
        }
        break;

        case MQ_PUBREC: {

            int packetID = get_short(buf, ++i);
            message = new Pubrec(packetID);
        }
        break;

        case MQ_PUBREL: {

            int packetID = get_short(buf, ++i);
            message = new Pubrel(packetID);
        }
        break;

        case MQ_PUBCOMP: {

            int packetID = get_short(buf, ++i);
            message = new Pubcomp(packetID);
        }
        break;

        case MQ_SUBSCRIBE: {

            i += length->getSize();

            int subscribeID = get_short(buf, i);
            i += 2;

            list<MQTopic> *subscriptions;
            int topics_size = length_details->getLength() - i;
		        int topics_index = 0;
            int topic_length = 0;

            while (buffer->getSize() > 0) {
              topic_length = get_short(buf, i);
              i += 2;
              char topic[topic_length];
              memcpy(topic, &buf[i], topic_length);
              i += topic_length;

              QoS *qos = new QoS(buf[i++]);
              if (qos < 0 || qos > 2) {
                printf("Subscribe qos must be in range from 0 to 2: %d", qos);
              }
              topic[topic_length] = '\0';
              MQTopic *subscription = new MQTopic(topic, qos);
              subscriptions->insert(*subscription);
            }

            Subscribe *subscibe = new Subscribe(subscribeID);
            subscibe->setTopics(subscriptions);

            message = subscibe;
        }
        break;

        case MQ_SUBACK: {

            i += length->getSize();

            int subackID = get_short(buf, i);
            i += 2;

            list<SubackCode> *subackCodes;
            int codes_size = length_details->getLength() - i;
            Suback *suback = new Suback(subackID);

            while (buffer->getSize() > 0) {
                SubackCode subackByte = (SubackCode)buf[i++];
                subackCodes->insert(subackByte);
            }
            suback->setReturnCodes(subackCodes);
            message = suback;
        }
        break;

        case MQ_UNSUBSCRIBE: {

            i += length->getSize();

            int unsubackID = get_short(buf, i);
            i += 2;

            list<String> *unsubscribeTopics;

            int topics_size = length_details->getLength() - i;
        		int topics_index = 0;
        		int topic_length = 0;
        		while (i < topics_size) {
          			topic_length = get_short(buf, i);
          			i += 2;
          			char topic[topic_length];
          			memcpy(topic, &buf[i], topic_length);
          			i += topic_length;

          			if (utf8_check(topic) != NULL) {
          				printf("Unsubscribe topic contains one or more restricted characters: U+0000, U+D000-U+DFFF");
          				return m;
          			}
          			topic[topic_length] = '\0';
          			unsubscribeTopics->insert(topic);
            }
            Unsubscribe *unsuback = new Unsubscribe(unsubackID, unsubscribeTopics);
            message = unsuback;
        }
        break;

        case MQ_UNSUBACK: {

            int packetID = get_short(buf, ++i);
            message = new Unsuback(packetID);
        }
        break;

        case MQ_DISCONNECT: {

            message = new Disconnect();
        }
        break;

        case MQ_PINGREQ: {

            message = new Pingreq();
        }
        break;

        case MQ_PINGRESP:{

            message = new Pingresp();
        }
        break;


        default:  printf("Decode. Type. Wrong message type"); break;
    }

    if (length->getLength() != message->getLength()) {
        printf("Decode. Length. Invalid length. Encoded: "+length->getLength()+", actual: "+message->getLength());
    }

    return message;
}

unsigned char * Parser::getBufferByLength(int length)
{
    unsigned char byteArray[];
    int lng = length;
    unsigned char encodedByte;

    int i = 0
    do {
        encodedByte = (unsigned char)(lng % 128);
        lng /= 128;

        if (lng > 0) {
            byteArray[i++] = ((unsigned char)(encodedByte | 128));
        } else {
            byteArray[i++] = (encodedByte);
        }
    } while (lng > 0);

    return byteArray;
}
