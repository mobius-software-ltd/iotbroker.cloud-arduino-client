import iot.mqttsn.sn_classes.SNmessageType as SNmessageType

class willTopicUpd():
    def __init__(self, retain, topic):
        self.retain = retain
        self.topic = topic

    def getLength(self):
        length = 2
        if self.topic is not None:
            length += self.topic.getLength() + 1
            if self.topic.getLength() > 252:
                length += 2
        return length

    def getType(self):
        return SNmessageType.snMessageType.getValueByKey('SN_WILL_TOPIC_UPD')

    def isRetain(self):
        return self.retain

    def setRetain(self, retain):
        self.retain = retain

    def getTopic(self):
        return self.topic

    def setTopic(self, topic):
        self.topic = topic