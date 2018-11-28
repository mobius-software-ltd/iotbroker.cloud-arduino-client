import iot.mqttsn.sn_classes.SNmessageType as SNmessageType

class snSuback():
    def __init__(self, topicID, code, qos, packetID):
        self.topicID = topicID
        self.code = code
        self.qos = qos
        self.packetID = packetID

    def getLength(self):
        return 8

    def getType(self):
        return SNmessageType.snMessageType.getValueByKey('SN_SUBACK')

    def getTopicID(self):
        return self.topicID

    def setTopicID(self, topicID):
        self.topicID = topicID

    def getCode(self):
        return self.code

    def setCode(self, code):
        self.code = code

    def getQoS(self):
        return self.qos

    def setQoS(self, qos):
        self.qos = qos

    def getPacketID(self):
        return self.packetID

    def setPacketID(self, packetID):
        self.packetID = packetID