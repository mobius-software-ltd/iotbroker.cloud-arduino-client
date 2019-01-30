import iot.classes.Qos as Qos
import iot.classes.QosType as QosType
import iot.network.UdpClient as UdpClient
import iot.mqttsn.SNParser as SNParser
import iot.timers.TimersMap as TimersMap
import iot.mqttsn.sn_classes.ReturnCode as ReturnCode
import iot.mqttsn.sn_classes.FullTopic as FullTopic
import iot.mqttsn.sn_classes.IdentifierTopic as IdentifierTopic
import iot.mqttsn.sn_classes.SNmessageType as SNmessageType
import iot.mqttsn.sn_messages.SNConnect as SNConnect
import iot.mqttsn.sn_messages.SNDisconnect as SNDisconnect
import iot.mqttsn.sn_messages.Register as Register
import iot.mqttsn.sn_messages.SNPublish as SNPublish
import iot.mqttsn.sn_messages.Regack as Regack
import iot.mqttsn.sn_messages.SNPingreq as SNPingreq
import iot.mqttsn.sn_messages.SNPuback as SNPuback
import iot.mqttsn.sn_messages.SNPubcomp as SNPubcomp
import iot.mqttsn.sn_messages.SNPubrec as SNPubrec
import iot.mqttsn.sn_messages.SNPubrel as SNPubrel
import iot.mqttsn.sn_messages.SNSubscribe as SNSubscribe
import iot.mqttsn.sn_messages.SNUnsubscribe as SNUnsubscribe
import iot.mqttsn.sn_messages.WillTopic as WillTopic
import iot.mqttsn.sn_messages.WillMsg as WillMsg

class snClient():
    def __init__(self, account):
        self.account = account
        self.parser = SNParser.snParser(None)
        self.resendperiod = 3000
        self.data = None
        self.udpClient = None
        self.timers = TimersMap.timersMap(self)
        self.forPublish = {}
        self.registerID = 0
        self.publishPackets = {}
        self.topics = {}
        self.connectionState = 0
        self.snMessageType = SNmessageType.snMessageType()
        self.returnCode = ReturnCode.returnCode()
        self.QosType = QosType.qosType()

    def send(self, message):
        if self.connectionState == 5: #CONNECTION_ESTABLISHED
            self.parser.setMessage(message)
            message = self.parser.encode()
            self.udpClient.sendMessage(message)
        else:
            return False

    def dataReceived(self, data):
        message = self.parser.decode(data)
        process_messageType_method(self, message.getType(), message)

    def setState(self, connectionState):
        self.connectionState = connectionState

    def getConnectionState(self):
        return self.connectionState

    def goConnect(self):
        self.setState(4) #CONNECTING

        if self.account.will is not None and len(self.account.will)> 0:
            willPresent = True
        else:
            willPresent = False

        cleanSession = self.account.isClean
        duration = self.account.keepAlive
        clientID = self.account.clientID
        connect = SNConnect.snConnect(willPresent, cleanSession, duration, clientID)

        if self.timers is not None:
            self.timers.stopAllTimers()
        #self.timers.goConnectTimer(connect)

        self.parser.setMessage(connect)
        message = self.parser.encode()

        self.UdpClient = UdpClient.udpClient(self.account.host, self.account.port, self)
        if self.account.enable:
            self.UdpClient.connectSecure(self.account.cert_path, self.account.key_path)
        else:
            self.UdpClient.connect()
        self.udpClient.sendMessage(message)

    def publish(self, topicName, qosValue, content, retain, dup):
        qos = Qos.qos(qosValue)
        topic = FullTopic.fullTopic(topicName, qos)
        register = Register.register(0,0,topicName)
        publish = SNPublish.snPublish(0,topic,content,dup,retain)
        self.registerID = self.timers.goMessageTimer(register)
        self.forPublish[self.registerID] = publish

    def subscribeTo(self, topicName, qosValue):
        qos = Qos.qos(qosValue)
        topic = FullTopic.fullTopic(topicName, qos)
        subscribe = SNSubscribe.snSubscribe(0, topic, False)
        self.timers.goMessageTimer(subscribe)

    def unsubscribeFrom(self, topicName):
        qos = Qos.qos(0)
        topic = FullTopic.fullTopic(topicName, qos)
        unsubscribe = SNUnsubscribe.snUnsubscribe(0,topic)
        self.timers.goMessageTimer(unsubscribe)

    def pingreq(self):
        self.send(SNPingreq.snPingreq(self.account.clientID))

    def disconnectWith(self, duration):
        if duration is not None and duration > 0:
            self.send(SNDisconnect(duration))
        else:
            self.send(SNDisconnect(0))
        self.timers.stopAllTimers()

    def timeoutMethod(self):
        self.timers.stopAllTimers()
        print('Timeout... all timers are stopped')

    def ConnectionLost(self):
        if self.isClean == True:
            self.clearAccountTopics()
        if self.timers != None:
            self.timers.stopAllTimers()
        if self.client != None:
            self.client.stop()
            self.setState(7) #CONNECTION_LOST

    def connected(self):
        self.setState(5) #CONNECTION_ESTABLISHED

    def connectFailed(self):
        self.setState(3) #CHANNEL_FAILED

    def isConnected(self):
        return self.connectionState == 5 #CONNECTION_ESTABLISHED

#__________________________________________________________________________________________
def processADVERTISE(self,message):
    print('Packet Advertise did receive')

def processSEARCHGW(self,message):
    print('Packet Search did receive')

def processGWINFO(self,message):
    print('Packet GWInfo did receive')

def processCONNECT(self,message):
    print('Packet Connect did receive')

def processCONNACK(self,message):
    self.setState(5) #CONNECTION_ESTABLISHED
    self.timers.stopConnectTimer()
    self.timers.goPingTimer(SNPingreq.snPingreq(self.account.clientID), self.account.keepAlive)
    print('Connack received code= ' + str(message.getCode()))

def processWILL_TOPIC_REQ(self,message):
    qos = Qos.qos(self.account.qos)
    topic = FullTopic.fullTopic(self.account.willTopic, qos)
    retain = self.account.retain
    willTopic = WillTopic.willTopic(retain, topic)
    self.send(willTopic)

def processPINGRESP(self,message):
    print('Ping resp was received')

def processWILL_TOPIC(self,message):
    print('Packet Will topic did receive')

def processWILL_MSG_REQ(self,message):
    willMessage = WillMsg.willMsg(self.account.will)
    self.send(willMessage)

def processWILL_MSG(self,message):
    print('Packet Will msg did receive')

def processREGISTER(self,message):
    if message.getType == self.snMessageType.getValueByKey('SN_REGISTER'):
        regack = Regack.regack(message.getTopicID(), message.getPacketID(), self.returnCode.getValueByKey('ACCEPTED'))
        self.send(regack)

def processREGACK(self,message):
    self.timers.stopTimer(self.registerID) #stop registerTimer
    if message.getType == self.snMessageType.getValueByKey('SN_REGACK'):
        if message.getCode() == self.returnCode.getValueByKey('ACCEPTED'):
            publish = self.forPublish[message.getPacketID()]
            if publish is not None:
                self.topics[message.getTopicID()] = publish.getTopic().getValue()
                topic = IdentifierTopic(message.getTopicID(),publish.getTopic().getQoS())
                publish.setPacketID(message.getPacketID())
                publish.setTopic(topic)
                if publish.getTopic().getQoS().getValue() ==  self.qosType.getValueByKey('AT_MOST_ONCE'):
                    self.send(publish)
                else:
                    self.timers.goMessageTimer(publish)

def processPUBLISH(self,message):
    if message.getType == self.snMessageType.getValueByKey('SN_PUBLISH'):
        if message.getTopic().getQoS() == self.qosType.getValueByKey('AT_LEAST_ONCE'):
            topicID = int(message.getTopic().getValue())
            puback = SNPuback.snPuback(topicID, message.getPacketID(), self.returnCode.getValueByKey('ACCEPTED'))
            self.send(puback)
        elif message.getTopic().getQoS() == self.qosType.getValueByKey('EXACTLY_ONCE'):
            pubrec = SNPubrec.snPubrec(message.getPacketID())
            self.publishPackets[message.getPacketID()] = message
            self.timers.goMessageTimer(pubrec)
    topic = message.getTopic()
    qos = Qos.qos(topic.getQoS())
    topicName = self.topics[int(topic.getValue())]
    topicResult = FullTopic.fullTopic(topicName, qos)
    print('Publish received')

def processPUBACK(self, message):
    publish = self.timers.removeTimer(message.getPacketID())
    if publish is not None and message.getType == self.snMessageType.getValueByKey('SN_PUBLISH'):
        topic = publish.getTopic()
        qos = topic.getQoS()
        topicName = self.topics[int(topic.getValue())]
        topicResult = FullTopic.fullTopic(topicName, qos)
        print('Puback received')
        self.publishPackets[publish.getPacketID()] = None

def processPUBCOMP(self, message):
    pubcomp = self.timers.removeTimer(message.getPacketID())
    if pubcomp is not None and message.getType == self.snMessageType.getValueByKey('SN_PUBCOMP'):
        publish = self.publishPackets.get(message.getPacketID())
        if publish is not None and message.getType == self.snMessageType.getValueByKey('SN_PUBLISH'):
            topic = publish.getTopic()
            qos = Qos.qos(topic.getQoS())
            topicName = self.topics[int(topic.getValue())]
            topicResult = FullTopic.fullTopic(topicName, qos)
            print('Puback received')
            self.publishPackets[pubcomp.getPacketID()] = None

def processPUBREC(self, message):
    if message.getType == self.snMessageType.getValueByKey('SN_PUBREC'):
        publish = self.timers.removeTimer(message.getPacketID())
        if publish is not None:
            self.publishPackets[message.getPacketID()] = publish
            pubrel = SNPubrel.snPubrel(message.getPacketID())
            self.timers.goMessageTimer(pubrel)

def processPUBREL(self, message):
    if message.getType == self.snMessageType.getValueByKey('SN_PUBREL'):
        self.timers.removeTimer(message.getPacketID())
        publish = self.publishPackets[message.getPacketID()]
        if publish is not None and message.getType == self.snMessageType.getValueByKey('SN_PUBLISH'):
            pubComp = SNPubcomp.snPubcomp(message.getPacketID())
            self.send(pubComp)
            topic = publish.getTopic()
            qos = Qos.qos(topic.getQoS())
            topicName = self.topics[int(topic.getValue())]
            topicResult = FullTopic.fullTopic(topicName, qos)
            print('Puback Received')

def processSUBSCRIBE(self, message):
    print('Packet Subscribe did receive')

def processSUBACK(self, message):
    if message.getType == self.snMessageType.getValueByKey('SN_SUBACK'):
        subscribe = self.timers.removeTimer(message.getPacketID())
        if subscribe is not None and message.getType == self.snMessageType.getValueByKey('SN_SUBSCRIBE'):
            self.topics[message.getPacketID()] = subscribe.getTopic().getValue()
            print('Suback Received')

def processUNSUBSCRIBE(self, message):
    print('Packet Unsubscribe did receive')

def processUNSUBACK(self, message):
    if message.getType == self.snMessageType.getValueByKey('SN_UNSUBACK'):
        unsubscribe = self.timers.removeTimer(message.getPacketID())
        if unsubscribe is not None and message.getType == self.snMessageType.getValueByKey('SN_UNSUBSCRIBE'):
            list = []
            list.append(unsubscribe.getTopic().getValue())
            print('Unsuback received')

def processPINGREQ(self, message):
    print('Packet Pingreq did receive')

def processDISCONNECT(self, message):
    self.timers.stopAllTimers()
    print('Disconnect received')

def processWILL_TOPIC_UPD(self, message):
    print('Packet Will topic upd did receive')

def processWILL_TOPIC_RESP(self, message):
    print('Packet Will topic resp did receive')

def processWILL_MSG_UPD(self, message):
    print('Packet Will msg upd did receive')

def processWILL_MSG_RESP(self, message):
    print('Packet Will msg resp did receive')

def processENCAPSULATED(self, message):
    print('Packet Encapsulated did receive')

switcherProcess = {
    0: processADVERTISE,
    1: processSEARCHGW,
    2: processGWINFO,
    4: processCONNECT,
    5: processCONNACK,
    6: processWILL_TOPIC_REQ,
    7: processWILL_TOPIC,
    8: processWILL_MSG_REQ,
    9: processWILL_MSG,
    10: processREGISTER,
    11: processREGACK,
    12: processPUBLISH,
    13: processPUBACK,
    14: processPUBCOMP,
    15: processPUBREC,
    16: processPUBREL,
    18: processSUBSCRIBE,
    19: processSUBACK,
    20: processUNSUBSCRIBE,
    21: processUNSUBACK,
    22: processPINGREQ,
    23: processPINGRESP,
    24: processDISCONNECT,
    26: processWILL_TOPIC_UPD,
    27: processWILL_TOPIC_RESP,
    28: processWILL_MSG_UPD,
    29: processWILL_MSG_RESP,
    254: processENCAPSULATED
}

def process_messageType_method(self, argument, message):
    return switcherProcess[argument].__call__(self, message)
