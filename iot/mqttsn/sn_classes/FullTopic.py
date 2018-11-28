import iot.mqttsn.sn_classes.TopicType as TopicType

class fullTopic():
    def __init__(self, value, qos):
        self.value = value
        self.qos = qos

    def getType(self):
        return TopicType.topicType.getValueByKey('NAMED')

    def getLength(self):
        return len(self.value)

    def getQoS(self):
        return self.qos

    def setQoS(self, qos):
        self.qos = qos

    def encode(self):
        return self.value

    def getValue(self):
        return self.value

    def setValue(self, value):
        self.value = value