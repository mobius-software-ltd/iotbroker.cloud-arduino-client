import iot.network.UdpClient as UdpClient
import iot.coap.CoapParser as CoapParser
import iot.coap.options.CoapOptionType as CoapOptionType
import iot.coap.options.OptionParser as OptionParser
import iot.timers.TimersMap as TimersMap
import iot.coap.tlv.CoapTopic as CoapTopic
import iot.coap.tlv.CoapMessage as CoapMessage
import iot.coap.tlv.CoapType as CoapType
import iot.coap.tlv.CoapCode as CoapCode
import iot.classes.Qos as Qos

class coapClient():
    def __init__(self, account):
        self.account = account
        self.parser = CoapParser.coapParser()
        self.parserOption = OptionParser.optionParser()
        self.resendperiod = 3000
        self.data = None
        self.udpClient = None
        self.timers = TimersMap.timersMap(self)
        self.Version = 1
        self.forPublish = {}
        self.forSubscribe = {}
        self.forUnsubscribe = {}
        self.pingNum = 0
        self.connectionState = 0
        self.coapOptionType = CoapOptionType.coapOptionType()
        self.coapType = CoapType.coapType()
        self.coapCode = CoapCode.coapCode()

    def goConnect(self):
        self.setState(4) #CONNECTING

        duration = self.account.keepAlive

        if self.timers is not None:
            self.timers.stopAllTimers()

        option = self.parserOption.encode(self.coapOptionType.getValueByKey('NODE_ID'), self.account.clientID)
        options = []
        options.append(option)
        message = CoapMessage.coapMessage(self.Version,self.coapType.getValueByKey('CONFIRMABLE'),self.coapCode.getValueByKey('PUT'),0,None,options,None)
        self.udpClient = UdpClient.udpClient(self.account.host, self.account.port, self)
        if self.account.enable:
            self.udpClient.connectSecure(self.account.cert_path, self.account.key_path)
        else:
            self.udpClient.connect()
        self.timers.goPingTimer(message,duration)

    def send(self, message):
        if self.connectionState == 5: #CONNECTION_ESTABLISHED
            message = self.parser.encode(message)
            self.udpClient.sendMessage(message)
        else:
            return False

    def dataReceived(self, data):
        message = self.parser.decode(data)
        type = message.getType()
        code = message.getCode()
        if (code == self.coapCode.getValueByKey('POST') or code == self.coapCode.getValueByKey('PUT')) and type != self.coapType.getValueByKey('ACKNOWLEDGEMENT'):
            topic = None
            qosValue = None
            for option in message.getOptionsDecode():
                if CoapOptionType.coapOptionType(option.getType()) == self.coapOptionType.getValueByKey('URI_PATH'):
                    topic = self.parserOption.decode(CoapOptionType.coapOptionType(option.getType()),option)
                    break
            for option in message.getOptionsDecode():
                if CoapOptionType.coapOptionType(option.getType()) == self.coapOptionType.getValueByKey('ACCEPT'):
                    qosValue = self.parserOption.decode(CoapOptionType.coapOptionType(option.getType()),option)
                    break
            if len(topic) > 0:
                content = message.getPayload()
                qos = Qos.qos(qosValue)
                topicResult = CoapTopic.coapTopic(topic, qos)
                print('Publish received')
            else:
                textFormat = "text/plain"
                options = []
                option = self.parserOption.encode(self.coapOptionType.getValueByKey('CONTENT_FORMAT'), textFormat)
                options.append(option)
                option = self.parserOption.encode(self.coapOptionType.getValueByKey('NODE_ID'), self.account.clientID)
                options.append(option)
                ack = CoapMessage(self.Version,self.coapType.getValueByKey('ACKNOWLEDGEMENT'),self.coapCode.getValueByKey('BAD_OPTION'),message.getPacketID(),message.getToken(),options,None)
                self.send(ack)

        process_messageType_method(self, message.getType().value, message)

    def setState(self, connectionState):
        self.connectionState = connectionState

    def getConnectionState(self):
        return self.connectionState

    def publish(self, topicName, qosValue, content, retain, dup):
        options = []
        option = self.parserOption.encode(self.coapOptionType.getValueByKey('URI_PATH'), topicName)
        options.append(option)
        option = self.parserOption.encode(self.coapOptionType.getValueByKey('NODE_ID'), self.account.clientID)
        options.append(option)
        option = self.parserOption.encode(self.coapOptionType.getValueByKey('ACCEPT'), qosValue)
        options.append(option)
        message = CoapMessage(self.Version, self.coapType.getValueByKey('CONFIRMABLE'), self.coapCode.getValueByKey('PUT'), 0, '0', options, content)
        packetID = self.timers.goMessageTimer(message)
        message.setPacketID(packetID)
        self.forPublish[packetID] = message

    def subscribeTo(self,topicName, qosValue):
        options = []
        option = self.parserOption.encode(self.coapOptionType.getValueByKey('OBSERVE'), 0)
        options.append(option)
        option = self.parserOption.encode(self.coapOptionType.getValueByKey('URI_PATH'), topicName)
        options.append(option)
        option = self.parserOption.encode(self.coapOptionType.getValueByKey('ACCEPT'), qosValue)
        options.append(option)
        option = self.parserOption.encode(self.coapOptionType.getValueByKey('NODE_ID'), self.account.clientID)
        options.append(option)
        message = CoapMessage(self.Version, self.coapType.getValueByKey('CONFIRMABLE'), self.coapCode.getValueByKey('GET'), 0, '0', options, None)
        packetID = self.timers.goMessageTimer(message)
        message.setPacketID(packetID)
        self.forSubscribe[packetID] = message

    def unsubscribeFrom(self, topicName):
        options = []
        option = self.parserOption.encode(self.coapOptionType.getValueByKey('OBSERVE'), 1)
        options.append(option)
        option = self.parserOption.encode(self.coapOptionType.getValueByKey('NODE_ID'), self.account.clientID)
        options.append(option)
        option = self.parserOption.encode(self.coapOptionType.getValueByKey('URI_PATH'), topicName)
        options.append(option)
        option = self.parserOption.encode(self.coapOptionType.getValueByKey('ACCEPT'), 0)
        options.append(option)
        message = CoapMessage(self.Version, self.coapType.getValueByKey('CONFIRMABLE'), self.coapCode.getValueByKey('GET'), 0, '0', options, None)
        packetID = self.timers.goMessageTimer(message)
        message.setPacketID(packetID)
        self.forUnsubscribe[packetID] = message

    def pingreq(self):
        pass

    def disconnectWith(self,duration):
        self.timers.stopAllTimers()

    def timeoutMethod(self):
        self.timers.stopAllTimers()
        print('Timeout ...')

    def ConnectionLost(self):
        self.setState(7) #CONNECTION_LOST

    def connected(self):
        self.setState(5) #CONNECTION_ESTABLISHED

    def connectFailed(self):
        self.setState(3) #CHANNEL_FAILED

    def isConnected(self):
        return self.connectionState == 5 #CONNECTION_ESTABLISHED

#__________________________________________________________________________________________

def CONFIRMABLE(self,message):
    if isinstance(message,CoapMessage):
        options = []
        option = self.parserOption.encode(self.coapOptionType.getValueByKey('NODE_ID'), self.account.clientID)
        options.append(option)
        ack = CoapMessage.coapMessage(self.Version,self.coapType.getValueByKey('ACKNOWLEDGEMENT'),message.getCode(),message.getPacketID(),message.getToken(),options,None)
        self.send(ack)

def NONCONFIRMABLE(self,message):
    if isinstance(message, CoapMessage):
        self.timers.removeTimer(int(message.getToken()))

def ACKNOWLEDGEMENT(self,message):
    ack = None
    topic = None
    qosValue = None
    if message.getToken() is not None:
        ack = self.timers.removeTimer(int(message.getToken()))
        if message.getCode() == self.coapCode.getValueByKey('CONTENT'):
            for option in message.getOptionsDecode():
                if CoapOptionType.coapOptionType(option.getType()) == self.coapOptionType.getValueByKey('URI_PATH'):
                    topic = self.parserOption.decode(CoapOptionType(option.getType()), option)
                    break
            for option in message.getOptionsDecode():
                if CoapOptionType.coapOptionType(option.getType()) == self.coapOptionType.getValueByKey('ACCEPT'):
                    qosValue = self.parserOption.decode(CoapOptionType.coapOptionType(option.getType()), option)
                    break
            if len(topic) > 0:
                content = message.getPayload()
                qos = Qos.qos(qosValue)
                topicResult = CoapTopic.coapTopic(topic, qos)
                print('Publish received')
    if ack is not None:
        if ack.getCode() == self.coapCode.getValueByKey('GET'):
            observeValue = None
            for option in ack.getOptionsDecode():
                if CoapOptionType.coapOptionType(option.getType()) == self.coapOptionType.getValueByKey('OBSERVE'):
                    observeValue = self.parserOption.decode(CoapOptionType.coapOptionType(option.getType()), option)
                    break
            for option in ack.getOptionsDecode():
                if CoapOptionType.coapOptionType(option.getType()) == self.coapOptionType.getValueByKey('URI_PATH'):
                    topic = self.parserOption.decode(CoapOptionType.coapOptionType(option.getType()), option)
                    break
            for option in ack.getOptionsDecode():
                if CoapOptionType.coapOptionType(option.getType()) == self.coapOptionType.getValueByKey('ACCEPT'):
                    qosValue = self.parserOption.decode(CoapOptionType.coapOptionType(option.getType()), option)
                    break
            if observeValue == 0:
                qos = Qos.qos(qosValue)
                print('Suback received')
            elif observeValue == 1:
                list = []
                list.append(topic)
                print('Unsuback received')
        elif ack.getCode() == self.coapCode.getValueByKey('PUT'):
            for option in ack.getOptionsDecode():
                if CoapOptionType.coapOptionType(option.getType()) == self.coapOptionType.getValueByKey('URI_PATH'):
                    topic = self.parserOption.decode(CoapOptionType.coapOptionType(option.getType()), option)
                    break
            for option in ack.getOptionsDecode():
                if CoapOptionType.coapOptionType(option.getType()) == self.coapOptionType.getValueByKey('ACCEPT'):
                    qosValue = self.parserOption.decode(CoapOptionType.coapOptionType(option.getType()), option)
                    break
            content = ack.getPayload()
            qos = Qos.qos(qosValue)
            topicResult = CoapTopic.coapTopic(topic, qos)
            print('Puback received')
    else:
        if self.pingNum == 0:
            self.pingNum +=1

def RESET(self,message):
    if isinstance(message, CoapMessage):
        self.timers.removeTimer(int(message.getToken()))

switcherProcess = {
    0: CONFIRMABLE,
    1: NONCONFIRMABLE,
    2: ACKNOWLEDGEMENT,
    3: RESET
}

def process_messageType_method(self, argument, message):
    return switcherProcess[argument].__call__(self, message)
