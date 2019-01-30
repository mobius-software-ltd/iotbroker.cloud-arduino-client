import iot.mqtt.mqtt_messages.MQTTConnect as MQTTConnect
import iot.mqtt.mqtt_messages.MQTTDisconnect as MQTTDisconnect
import iot.mqtt.mqtt_messages.MQTTPingreq as MQTTPingreq
import iot.mqtt.mqtt_messages.MQTTPuback as MQTTPuback
import iot.mqtt.mqtt_messages.MQTTPubcomp as MQTTPubcomp
import iot.mqtt.mqtt_messages.MQTTPublish as MQTTPublish
import iot.mqtt.mqtt_messages.MQTTPubrec as MQTTPubrec
import iot.mqtt.mqtt_messages.MQTTPubrel as MQTTPubrel
import iot.mqtt.mqtt_messages.MQTTSubscribe as MQTTSubscribe
import iot.mqtt.mqtt_messages.MQTTUnsubscribe as MQTTUnsubscribe
import iot.mqtt.mqtt_classes.MQTTTopic as MQTTTopic
import iot.mqtt.mqtt_classes.Will as Will
import iot.mqtt.MQTTParser as MQTTParser
import iot.timers.TimersMap as TimersMap
import iot.network.TcpClient as TcpClient

class mqttClient():
    def __init__(self, account):
        self.account = account
        self.parser = MQTTParser.mqttParser(None)
        self.resendperiod = 3000
        self.data = None
        self.timers = TimersMap.timersMap(self)
        self.publishPackets = {}
        self.connectionState = 0

    def send(self, message):
        if self.connectionState == 5: #CONNECTION_ESTABLISHED
            self.parser.setMessage(message)
            message = self.parser.encode()
            self.TcpClient.sendMessage(message)
        else:
            return False

    def dataReceived(self, data):
        message = self.parser.decode(data)
        process_messageType_method(self, message.getType(), message)

    def setState(self, connectionState):
        self.connectionState = connectionState

    def isConnected(self):
        return self.connectionState == 5 #CONNECTION_ESTABLISHED

    def closeChannel(self):
        if self.client != None:
            self.client.stop()

    def goConnect(self):
        self.setState(4) #CONNECTING
        if self.account.willTopic is not None:
            topic = MQTTTopic.mqttTopic(self.account.willTopic, self.account.qos)
            will = Will.will(topic, self.account.will, self.account.retain)
        else:
            will = None
        connect = MQTTConnect.mqttConnect(self.account.username, self.account.password, self.account.clientID, self.account.isClean, self.account.keepAlive, will)
        if self.timers is not None:
            self.timers.stopAllTimers()
        self.TcpClient = TcpClient.tcpClient(self.account.host, self.account.port, self)
        if self.account.enable:
            self.TcpClient.connectSecure(certificates.CA_CERT, certificates.P_KEY)
        else:
            self.TcpClient.connect()
        self.send(connect)

    def publish(self, name, qos, content, retain, dup):
        topic = MQTTTopic.mqttTopic(name, qos)
        publish = MQTTPublish.mqttPublish(0, topic, content, retain, dup)
        if(qos == 0):
            self.send(publish)
        else:
            if(qos in [1,2]):
                self.timers.goMessageTimer(publish)

    def unsubscribeFrom(self, topicName):
        listTopics = []
        listTopics.append(topicName)
        unsubscribe = MQTTUnsubscribe.mqttUnsubscribe(0,listTopics)
        self.timers.goMessageTimer(unsubscribe)

    def subscribeTo(self, name, qos):
        topic = MQTTTopic.mqttTopic(name, qos)
        listMQTopics = [topic]
        subscribe = MQTTSubscribe.mqttSubscribe(0,listMQTopics)
        self.timers.goMessageTimer(subscribe)

    def pingreq(self):
        self.send(MQTTPingreq.mqttPingreq())

    def disconnectWith(self, duration):
        self.send(MQTTDisconnect.mqttDisconnect())
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
#__________________________________________________________________________________________

def processConnack(self,message):
    self.timers.stopConnectTimer()
    self.timers.goPingTimer(MQTTPingreq.mqttPingreq(), self.account.keepAlive)
    if message.returnCode == 0: #MQ_ACCEPTED
        print('Connack received...')
    else:
        print('Disconnect received...')

def processSuback(self,message):
    subscribe = self.timers.removeTimer(message.packetID)
    if subscribe is not None:
        size = len(subscribe.listMQTopics)
        topic = subscribe.listMQTopics[size-1]
        qos = topic.getQoS()
        print('Suback received topic='+ str(topic) + ', QoS='+str(qos))

def processUnsuback(self,message):
    unsubscribe = self.timers.removeTimer(message.packetID)
    if unsubscribe is not None:
        print('Unsuback received topics=' + str(unsubscribe.listTopics))

def processPublish(self,message):
    publisherQoS = message.topic.qos.getValue()
    if publisherQoS.getValue() == 0:
        print('Publish received topic=' + str(message.topic)+' QoS=' + str(publisherQoS) + ' content=' + str(message.content))
    if publisherQoS.getValue() == 1:  #AT_LEAST_ONCE
        puback = MQTTPuback.mqttPuback(message.packetID)
        self.send(puback)
        print('Publish received topic=' + str(message.topic)+' QoS=' + str(publisherQoS) + ' content=' + str(message.content))
    if publisherQoS.getValue() == 2:  #EXACTLY_ONCE
        pubrec = MQTTPubrec.mqttPubrec(message.packetID)
        self.send(pubrec)
        self.publishPackets[message.packetID] = message

def processPuback(self,message):
    publish = self.timers.removeTimer(message.packetID)
    if publish is not None:
        print('Puback received topic=' + str(publish.topic)+' QoS=' + str(publish.topic.getQoS()) + ' content=' + str(publish.content))

def processPubrec(self, message):
    publish = self.timers.removeTimer(message.packetID)
    if publish is not None:
        self.timers.goMessageTimer(MQTTPubrel.mqttPubrel(publish.packetID))
        self.publishPackets[publish.packetID] = publish

def processPubrel(self,message):
    pubrec = self.timers.removeTimer(message.packetID)
    if pubrec is not None:
        publish = self.publishPackets.get(message.packetID)
        print('Pubrel publish received topic=' + str(publish.topic)+' QoS=' + str(publish.topic.getQoS()) + ' content=' + str(publish.content))
        self.send(MQTTPubcomp.mqttPubcomp(message.packetID))

def processPubcomp(self,message):
    pubrel = self.timers.removeTimer(message.packetID)
    if pubrel is not None:
        publish = self.publishPackets.get(message.packetID)
        print('Pubcomp puback received topic=' + str(publish.topic)+' QoS=' + str(publish.topic.getQoS()) + ' content=' + str(publish.content))

def processPingresp(self,message):
    print('Pingresp Received')

def processSubscribe(self,message):
    print('received invalid message subscribe')

def processConnect(self,message):
    print('received invalid message connect')

def processPingreq(self,message):
    print('received invalid message pingreq')

def processDisconnect(self,message):
    self.timers.stopAllTimers()
    print('Disconnect received from server')

def processUnsubscribe(self,message):
    print('received invalid message unsubscribe')

switcherProcess = {
    1: processConnect,
    2: processConnack,
    3: processPublish,
    4: processPuback,
    5: processPubrec,
    6: processPubrel,
    7: processPubcomp,
    8: processSubscribe,
    9: processSuback,
    10: processUnsubscribe,
    11: processUnsuback,
    12: processPingreq,
    13: processPingresp,
    14: processDisconnect,
}

def process_messageType_method(self, argument, message):
    return switcherProcess[argument].__call__(self, message)
