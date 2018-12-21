import iot.mqttsn.sn_classes.SNmessageType as SNmessageType

class regack():
    def __init__(self, topicID, packetID, code):
        self.topicID = topicID
        self.packetID = packetID
        self.code = code
        self.snMessageType = SNmessageType.snMessageType()

    def getLength(self):
        return 7

    def getType(self):
        return self.snMessageType.getValueByKey('SN_REGACK')

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
