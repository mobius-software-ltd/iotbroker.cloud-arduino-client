#include "mqjsonparser.h"
#include "rapidjson/document.h"
#include "utils/base64.h"

#include "iot-protocols/mqtt/classes/mqttenums.h"
#include "iot-protocols/mqtt/messages/connect.h"
#include "iot-protocols/mqtt/messages/connack.h"
#include "iot-protocols/mqtt/messages/disconnect.h"
#include "iot-protocols/mqtt/messages/pingreq.h"
#include "iot-protocols/mqtt/messages/pingresp.h"
#include "iot-protocols/mqtt/messages/publish.h"
#include "iot-protocols/mqtt/messages/puback.h"
#include "iot-protocols/mqtt/messages/pubcomp.h"
#include "iot-protocols/mqtt/messages/pubrec.h"
#include "iot-protocols/mqtt/messages/pubrel.h"
#include "iot-protocols/mqtt/messages/subscribe.h"
#include "iot-protocols/mqtt/messages/suback.h"
#include "iot-protocols/mqtt/messages/unsubscribe.h"
#include "iot-protocols/mqtt/messages/unsuback.h"

unsigned char[] MQJsonParser::json(Message *message)
{
    Value json_val;
    Document doc;
    auto& allocator = doc.GetAllocator();
    doc.SetObject();

    MQMessageType type = (MQMessageType)message->getType();

    switch (type) {

    case MQ_CONNECT: {
        Connect *connect = (Connect *)message;
        json_val.SetInt(connect->getType());
        doc.AddMember("packet", json_val, allocator);
        json_val.SetInt(connect->getProtocolLevel());
        doc.AddMember("protocolLevel", json_val, allocator);
        json_val.SetString(connect->getUsername());
        doc.AddMember("username", json_val, allocator);
        json_val.SetString(connect->getPassword());
        doc.AddMember("password", json_val, allocator);
        json_val.SetString(connect->getClientID());
        doc.AddMember("clientID", json_val, allocator);
        json_val.SetBool(connect->isCleanSession());
        doc.AddMember("cleanSession", json_val, allocator);
        json_val.SetInt(connect->getKeepAlive());
        doc.AddMember("keepalive", json_val, allocator);
        json_val.SetBool(connect->isWillFlag());
        doc.AddMember("willFlag", json_val, allocator);
        json_val.SetBool(connect->isUsernameFlag());
        doc.AddMember("usernameFlag", json_val, allocator);
        json_val.SetBool(connect->isPasswordFlag());
        doc.AddMember("passwordFlag", json_val, allocator);
        if (connect->isWillFlag()) {
            Document docTopic;
            docTopic.SetObject();
            json_val.SetString(connect->getWill()->getTopic()->getName());
            docTopic.AddMember("name", json_val, allocator);
            json_val.SetInt(connect->getWill()->getTopic()->getQoS()->getValue());
            docTopic.AddMember("qos", json_val, allocator);
            Document docWill;
            docWill.SetObject();
            json_val.CopyFrom(docTopic);
            docWill.AddMember("topic", json_val, allocator);
            json_val.SetString(connect->getWill()->getContent().toBase64());
            docWill.AddMember("content", json_val, allocator);
            json_val.SetBool(connect->getWill()->isRetain());
            doc.AddMember("retain", json_val, allocator);
            json_val.CopyFrom(docWill);
            doc.AddMember("will", json_val, allocator);
        } else {
          doc.AddMember("will", null, allocator);
        }
    } break;
    case MQ_CONNACK: {
        Connack *connack = (Connack *)message;
        json_val.SetInt(connect->getType());
        doc.AddMember("packet", json_val, allocator);
        json_val.SetBool(connect->isSessionPresent());
        doc.AddMember("sessionPresent", json_val, allocator);
        json_val.SetInt(connect->getReturnCode());
        doc.AddMember("returnCode", json_val, allocator);
    } break;
    case MQ_PUBLISH: {
        Publish *publish = (Publish *)message;
        json_val.SetInt(connect->getType());
        doc.AddMember("packet", json_val, allocator);
        if (publish->getPacketID() == 0) {
            doc.AddMember("packetID", null, allocator);
        } else {
            json_val.SetInt(connect->getPacketID());
            doc.AddMember("packetID", json_val, allocator);
        }
        Document docTopic;
        docTopic.SetObject();
        json_val.SetString(publish->getTopic()->getName());
        docTopic.AddMember("name", json_val, allocator);
        json_val.SetInt(publish->getTopic()->getQoS()->getValue());
        docTopic.AddMember("qos", json_val, allocator);
        json_val.CopyFrom(docTopic);
        doc.AddMember("topic", json_val, allocator);
        json_val.SetString(publish->getContent().toBase64());
        doc.AddMember("content", json_val, allocator);
        json_val.SetBool(publish->isRetain());
        doc.AddMember("retain", json_val, allocator);
        json_val.SetBool(publish->isDup());
        doc.AddMember("retain", json_val, allocator);
    } break;
    case MQ_PUBACK: {
        Puback *puback = (Puback *)message;
        json_val.SetInt(puback->getType());
        doc.AddMember("packet", json_val, allocator);
        json_val.SetInt(puback->getPacketID());
        doc.AddMember("packetID", json_val, allocator);
    } break;
    case MQ_PUBREC: {
        Pubrec *pubrec = (Pubrec *)message;
        json_val.SetInt( pubrec->getType());
        doc.AddMember("packet", json_val, allocator);
        json_val.SetInt( pubrec->getPacketID());
        doc.AddMember("packetID", json_val, allocator);
    } break;
    case MQ_PUBREL: {
        Pubrel *pubrel = (Pubrel *)message;
        json_val.SetInt( pubrel->getType());
        doc.AddMember("packet", json_val, allocator);
        json_val.SetInt( pubrel->getPacketID());
        doc.AddMember("packetID", json_val, allocator);
    } break;
    case MQ_PUBCOMP: {
        Pubcomp *pubcomp = (Pubcomp *)message;
        json_val.SetInt( pubcomp->getType());
        doc.AddMember("packet", json_val, allocator);
        json_val.SetInt( pubcomp->getPacketID());
        doc.AddMember("packetID", json_val, allocator);
    } break;
    case MQ_SUBSCRIBE: {
        Subscribe *subscribe = (Subscribe *)message;
        json_val.SetInt( subscribe->getType());
        doc.AddMember("packet", json_val, allocator);
        json_val.SetInt( subscribe->getPacketID());
        doc.AddMember("packetID", json_val, allocator);
        Document docTopic;
        docTopic.SetObject();
        Value topics(kArrayType);
        list<MQTopic> listTopics = subscribe->getTopics()
        listTopics::iterator it;
        for (it = data.begin(); it != data.end(); ++it){
            MQTopic topic = it;
            json_val.SetString(topic.getName());
            docTopic.AddMember("name", json_val, allocator);
            json_val.SetInt(topic.getQoS()->getValue());
            docTopic.AddMember("qos", json_val, allocator);
            topics.PushBack(docTopic, allocator)
        }
        json_val.SetArray(topics);
        doc.AddMember("topics", json_val, allocator);
    } break;
    case MQ_SUBACK: {
        Suback *suback = (Suback *)message;
        json_val.SetInt( suback->getType());
        doc.AddMember("packet", json_val, allocator);
        json_val.SetInt( suback->getPacketID());
        doc.AddMember("packetID", json_val, allocator);
        json_val.SetArray(suback->getReturnCodes());
        doc.AddMember("returnCodes", json_val, allocator);
    } break;
    case MQ_UNSUBSCRIBE: {
        Unsubscribe *unsubscribe = (Unsubscribe *)message;
        json_val.SetInt( unsubscribe->getType());
        doc.AddMember("packet", json_val, allocator);
        json_val.SetInt( unsubscribe->getPacketID());
        doc.AddMember("packetID", json_val, allocator);
        json_val.SetArray(unsubscribe->getTopics());
        doc.AddMember("topics", json_val, allocator);
    } break;
    case MQ_UNSUBACK: {
        Unsuback *unsuback = (Unsuback *)message;
        json_val.SetInt( unsuback->getType());
        doc.AddMember("packet", json_val, allocator);
        json_val.SetInt( unsuback->getPacketID());
        doc.AddMember("packetID", json_val, allocator);
    } break;
    case MQ_PINGREQ: {
        Pingreq *pingreq = (Pingreq *)message;
        json_val.SetInt( pingreq->getType());
        doc.AddMember("packet", json_val, allocator);
    } break;
    case MQ_PINGRESP: {
        Pingresp *pingresp = (Pingresp *)message;
        json_val.SetInt( pingresp->getType());
        doc.AddMember("packet", json_val, allocator);
    } break;
    case MQ_DISCONNECT: {
        Disconnect *disconnect = (Disconnect *)message;
        json_val.SetInt( disconnect->getType());
        doc.AddMember("packet", json_val, allocator);
    } break;
    default:

        return unsigned char byte[];
    }
    return doc;
}

Message *MQJsonParser::message(const Value& doc)
{
    if (doc.IsObject()) {
        MQMessageType type = (MQMessageType)doc["packet"].GetInt();

        switch (type) {

        case MQ_CONNECT: {
            Connect *connect = new Connect();
            connect->setUsername(doc["username"].GetString());
            connect->setPassword(doc["password"].GetString());
            connect->setClientID(doc["clientID"].GetString());
            connect->setCleanSession(doc["cleanSession"].GetBool());
            connect->setKeepAlive(doc["keepalive"].GetInt());

            if (doc.HasMember("will")) {
                Will *will = new Will();
                Document willObj = doc["will"].GetObject(();
                if (willObj.HasMember("topic")) {
                    Document topicObj = willObj["topic"].GetObject();
                    MQTopic *topic = new MQTopic(topicObj["name"].GetString(), new QoS(topicObj["qos"].GetInt()));
                    will->setTopic(topic);
                }
                will->setContent(base64_decode(willObj["content"].GetString().toUtf8()));
                will->setRetain(willObj["retain"].GetBool());

                connect->setWill(will);
            }
            return connect;
        } break;
        case MQ_CONNACK: {
            Connack *connack = new Connack();
            connack->setSessionPresent(doc["sessionPresent"].GetBool());
            connack->setReturnCode((MQConnackCode)doc["returnCode"].GetInt());
            return connack;
        } break;
        case MQ_PUBLISH: {
            Publish *publish = new Publish();
            publish->setPacketID(doc["packetID"].GetInt());
            if (doc.HasMember("topic")) {
                Document topicObj = doc["topic"].GetObject();
                MQTopic *topic = new MQTopic(topicObj["name"].GetString(), new QoS(topicObj["qos"].GetInt()));
                publish->setTopic(topic);
            }
            publish->setContent(base64_decode(doc["content"].GetString().toUtf8()));
            publish->setRetain(doc["retain"].GetBool());
            publish->setDup(doc["dup"].GetBool());
            return publish;
        } break;
        case MQ_PUBACK: {
            Puback *puback = new Puback();
            puback->setPacketID(doc["packetID"].GetInt());
            return puback;
        } break;
        case MQ_PUBREC: {
            Pubrec *pubrec = new Pubrec();
            pubrec->setPacketID(doc["packetID"].GetInt());
            return pubrec;
        } break;
        case MQ_PUBREL: {
            Pubrel *pubrel = new Pubrel();
            pubrel->setPacketID(doc["packetID"].GetInt());
            return pubrel;
        } break;
        case MQ_PUBCOMP: {
            Pubcomp *pubcomp = new Pubcomp();
            pubcomp->setPacketID(doc["packetID"].GetInt());
            return pubcomp;
        } break;
        case MQ_SUBSCRIBE: {
            Subscribe *subscribe = new Subscribe();
            subscribe->setPacketID(doc["packetID"].GetInt());
            if (doc.HasMember("topic")) {
                list<MQTopic> *listTopics = new list<MQTopic>();
                Value topics(kArrayType) = doc["topics"].GetArray();
                topics::iterator it;
                for (it = data.begin(); it != data.end(); ++it){
                  Document topicObj = it.GetObject();
                  MQTopic topic = MQTopic(topicObj["name"].GetString(), new QoS(topicObj["qos"].GetInt()));
                  listTopics->append(topic);
                }
                subscribe->setTopics(listTopics);
            }
            return subscribe;
        } break;
        case MQ_SUBACK: {
            Suback *suback = new Suback();
            suback->setPacketID(doc["packetID"].GetInt());
            if (doc.HasMember("returnCodes")) {
                list<SubackCode> *listCodes = doc["returnCodes"].GetArray();
                suback->setReturnCodes(listCodes);
            }
            return suback;
        } break;
        case MQ_UNSUBSCRIBE: {
            Unsubscribe *unsubscribe = new Unsubscribe();
            unsubscribe->setPacketID(doc["packetID"].GetInt());
            if (doc.HasMember("topics")) {
                list<String> *listTopics = obj["topics"].GetArray();
                unsubscribe->setTopics(listTopics);
            }
            return unsubscribe;
        } break;
        case MQ_UNSUBACK: {
            Unsuback *unsuback = new Unsuback();
            unsuback->setPacketID(doc["packetID"].GetInt());
            return unsuback;
        } break;
        case MQ_PINGREQ: {
            Pingreq *pingreq = new Pingreq();
            return pingreq;
        } break;
        case MQ_PINGRESP: {
            Pingresp *pingresp = new Pingresp();
            return pingresp;
        } break;
        case MQ_DISCONNECT: {
            Disconnect *disconnect = new Disconnect();
            return disconnect;
        } break;
        default:
            return NULL;
        }
    }

    return NULL;
}
