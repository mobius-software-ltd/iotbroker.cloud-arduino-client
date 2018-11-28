import iot.mqttsn.sn_classes.SNmessageType as SNmessageType

class snSubscribe():
    def __init__(self, packetID, topic, dup):
        self.packetID = packetID
        self.topic = topic
        self.dup = dup

    def getLength(self):
        length = 5
        if self.topic is not None and self.topic.getLength() > 0:
            length += self.topic.getLength()
        if self.topic.getLength() > 250:
            length += 2
        return length

    def getType(self):
        return SNmessageType.snMessageType.getValueByKey('SN_SUBSCRIBE')

    def getPacketID(self):
        return self.packetID

    def setPacketID(self, packetID):
        self.packetID = packetID

    def getTopic(self):
        return self.topic

    def setTopic(self, topic):
        self.topic = topic

    def isDup(self):
        return self.dup

    def setDup(self, dup):
        self.dup = dup