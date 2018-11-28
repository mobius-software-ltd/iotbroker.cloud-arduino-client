import iot.mqttsn.sn_classes.SNmessageType as SNmessageType

class snPuback():
    def __init__(self, topicID, packetID, code):
        self.topicID = topicID
        self.packetID = packetID
        self.code = code

    def getLength(self):
        return 7

    def getType(self):
        return SNmessageType.snMessageType.getValueByKey('SN_PUBACK')

    def getTopicID(self):
        return self.topicID

    def setTopicID(self, topicID):
        self.topicID = topicID

    def getPacketID(self):
        return self.packetID

    def setPacketID(self, packetID):
        self.packetID = packetID

    def getCode(self):
        return self.code

    def setCode(self, code):
        self.code = code