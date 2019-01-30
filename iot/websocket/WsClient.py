import iot.classes.Qos as Qos
import iot.mqtt.mqtt_classes.MQTTTopic as MQTTTopic
import iot.network.WebSocketsClient as WebSocketsClient
import iot.timers.TimersMap as TimersMap
import iot.network.wsUtil.OpCode as OpCode
import iot.network.wsUtil.WsMessage as WsMessage
import iot.network.wsUtil.WsParser as WsParser
import base64

class wsClient():
    def __init__(self, account):
        self.account = account
        self.resendperiod = 3000
        self.data = None
        self.timers = TimersMap.timersMap(self)
        self.publishPackets = {}
        self.connectionState = 0
        self.opCode = OpCode.opCode()

    def send(self, message):
        if self.connectionState == 5: #CONNECTION_ESTABLISHED
            data = WsParser.wsParser.encode(message)
            self.wsClient.sendMessage(data)
        else:
            return False

    def dataReceived(self, message):
        process_messageType_method(self, message['packet'], message)

    def setState(self, connectionState):
        self.connectionState = connectionState

    def goConnect(self):
        self.setState(4) #CONNECTING
        if self.account.willTopic and len(self.account.willTopic)>0 is not None:
            will = {"topic": {"name": self.account.willTopic, "qos": self.account.qos},
                    "content": base64.standard_b64encode(self.account.will.encode()).decode("utf-8"),
                    "retain": self.account.retain}
            willFlag = True
        else:
            will = None
            willFlag = False

        self.wsClient = WebSocketsClient.wsTransport(self.account.host, self.account.port, self)
        if self.account.enable:
            self.wsClient.connectSecure(self.account.cert_path, self.account.key_path)
        else:
            self.wsClient.connect()

        if self.account.username is not None and len(self.account.username)>0:
            usernameFlag = True
        else:
            usernameFlag = False

        if self.account.password is not None and len(self.account.password)>0:
            passwordFlag = True
        else:
            passwordFlag = False

        connect = {"packet": 1, "protocolLevel": 4, "username": self.account.username, "password": self.account.password,
             "clientID": self.account.clientID, "cleanSession": self.account.isClean, "keepalive": self.account.keepAlive, "will": will, "willFlag": willFlag,
             "passwordFlag": passwordFlag, "usernameFlag": usernameFlag, "protocolName": "MQTT"}

        if self.timers is not None:
            self.timers.stopAllTimers()

        message = WsMessage.wsMessage(True, self.opCode.getValueByKey('TEXT'), True, connect)
        self.timers.goConnectTimer(message)

    def publish(self, name, qos, content, retain, dup):
        publish = {
            "packet": 3,
            "packetID": None,
            "topic": {
                "name": name,
                "qos": qos
            },
            "content": base64.standard_b64encode(content.encode()).decode("utf-8"),
            "retain": retain,
            "dup": dup
        }

        message = WsMessage.wsMessage(True, self.opCode.getValueByKey('TEXT'), True, publish)
        if (qos == 0):
            self.send(message)
        else:
            if (qos in [1, 2]):
                self.timers.goMessageTimer(message)

    def unsubscribeFrom(self, topicName):
        listTopics = []
        listTopics.append(topicName)
        unsubscribe = {
            "packet": 10,
            "packetID": None,
            "topics": [
                topicName
            ],
        }
        message = WsMessage.wsMessage(True, self.opCode.getValueByKey('TEXT'), True, unsubscribe)
        self.timers.goMessageTimer(message)

    def subscribeTo(self, name, qos):
        topic = MQTTTopic.mqttTopic(name, qos)
        listMQTopics = [topic]
        subscribe = {
            "packet": 8,
            "packetID": None,
            "topics": [
                {
                    "name": name,
                    "qos": qos
                }
            ]
        }
        message = WsMessage.wsMessage(True, self.opCode.getValueByKey('TEXT'), True, subscribe)
        self.timers.goMessageTimer(message)

    def pingreq(self):
        ping = {"packet": 12}
        message = WsMessage.wsMessage(True, self.opCode.getValueByKey('TEXT'), True, ping)
        self.send(message)

    def disconnectWith(self, duration):
        disconnect = {"packet": 14}
        message = WsMessage.wsMessage(True, self.opCode.getValueByKey('TEXT'), True, disconnect)
        self.send(message)
        self.timers.stopAllTimers()

    def timeoutMethod(self):
        self.timers.stopAllTimers()
        print('Timeout... all timers are stopped')

    def PacketReceived(self,ProtocolMessage):
        ProtocolMessage.processBy()

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

def processConnack(self,message):
    self.timers.stopConnectTimer()
    ping = {"packet":12}
    message = WsMessage.wsMessage(True, self.opCode.getValueByKey('TEXT'), True, ping)
    self.timers.goPingTimer(message, self.account.keepAlive)

    if message['returnCode'] == 0: #MQ_ACCEPTED
        self.setState(5) #CONNECTION_ESTABLISHED
        print('Connack received...')

def processSuback(self,message):
    subscribe = self.timers.removeTimer(message['packetID'])
    if subscribe is not None:
        name = subscribe['topics'][0]['name']
        qos = Qos.qos(subscribe['topics'][0]['qos'])
        topic = MQTTTopic.mqttTopic(name, qos)
        print('Suback received topic='+ str(topic) + ', QoS='+str(qos))

def processUnsuback(self,message):
    unsubscribe = self.timers.removeTimer(message['packetID'])
    if unsubscribe is not None:
      print('Unsuback received topics=' + str(unsubscribe.listTopics))

def processPublish(self,message):
    publisherQoS = message['topic']['qos']

    name = message['topic']['name']
    qos = Qos.qos(message['topic']['qos'])
    topic = MQTTTopic.mqttTopic(name, qos)

    if publisherQoS == 0:
        print('Publish received topic=' + str(message.topic)+' QoS=' + str(publisherQoS) + ' content=' + str(message.content))
    if publisherQoS == 1:  #AT_LEAST_ONCE
        puback = {"packet": 4,"packetID": message['packetID']}
        message = WsMessage.wsMessage(True, self.opCode.getValueByKey('TEXT'), True, puback)
        self.send(message)
        print('Publish received topic=' + str(message.topic)+' QoS=' + str(publisherQoS) + ' content=' + str(message.content))
    if publisherQoS == 2:  #EXACTLY_ONCE
        pubrec = {"packet": 5, "packetID": message['packetID']}
        message = WsMessage.wsMessage(True, self.opCode.getValueByKey('TEXT'), True, pubrec)
        self.send(message)
        self.publishPackets[message['packetID']] = message

def processPuback(self,message):
    publish = self.timers.removeTimer(message['packetID'])
    if publish is not None:
        name = publish['topic']['name']
        qos = Qos.qos(publish['topic']['qos'])
        topic = MQTTTopic.mqttTopic(name, qos)
        print('Puback received topic=' + str(publish.topic)+' QoS=' + str(publish.topic.getQoS()) + ' content=' + str(publish.content))

def processPubrec(self, message):
    publish = self.timers.removeTimer(message['packetID'])
    if publish is not None:
        pubrel = {"packet": 6, "packetID": message['packetID']}
        self.timers.goMessageTimer(pubrel)
        self.publishPackets[publish['packetID']] = publish

def processPubrel(self,message):
    pubrec = self.timers.removeTimer(message['packetID'])
    if pubrec is not None:
        publish = self.publishPackets.get(message['packetID'])
        name = publish['topic']['name']
        qos = Qos.qos(publish['topic']['qos'])
        topic = MQTTTopic.mqttTopic(name, qos)
        print('Pubrel publish received topic=' + str(publish.topic)+' QoS=' + str(publish.topic.getQoS()) + ' content=' + str(publish.content))
        pubcomp = {"packet": 7, "packetID": message['packetID']}
        message = WsMessage.wsMessage(True, self.opCode.getValueByKey('TEXT'), True, pubcomp)
        self.send(message)

def processPubcomp(self,message):
    pubrel = self.timers.removeTimer(message['packetID'])
    if pubrel is not None:
        publish = self.publishPackets.get(message['packetID'])
        name = publish['topic']['name']
        qos = Qos.qos(publish['topic']['qos'])
        topic = MQTTTopic.mqttTopic(name, qos)
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
