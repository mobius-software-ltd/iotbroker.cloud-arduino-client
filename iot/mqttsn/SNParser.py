import iot.mqttsn.sn_messages.Advertise as Advertise
import iot.mqttsn.sn_messages.Encapsulated as Encapsulated
import iot.mqttsn.sn_messages.GWInfo as GWInfo
import iot.mqttsn.sn_messages.Regack as Regack
import iot.mqttsn.sn_messages.Register as Register
import iot.mqttsn.sn_messages.SearchGW as SearchGW
import iot.mqttsn.sn_messages.SNConnack as SNConnack
import iot.mqttsn.sn_messages.SNConnect as SNConnect
import iot.mqttsn.sn_messages.SNDisconnect as SNDisconnect
import iot.mqttsn.sn_messages.SNPingreq as SNPingreq
import iot.mqttsn.sn_messages.SNPingresp as SNPingresp
import iot.mqttsn.sn_messages.SNPuback as SNPuback
import iot.mqttsn.sn_messages.SNPubcomp as SNPubcomp
import iot.mqttsn.sn_messages.SNUnsuback as SNUnsuback
import iot.mqttsn.sn_messages.SNPublish as SNPublish
import iot.mqttsn.sn_messages.SNPubrec as SNPubrec
import iot.mqttsn.sn_messages.SNPubrel as SNPubrel
import iot.mqttsn.sn_messages.SNSuback as SNSuback
import iot.mqttsn.sn_messages.SNSubscribe as SNSubscribe
import iot.mqttsn.sn_messages.SNUnsubscribe as SNUnsubscribe
import iot.mqttsn.sn_messages.WillMsg as WillMsg
import iot.mqttsn.sn_messages.WillMsgReq as WillMsgReq
import iot.mqttsn.sn_messages.WillMsgResp as WillMsgResp
import iot.mqttsn.sn_messages.WillMsgUpd as WillMsgUpd
import iot.mqttsn.sn_messages.WillTopic as WillTopic
import iot.mqttsn.sn_messages.WillTopicReq as WillTopicReq
import iot.mqttsn.sn_messages.WillTopicResp as WillTopicResp
import iot.mqttsn.sn_messages.WillTopicUpd as WillTopicUpd

import iot.mqttsn.sn_classes.Flags as Flags
import iot.mqttsn.sn_classes.Controls as Controls
import iot.mqttsn.sn_classes.FullTopic as FullTopic
import iot.mqttsn.sn_classes.ShortTopic as ShortTopic
import iot.mqttsn.sn_classes.IdentifierTopic as IdentifierTopic
import iot.mqttsn.sn_classes.TopicType as TopicType
import iot.mqttsn.sn_classes.SNmessageType as SNmessageType

import struct

class snParser():
    def __init__(self, message):
        if message is not None:
            self.message = message
        self.index = 0
        self.length = 0

    def setMessage(self, message):
        if message is not None:
            self.message = message

    def encode(self):
        messageType = self.message.getType()
        buffer = encode_messageType_method(self, messageType, self.message)
        return buffer

    def decode(self, data):
        self.buffer = bytearray(data)
        length, index = self.decodeContentLength()
        self.index = index
        self.length = length
        messageType = struct.unpack('B',self.buffer[index:index+1])
        self.index += 1
        messageReturn = decode_messageType_method(self, messageType[0])
        self.index = 0
        return messageReturn

    def decodeContentLength(self):
        length = self.length
        index = self.index
        firstByte = struct.unpack('B', self.buffer[index:index+1])
        if firstByte[0] == 1:
            length = getShort(self.buffer[index+1:index+3])
            index += 3
        else:
            length = firstByte[0]
            index += 1
        return length, index

def ADVERTISE(self, message):
    data = bytearray()
    if message.getLength() <= 255:
        data = addByte(data, message.getLength())
    else:
        data = addByte(data, 1)
        data = addShort(data, message.getLength())

    data = addByte(data, int(message.getType()))
    data = addByte(data, int(message.getgwID()))
    data = addShort(data, int(message.getDuration()))

    return data

def SEARCHGW(self, message):
    data = bytearray()
    if message.getLength() <= 255:
        data = addByte(data, message.getLength())
    else:
        data = addByte(data, 1)
        data = addShort(data, message.getLength())

    data = addByte(data, int(message.getType()))
    data = addByte(data, int(message.getRadius()))
    
    return data

def GWINFO(self, message):
    data = bytearray()
    if message.getLength() <= 255:
        data = addByte(data, message.getLength())
    else:
        data = addByte(data, 1)
        data = addShort(data, message.getLength())

    data = addByte(data, int(message.getType()))
    data = addByte(data, message.getgwID())
    if message.getgwAddress() is not None and len(message.getgwAddress())>0:
	    data = addString(data, message.getgwAddress())

    return data

def CONNECT(self, message):
    data = bytearray()
    if message.getLength() <= 255:
        data = addByte(data, message.getLength())
    else:
        data = addByte(data, 1)
        data = addShort(data, message.getLength())

    data = addByte(data, int(message.getType()))
    flags = Flags.flags(False, None, False, message.getWillPresent(), message.getCleanSession(), None)
    flagsByte = flags.encode()
    data = addByte(data, flagsByte)
    data = addByte(data, message.getProtocolID())
    data = addShort(data, message.getDuration())
    data = addString(data, message.getClientID())
    
    return data

def CONNACK(self,message):
    data = bytearray()
    if message.getLength() <= 255:
        data = addByte(data, message.getLength())
    else:
        data = addByte(data, 1)
        data = addShort(data, message.getLength())

    data = addByte(data, int(message.getType()))
    data = addByte(data, message.getCode())
    
    return data

def WILL_TOPIC_RESP(self,message):
    data = bytearray()
    if message.getLength() <= 255:
        data = addByte(data, message.getLength())
    else:
        data = addByte(data, 1)
        data = addShort(data, message.getLength())

    data = addByte(data, int(message.getType()))
    data = addByte(data, message.getCode())
   
    return data

def WILL_MSG_RESP(self,message):
    data = bytearray()
    if message.getLength() <= 255:
        data = addByte(data, message.getLength())
    else:
        data = addByte(data, 1)
        data = addShort(data, message.getLength())

    data = addByte(data, int(message.getType()))
    data = addByte(data, message.getCode())
    
    return data

def WILL_TOPIC(self,message):
    data = bytearray()
    if message.getLength() <= 255:
        data = addByte(data, message.getLength())
    else:
        data = addByte(data, 1)
        data = addShort(data, message.getLength())

    data = addByte(data, int(message.getType()))
    if message.getTopic() is not None:
        flags = Flags.flags(False, message.getTopic().getQoS(), message.isRetain(), False, False, message.getTopic().getType())
        flagsByte = flags.encode()
        data = addByte(data, flagsByte)
        data = addString(data, message.getTopic().getValue())
        return data

def WILL_MSG(self,message):
    data = bytearray()
    if message.getLength() <= 255:
        data = addByte(data, message.getLength())
    else:
        data = addByte(data, 1)
        data = addShort(data, message.getLength())

    data = addByte(data, int(message.getType()))
    data = addString(data, message.getContent())

    return data

def REGISTER(self,message):
    data = bytearray()
    if message.getLength() <= 255:
        data = addByte(data, message.getLength())
    else:
        data = addByte(data, 1)
        data = addShort(data, message.getLength())

    data = addByte(data, int(message.getType()))
    data = addShort(data, message.getTopicID())
    data = addShort(data, message.getPacketID())
    data = addString(data, message.getTopicName())

    return data

def REGACK(self,message):
    data = bytearray()
    if message.getLength() <= 255:
        data = addByte(data, message.getLength())
    else:
        data = addByte(data, 1)
        data = addShort(data, message.getLength())

    data = addByte(data, int(message.getType()))
    data = addShort(data, message.getTopicID())
    data = addShort(data, message.getPacketID())
    data = addByte(data, message.getCode())

    return data

def PUBLISH(self,message):
    data = bytearray()
    if message.getLength() <= 255:
        data = addByte(data, message.getLength())
    else:
        data = addByte(data, 1)
        data = addShort(data, message.getLength())

    data = addByte(data, int(message.getType()))
    topic = message.getTopic()
    if topic is not None:
        flags = Flags.flags(message.isDup(), message.getTopic().getQoS(), message.isRetain(), False, False, message.getTopic().getType())
        flagsByte = flags.encode()
        data = addByte(data, flagsByte)

        if topic.getType() == TopicType.topicType.getValueByKey('NAMED'):
            data = addString(data, message.getTopic().getValue())
        else:
            data = addShort(data, message.getTopic().getValue())

        data = addShort(data, message.getPacketID())
        data = addString(data, message.getContent())
        return data
   
def PUBACK(self,message):
    data = bytearray()
    if message.getLength() <= 255:
        data = addByte(data, message.getLength())
    else:
        data = addByte(data, 1)
        data = addShort(data, message.getLength())

    data = addByte(data, int(message.getType()))
    data = addShort(data, message.getTopicID())
    data = addShort(data, message.getPacketID())
    data = addByte(data, message.getCode())

    return data

def PUBREC(self,message):
    data = bytearray()
    if message.getLength() <= 255:
        data = addByte(data, message.getLength())
    else:
        data = addByte(data, 1)
        data = addShort(data, message.getLength())

    data = addByte(data, int(message.getType()))
    data = addShort(data, message.getPacketID())
   
    return data

def PUBREL(self,message):
    data = bytearray()
    if message.getLength() <= 255:
        data = addByte(data, message.getLength())
    else:
        data = addByte(data, 1)
        data = addShort(data, message.getLength())

    data = addByte(data, int(message.getType()))
    data = addShort(data, message.getPacketID())
    
    return data

def PUBCOMP(self,message):
    data = bytearray()
    if message.getLength() <= 255:
        data = addByte(data, message.getLength())
    else:
        data = addByte(data, 1)
        data = addShort(data, message.getLength())

    data = addByte(data, int(message.getType()))
    data = addShort(data, message.getPacketID())
    
    return data

def UNSUBACK(self,message):
    data = bytearray()
    if message.getLength() <= 255:
        data = addByte(data, message.getLength())
    else:
        data = addByte(data, 1)
        data = addShort(data, message.getLength())

    data = addByte(data, int(message.getType()))
    data = addShort(data, message.getPacketID())
    
    return data

def SUBSCRIBE(self,message):
    data = bytearray()
    if message.getLength() <= 255:
        data = addByte(data, message.getLength())
    else:
        data = addByte(data, 1)
        data = addShort(data, message.getLength())

    data = addByte(data, message.getType())
    topic = message.getTopic()
    if topic is not None:
        flags = Flags.flags(message.isDup(), message.getTopic().getQoS(), False, False, False, message.getTopic().getType())
        flagsByte = flags.encode()
        data = addByte(data, flagsByte)
        data = addShort(data, message.getPacketID())

        if topic.getType() == TopicType.topicType.getValueByKey('NAMED'):
            data = addString(data, message.getTopic().getValue())
        else:
            data = addShort(data, message.getTopic().getValue())
        return data

def SUBACK(self,message):
    data = bytearray()
    if message.getLength() <= 255:
        data = addByte(data, message.getLength())
    else:
        data = addByte(data, 1)
        data = addShort(data, message.getLength())

    data = addByte(data, int(message.getType()))
    flags = Flags.flags(False, message.getQoS(), False, False, False, None)
    flagsByte = flags.encode()
    data = addByte(data, flagsByte)
    data = addShort(data, message.getTopicID())
    data = addShort(data, message.getPacketID())
    data = addByte(data, message.getCode())
    return data

def UNSUBSCRIBE(self,message):
    data = bytearray()
    if message.getLength() <= 255:
        data = addByte(data, message.getLength())
    else:
        data = addByte(data, 1)
        data = addShort(data, message.getLength())

    data = addByte(data, int(message.getType()))
    if message.getTopic() is not None:
        flags = Flags.flags(False,message.getTopic().getQoS(),False,False,False,message.getTopic().getType())
        flagsByte = flags.encode()
        data = addByte(data, flagsByte)
        data = addShort(data, message.getPacketID())
        data = addString(data, message.getTopic().getValue())
        return data

def PINGREQ(self,message):
    data = bytearray()
    if message.getLength() <= 255:
        data = addByte(data, message.getLength())
    else:
        data = addByte(data, 1)
        data = addShort(data, message.getLength())

    if message.getLength() > 2:
        data = addByte(data, int(message.getType()))
        data = addString(data, message.getClientID())
        return data
    else:
        return data

def DISCONNECT(self,message):
    data = bytearray()
    data = addByte(data, message.getLength())

    data = addByte(data, int(message.getType()))
    if message.getLength() > 2:
        data = addShort(data, message.getDuration())
    return data

def WILL_TOPIC_UPD(self,message):
    data = bytearray()
    if message.getLength() <= 255:
        data = addByte(data, message.getLength())
    else:
        data = addByte(data, 1)
        data = addShort(data, message.getLength())

    data = addByte(data, int(message.getType()))
    if message.getTopic() is not None:
        flags = Flags.flags(False,message.getTopic().getQoS(),message.isRetain(),False,False,None)
        flagsByte = flags.encode()
        data = addByte(data, flagsByte)
        data = addString(data, message.getTopic().getValue())
        return data

def WILL_MSG_UPD(self,message):
    data = bytearray()
    if message.getLength() <= 255:
        data = addByte(data, message.getLength())
    else:
        data = addByte(data, 1)
        data = addShort(data, message.getLength())

    data = addByte(data, int(message.getType()))
    if message.getContent() is not None:
        data = addString(data, message.getContent())
        return data

def WILL_TOPIC_REQ(self,message):
    print('Encode.willTopicReq not parse message')

def WILL_MSG_REQ(self,message):
    print('Encode.willMsgReq not parse message')

def PINGRESP(self,message):
    print('Encode.pingResp not parse message')

def ENCAPSULATED(self,message):
    data = bytearray()
    if message.getLength() <= 255:
        data = addByte(data, message.getLength())
    else:
        data = addByte(data, 1)
        data = addShort(data, message.getLength())

    data = addByte(data, int(message.getType()))
    data = addByte(data, Controls.controls.encode(message.getRadius()))
    data = addString(data, message.getWirelessNodeID())
    data = addString(data, message.getMessage())
    return data

switcherEncode = {
        0: ADVERTISE,
        1: SEARCHGW,
        2: GWINFO,
        4: CONNECT,
        5: CONNACK,
        6: WILL_TOPIC_REQ,
        7: WILL_TOPIC,
        8: WILL_MSG_REQ,
        9: WILL_MSG,
        10: REGISTER,
        11: REGACK,
        12: PUBLISH,
        13: PUBACK,
        14: PUBCOMP,
        15: PUBREC,
        16: PUBREL,
        18: SUBSCRIBE,
        19: SUBACK,
        20: UNSUBSCRIBE,
        21: UNSUBACK,
        22: PINGREQ,
        23: PINGRESP,
        24: DISCONNECT,
        26: WILL_TOPIC_UPD,
        27: WILL_TOPIC_RESP,
        28: WILL_MSG_UPD,
        29: WILL_MSG_RESP,
        254: ENCAPSULATED
    }

def encode_messageType_method(self, argument, message):
    return switcherEncode[argument].__call__(self, message)

def ADVERTISE_DECODE(self):
    data = bytearray(self.buffer)
    gwId = getByte(data,self.index)
    duration = getShort(data[self.index+1:self.index+3])
    message = Advertise.advertise(gwId, duration)
    return message

def SEARCHGW_DECODE(self):
    data = bytearray(self.buffer)
    radius = getByte(data,self.index)
    message = SearchGW.searchGW(radius)
    return message

def GWINFO_DECODE(self):
    data = bytearray(self.buffer)
    infogwId = getByte(data, self.index)
    if self.index+1 < self.length:
        gwInfoAddress = getString(data[self.index+1:len(data)])
        gwInfoAddress = gwInfoAddress.strip()
    message = GWInfo.gwInfo(infogwId, gwInfoAddress)
    return message

def CONNECT_DECODE(self):
    data = bytearray(self.buffer)
    decodeFlags = Flags.flags(False, None, False, False, False, None)
    flags = decodeFlags.decode(getByte(data, self.index), SNmessageType.snMessageType.getValueByKey('SN_CONNECT'))
    self.index += 1
    protocolID = getByte(data, self.index)
    if protocolID != 1:
        print('Invalid protocolID ' + protocolID)
    self.index += 1
    duration = getShort(data[self.index:self.index + 2])
    self.index += 2
    clientID = getString(data[self.index:len(data)])
    clientID = clientID.strip()
    message = SNConnect.snConnect(flags.isWill(), flags.isClean(), duration, clientID)
    return message

def CONNACK_DECODE(self):
    data = bytearray(self.buffer)
    code = getByte(data, self.index)
    message = SNConnack.snConnack(code)
    return message

def WILL_TOPIC_REQ_DECODE(self):
    data = bytearray(self.buffer)
    message = WillTopicReq.willTopicReq()
    return message

def WILL_TOPIC_DECODE(self):
    data = bytearray(self.buffer)
    retain = False
    willTopic = None
    if self.index < len(data):
        decodeFlags = Flags.flags(False, None, False, False, False, None)
        flags = decodeFlags.decode(getByte(data, self.index), SNmessageType.snMessageType.getValueByKey('SN_WILL_TOPIC'))
        self.index += 1
        retain = flags.isRetain()
        value = getString(data[self.index:len(data)])
        value = value.strip()
        willTopic = FullTopic.fullTopic(value, flags.getQoS())
    message = WillTopic.willTopic(retain, willTopic)
    return message

def WILL_MSG_REQ_DECODE(self):
    data = bytearray(self.buffer)
    message = WillMsgReq.willMsgReq()
    return message

def WILL_MSG_DECODE(self):
    data = bytearray(self.buffer)
    if self.index < len(data):
        content = getString(data[self.index:len(data)])
    message = WillMsg.willMsg(content)
    return message

def REGISTER_DECODE(self):
    data = bytearray(self.buffer)
    topicID = getShort(data[self.index:self.index + 2])
    self.index += 2
    messageID = getShort(data[self.index:self.index + 2])
    self.index += 2
    if self.index < self.length:
        topicName = getString(data[self.index:len(data)])
    message = Register.register(topicID, messageID, topicName)
    return message

def REGACK_DECODE(self):
    data = bytearray(self.buffer)
    topicID = getShort(data[self.index:self.index + 2])
    self.index += 2
    messageID = getShort(data[self.index:self.index + 2])
    self.index += 2
    code = getByte(data,self.index)
    message = Regack.regack(topicID, messageID, code)
    return message

def PUBLISH_DECODE(self):
    data = bytearray(self.buffer)
    decodeFlags = Flags.flags(False, None, False, False, False, None)
    flags = decodeFlags.decode(getByte(data, self.index), SNmessageType.snMessageType.getValueByKey('SN_PUBLISH'))
    self.index += 1
    topicID = getShort(data[self.index:self.index + 2])
    self.index += 2
    messageID = getShort(data[self.index:self.index + 2])
    self.index += 2
    if flags.getQoS() != 0 and messageID == 0:
        print('invalid PUBLISH QoS-0 messageID: ' + messageID)
    topic = None
    if flags.getTopicType() == TopicType.SHORT: #SHORT
        topic = ShortTopic.shortTopic(topicID, flags.getQoS())
    else:
        topic = IdentifierTopic.identifierTopic(topicID, flags.getQoS())
    content = ''
    if self.index < self.length:
        content = getString(data[self.index:len(data)])
        content.strip()
    message = SNPublish.snPublish(messageID,topic,content,flags.isDup(),flags.isRetain())
    return message

def PUBACK_DECODE(self):
    data = bytearray(self.buffer)
    topicID = getShort(data[self.index:self.index + 2])
    self.index += 2
    messageID = getShort(data[self.index:self.index + 2])
    self.index += 2
    code = getByte(data, self.index)
    message = SNPuback.snPuback(topicID, messageID, code)
    return message

def PUBREC_DECODE(self):
    data = bytearray(self.buffer)
    messageID = getShort(data[self.index:self.index + 2])
    message = SNPubrec.snPubrec(messageID)
    return message

def PUBREL_DECODE(self):
    data = bytearray(self.buffer)
    messageID = getShort(data[self.index:self.index + 2])
    message = SNPubrel.snPubrel(messageID)
    return message

def PUBCOMP_DECODE(self):
    data = bytearray(self.buffer)
    messageID = getShort(data[self.index:self.index + 2])
    message = SNPubcomp.snPubcomp(messageID)
    return message

def SUBSCRIBE_DECODE(self):
    data = bytearray(self.buffer)
    decodeFlags = Flags.flags(False, None, False, False, False, None)
    flags = decodeFlags.decode(getByte(data, self.index), SNmessageType.snMessageType.getValueByKey('SN_WILL_TOPIC'))
    self.index += 1
    messageID = getShort(data[self.index:self.index + 2])
    self.index += 2
    topic = None
    if self.index < self.length:
        if flags.getTopicType() == TopicType.NAMED:
            topicName = getString(data[self.index:len(data)])
            topic = FullTopic.fullTopic(topicName, flags.getQoS())
        if flags.getTopicType() == TopicType.ID:
            topicID = getShort(data[self.index:self.index + 2])
            topic = IdentifierTopic.identifierTopic(topicName, flags.getQoS())
        if flags.getTopicType() == TopicType.SHORT:
            topicID = getShort(data[self.index:self.index + 2])
            topic = ShortTopic.shortTopic(topicID, flags.getQoS())
    message = SNSubscribe.snSubscribe(messageID, topic, flags.isDup())
    return message

def SUBACK_DECODE(self):
    data = bytearray(self.buffer)
    decodeFlags = Flags.flags(False, None, False, False, False, None)
    flags = decodeFlags.decode(getByte(data, self.index), SNmessageType.snMessageType.getValueByKey('SN_SUBACK'))
    self.index += 1
    topicID = getShort(data[self.index:self.index + 2])
    self.index += 2
    messageID = getShort(data[self.index:self.index + 2])
    self.index += 2
    code = getByte(data, self.index)
    message = SNSuback.snSuback(topicID, code, flags.getQoS(), messageID)
    return message

def UNSUBSCRIBE_DECODE(self):
    data = bytearray(self.buffer)
    decodeFlags = Flags.flags(False, None, False, False, False, None)
    flags = decodeFlags.decode(getByte(data, self.index), SNmessageType.snMessageType.getValueByKey('SN_UNSUBSCRIBE'))
    self.index += 1
    messageID = getShort(data[self.index:self.index + 2])
    self.index += 2
    topic = None
    if self.index < self.length:
        if flags.getTopicType() == TopicType.NAMED:
            topicName = getString(data[self.index:len(data)])
            topic = FullTopic.fullTopic(topicName, flags.getQoS())
        if flags.getTopicType() == TopicType.ID: #ID
            topicID = getShort(data[self.index:self.index + 2])
            topic = IdentifierTopic.identifierTopic(topicName, flags.getQoS())
        if flags.getTopicType() == TopicType.SHORT: #SHORT
            topicName = getString(data[self.index:len(data)])
            topic = ShortTopic.shortTopic(topicName, flags.getQoS())
    message = SNUnsubscribe.snUnsubscribe(messageID, topic)
    return message

def UNSUBACK_DECODE(self):
    data = bytearray(self.buffer)
    messageID = getShort(data[self.index:self.index + 2])
    message = SNUnsuback.snUnsuback(messageID)
    return message

def PINGREQ_DECODE(self):
    data = bytearray(self.buffer)
    clientID = None
    if self.index < self.length:
        clientID = getString(data[self.index:len(data)])
    message = SNPingreq.snPingreq(clientID.strip())
    return message

def PINGRESP_DECODE(self):
    data = bytearray(self.buffer)
    message = SNPingresp.snPingresp()
    return message

def DISCONNECT_DECODE(self):
    data = bytearray(self.buffer)
    duration = 0
    if self.index < self.length:
        duration = getShort(data[self.index:self.index + 2])
    message = SNDisconnect.snDisconnect(duration)
    return message

def WILL_TOPIC_UPD_DECODE(self):
    data = bytearray(self.buffer)
    topic = None
    retain = False
    if self.index < self.length:
        decodeFlags = Flags.flags(False, None, False, False, False, None)
        flags = decodeFlags.decode(getByte(data, self.index), SNmessageType.snMessageType.getValueByKey('SN_WILL_TOPIC_UPD'))
        self.index += 1
        retain = flags.isRetain()
        value = getString(data[self.index:len(data)])
        topic = FullTopic.fullTopic(value, flags.getQoS())
    message = WillTopicUpd.willTopicUpd(retain, topic)
    return message

def WILL_MSG_UPD_DECODE(self):
    data = bytearray(self.buffer)
    content = ''
    if self.index < self.length:
        content = getString(data[self.index:len(data)])
    message = WillMsgUpd.willMsgUpd(content)
    return message

def WILL_TOPIC_RESP_DECODE(self):
    data = bytearray(self.buffer)
    code = getByte(data, self.index)
    message = WillTopicResp.willTopicResp(code)
    return message

def WILL_MSG_RESP_DECODE(self):
    data = bytearray(self.buffer)
    code = getByte(data, self.index)
    message = WillMsgResp.willMsgResp(code)
    return message

def ENCAPSULATED_DECODE(self):
    print('Encapsulated.decode ')

switcherDecode = {
        0: ADVERTISE_DECODE,
        1: SEARCHGW_DECODE,
        2: GWINFO_DECODE,
        4: CONNECT_DECODE,
        5: CONNACK_DECODE,
        6: WILL_TOPIC_REQ_DECODE,
        7: WILL_TOPIC_DECODE,
        8: WILL_MSG_REQ_DECODE,
        9: WILL_MSG_DECODE,
        10: REGISTER_DECODE,
        11: REGACK_DECODE,
        12: PUBLISH_DECODE,
        13: PUBACK_DECODE,
        14: PUBCOMP_DECODE,
        15: PUBREC_DECODE,
        16: PUBREL_DECODE,
        18: SUBSCRIBE_DECODE,
        19: SUBACK_DECODE,
        20: UNSUBSCRIBE_DECODE,
        21: UNSUBACK_DECODE,
        22: PINGREQ_DECODE,
        23: PINGRESP_DECODE,
        24: DISCONNECT_DECODE,
        26: WILL_TOPIC_UPD_DECODE,
        27: WILL_TOPIC_RESP_DECODE,
        28: WILL_MSG_UPD_DECODE,
        29: WILL_MSG_RESP_DECODE,
        254: ENCAPSULATED_DECODE
    }

def decode_messageType_method(self, argument):
    return switcherDecode[argument].__call__(self)

def addByte(data, byte):
    data.append(byte)
    return data

def getByte(data, index):
    tuple = struct.unpack('B', data[index: index+1])
    return tuple[0]

def addShort(data, short):
    dataStruct  = struct.pack('h', short)
    data += dataStruct[::-1]
    return data

def getShort(data):
    tuple = struct.unpack('h', data[::-1])
    return tuple[0]

def addString(dataIn, text):
    data = dataIn
    for ch in text:
        ch = bytes(ch, encoding='utf_8')
        data += struct.pack('c', ch)
    return data

def getString(data):
    return data.decode('utf_8')
