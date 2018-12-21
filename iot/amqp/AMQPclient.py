import iot.amqp.header.impl.AMQPProtoHeader as AMQPProtoHeader
import iot.amqp.header.impl.AMQPPing as AMQPPing
import iot.amqp.header.impl.AMQPOpen as AMQPOpen
import iot.amqp.header.impl.SASLInit as SASLInit
import iot.amqp.header.impl.AMQPBegin as AMQPBegin
import iot.amqp.header.impl.AMQPEnd as AMQPEnd
import iot.amqp.header.impl.AMQPClose as AMQPClose
import iot.amqp.header.impl.AMQPTransfer as AMQPTransfer
import iot.amqp.header.impl.AMQPAttach as AMQPAttach
import iot.amqp.header.impl.AMQPDisposition as AMQPDisposition
import iot.amqp.header.impl.AMQPDetach as AMQPDetach
import iot.amqp.sections.AMQPData as AMQPData
import iot.amqp.terminus.AMQPSource as AMQPSource
import iot.amqp.terminus.AMQPTarget as AMQPTarget
import iot.amqp.wrappers.AMQPMessageFormat as AMQPMessageFormat
import iot.amqp.avps.OutcomeCode as OutcomeCode
import iot.amqp.numeric.NumericUtil as NumericUtil
import iot.classes.ConnectionState as ConnectionState
import iot.mqtt.mqtt_classes.MQTTTopic as MQTTTopic
import iot.network.TcpClient as TcpClient
import iot.amqp.AMQPParser as AMQPParser
import iot.timers.TimersMap as TimersMap
import iot.amqp.avps.SectionCode as SectionCode
import iot.amqp.avps.SendCode as SendCode
import iot.amqp.avps.RoleCode as RoleCode
import iot.amqp.avps.ReceiveCode as ReceiveCode
import iot.amqp.avps.TerminusDurability as TerminusDurability
import iot.amqp.numeric.Long as Long
import iot.amqp.numeric.Int as Int
import iot.classes.Qos as Qos
import iot.amqp.tlv.impl.AMQPAccepted as AMQPAccepted

class amqpClient():
    def __init__(self, account):
        self.account = account
        self.parser = AMQPParser.amqpParser()
        self.nextHandle = 1
        self.connectionState = None
        self.channel = 0
        self.isSASLConfirm = False
        self.timers = TimersMap.timersMap(self)
        self.usedIncomingMappings = {}
        self.usedOutgoingMappings = {}
        self.usedMappings = {}
        self.pendingMessages = []
        self.timeout = 0

    def send(self, header):
        connectionState = ConnectionState.connectionState()
        if self.connectionState == connectionState.getValueByKey('CONNECTION_ESTABLISHED'):
            message = self.parser.encode(header)
            self.TcpClient.sendMessage(message)
        else:
            return False

    def dataReceived(self, data):
        part = ''
        received = bytearray()
        while len(received)<len(data):
            index = 0
            part = self.parser.next(data,index)
            index += len(part)
            received += part
            data = data[index:]
            message = self.parser.decode(part)
            process_messageType_method(self, message.getCode().value, message)

    def goConnect(self):
        connectionState = ConnectionState.connectionState()
        self.setState(connectionState.getValueByKey('CONNECTING'))
        header = AMQPProtoHeader.amqpProtoHeader(3)  # SASL = 3
        self.TcpClient = TcpClient.tcpClient(self.account.serverHost, self.account.port, self)
        if self.account.isSecure:
            self.TcpClient.connectSecure(self.account.cert_path, self.account.key_path)
        else:
            self.TcpClient.connect()
        self.setState(connectionState.getValueByKey('CONNECTION_ESTABLISHED'))
        self.send(header)

    def publish(self, name, qos, content, retain, dup):
        topic = MQTTTopic.mqttTopic(name, qos)
        messageFormat = AMQPMessageFormat.amqpMessageFormat(0,None,None)
        transfer = AMQPTransfer.amqpTransfer(None,None,None,self.channel,None,None,None,messageFormat,True,False,None,None,None,None,None,None)
        data = AMQPData.amqpData(bytes(content, encoding='utf_8'))
        sections = {}
        sectionCode = SectionCode.sectionCode()
        sections[sectionCode.getValueByKey('DATA')]= data
        transfer.setSections(sections)
        if name in self.usedOutgoingMappings:
            handle = self.usedOutgoingMappings[name]
            handle_numeric = Long.long(handle)
            transfer.setHandle(handle_numeric)
            self.timers.goMessageTimer(transfer)
            if transfer.getSettled() is not None:
                settled = transfer.getSettled()
                if settled:
                    if transfer.getDeliveryId() is not None:
                        self.timers.removeTimer(transfer.getDeliveryId())
        else:
            currentHandler = self.nextHandle
            self.nextHandle += 1
            self.usedOutgoingMappings[name] = currentHandler
            self.usedMappings[currentHandler] = name
            currentHandler_numeric = Long.long(currentHandler)
            transfer.setHandle(currentHandler_numeric)
            self.pendingMessages.append(transfer)
            receiveCode = ReceiveCode.receiveCode()
            terminusDurability = TerminusDurability.terminusDurability()
            attach = AMQPAttach.amqpAttach(None,None,None,self.channel,str(name),currentHandler_numeric,RoleCode.roleCode.getValueByKey('SENDER'),None,Int.int(receiveCode.getValueByKey('FIRST')),None,None,None,None,Long.long(0),None,None,None,None)
            source = AMQPSource.amqpSource(str(name),Long.long(terminusDurability.getValueByKey('NONE')),None,Long.long(0),False,None,None,None,None,None,None)
            attach.setSource(source)
            self.send(attach)

    def subscribeTo(self, name, qos):
        topic = MQTTTopic.mqttTopic(name, qos)
        if name in self.usedIncomingMappings:
            currentHandler = self.usedIncomingMappings[name]
        else:
            currentHandler = self.nextHandle
            self.nextHandle += 1
            self.usedIncomingMappings[name] = currentHandler
            self.usedMappings[currentHandler] = name
        sendCode = SendCode.sendCode()
        roleCode = RoleCode.roleCode()
        terminusDurability = TerminusDurability.terminusDurability()
        attach = AMQPAttach.amqpAttach(None,None,None,self.channel,str(name),Long.long(currentHandler),roleCode.getValueByKey('RECEIVER'),Int.int(sendCode.getValueByKey('MIXED')),None,None,None,None,None,None,None,None,None,None)
        target = AMQPTarget.amqpTarget(str(name),Long.long(terminusDurability.getValueByKey('NONE')),None,Long.long(0),False,None,None)
        attach.setTarget(target)
        self.send(attach)

    def unsubscribeFrom(self, topicName):
        if topicName in self.usedIncomingMappings:
            detach = AMQPDetach.amqpDetach(None,None,None,self.channel,Long.long(self.usedIncomingMappings[topicName]),True,None)
            self.send(detach)
        else:
            listTopics = []
            listTopics.append(topicName)
            print('Unsuback received topics=' + str(listTopics))

    def pingreq(self):
        ping = AMQPPing.amqpPing()
        self.send(ping)

    def disconnectWith(self, duration):
        self.timers.stopAllTimers()
        end = AMQPEnd.amqpEnd(None,None,None,self.channel,None)
        self.send(end)

    def getPingreqMessage(self):
        return AMQPPing.amqpPing()

    def timeoutMethod(self):
        self.timers.stopAllTimers()
        print('Timeout... all timers are stopped')

    def setTopics(self, topics):
        pass

    def setState(self, connectionState):
        self.connectionState = connectionState
        
    def isConnected(self):
        return self.connectionState == self.connectionState.getValueByKey('CONNECTION_ESTABLISHED')

#__________________________________________________________________________________________

def processProto(self,message):
    if self.isSASLConfirm and message.getProtocolId() == 0:
        open  = AMQPOpen.amqpOpen(None,None,None,message.getChannel(),self.account.clientID,self.account.serverHost,None,None,Long.long(50*1000),None,None,None,None,None)
        self.send(open)

def processMechanisms(self,message):
    plainMech = None
    mechanisms = message.getMechanisms()
    for mechanism in mechanisms:
        if mechanism.getValue() == 'PLAIN':
            plainMech = mechanism
            plainMech.setValue(mechanism.getValue())
            break
    if plainMech is None:
        self.timers.stopAllTimers()
        return
    challenge = bytearray()
    challenge = NumericUtil.util.addString(challenge,self.account.username)
    challenge = NumericUtil.util.addByte(challenge, 0)
    challenge = NumericUtil.util.addString(challenge, self.account.username)
    challenge = NumericUtil.util.addByte(challenge, 0)
    challenge = NumericUtil.util.addString(challenge, self.account.password)

    init = SASLInit.saslInit(None,None,message.getType(),message.getChannel(),plainMech,challenge,None)
    self.send(init)

def processOutcome(self,message):
    outcomeCode = OutcomeCode.outcomeCode()
    if message.getOutcomeCode() == outcomeCode.getValueByKey('OK'):
        self.isSASLConfirm = True
        header = AMQPProtoHeader.amqpProtoHeader(0)
        self.send(header)
    elif message.getOutcomeCode() == outcomeCode.getValueByKey('AUTH'):
        print('Connection authentication failed')
        print('Due to an unspecified problem with the supplied')
    elif message.getOutcomeCode() == outcomeCode.getValueByKey('SYS'):
        print('Connection authentication failed')
        print('Due to a system error')
    elif message.getOutcomeCode() == outcomeCode.getValueByKey('SYS_PERM'):
        print('Connection authentication failed')
        print('Due to a system error that is unlikely to be cor- rected without intervention')
    elif message.getOutcomeCode() == outcomeCode.getValueByKey('SYS_TEMP'):
        print('Connection authentication failed')
        print('Due to a transient system error')

def processOpen(self,message):
    print('Connack received...')
    self.timeout = message.getIdleTimeout()
    begin = AMQPBegin.amqpBegin(None, None, None, self.channel, None, Long.long(0), Long.long(2147483647), Long.long(0), None, None, None, None)
    self.send(begin)

def processBegin(self,message):
    ping = AMQPPing.amqpPing()
    if self.timeout is None:
        self.timers.goPingTimer(ping, 50)
    else:
        self.timers.goPingTimer(ping, self.timeout / 1000)

def processEnd(self,message):
    close = AMQPClose.amqpClose(None,None,None,self.channel,None)
    self.send(close)

def processClose(self,message):
    self.timers.stopAllTimers()
    self.isSASLConfirm = False
    connectionState = ConnectionState.connectionState()
    self.connectionState == connectionState.getValueByKey('CONNECTION_LOST')

def processAttach(self,message):
    roleCode = RoleCode.roleCode()
    if message.getRole() == roleCode.getValueByKey('RECEIVER'):
        for pending in self.pendingMessages:
            h1 = pending.getHandle()
            h2 = message.getHandle()
            if h1 == h2:
                self.pendingMessages.remove(pending)
                self.timers.goMessageTimer(pending)
                if pending.getSettled() is not None:
                    settled = pending.getSettled()
                    if settled:
                        if pending.getDeliveryId() is not None:
                            id = pending.getDeliveryId()
                            self.timers.removeTimer(id)
    else:
        handle = message.getHandle()
        self.usedIncomingMappings[message.getName()] = handle
        self.usedMappings[handle] = message.getName()
        topic = MQTTTopic.mqttTopic(message.getName(),1)
        qos = topic.getQoS()
        print('Suback received topic='+ str(topic) + ', QoS='+str(qos))

def processTransfer(self,message):
    data = message.getData()
    qos = Qos.qos(1)
    roleCode = RoleCode.roleCode()
    if message.getSettled() is not None and message.getSettled():
        qos = Qos.qos(0)
    else:
        state = AMQPAccepted.amqpAccepted()
        disposition = AMQPDisposition.amqpDisposition(None,None,None,self.channel,roleCode.getValueByKey('RECEIVER'),Long.long(message.getDeliveryId()),Long.long(message.getDeliveryId()),True,state,None)
        self.send(disposition)
    handle = message.getHandle()
    if handle is not None and (handle in self.usedMappings):
        topic = self.usedMappings[handle]
        print('Publish received topic=' + str(topic)+' QoS=' + str(qos) + ' content=' + str(data.getData()))

def processDetach(self,message):
    handle = message.getHandle()
    if handle in self.usedMappings:
        topicName = self.usedMappings[handle]
        self.usedMappings.pop(handle)
        if topicName in self.usedOutgoingMappings:
            self.usedOutgoingMappings.pop(topicName)
        listTopics = []
        listTopics.append(topicName)
        print('Unsuback received topics=' + str(listTopics))

def processDisposition(self, message):
    if message.getFirst() is not None:
        first = message.getFirst()
        if message.getLast() is not None:
            last = message.getLast()
            for i in range(first,last-1):
                transfer = self.timers.removeTimer(i)
                if transfer is not None:
                    handle = transfer.getHandle()
                    topic = self.usedMappings[handle]
                    print('Publish received topic=' + str(topic)+' QoS=' + str(1) + ' content=' + str(transfer.getData()))
        else:
            transfer = self.timers.removeTimer(first)
            if transfer is not None:
                handle = transfer.getHandle()
                topic = self.usedMappings[handle]
                qos = Qos.qos(1)
                print('Publish received topic=' + str(topic)+' QoS=' + str(qos) + ' content=' + str(transfer.getData().getData()))

def processFlow(self, message):
    pass

def processInit(self, message):
    print("received invalid message init")

def processChallenge(self, message):
    print("received invalid message challenge")

def processResponse(self, message):
    print("received invalid message response")

def processPing(self, message):
    pass

switcherProcess = {
    16: processOpen,
    17: processBegin,
    18: processAttach,
    19: processFlow,
    20: processTransfer,
    21: processDisposition,
    22: processDetach,
    23: processEnd,
    24: processClose,
    64: processMechanisms,
    65: processInit,
    66: processChallenge,
    67: processResponse,
    68: processOutcome,
    254: processProto,
    255: processPing,
}

def process_messageType_method(self, argument, message):
    return switcherProcess[argument].__call__(self, message)



