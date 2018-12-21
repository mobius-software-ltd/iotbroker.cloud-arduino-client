import iot.mqttsn.sn_classes.TopicType as TopicType

class ShortTopic():
    def __init__(self, value, qos):
        self.value = value
        self.qos = qos
        self.topicTypeEnum = TopicType.topicType()

    def getType(self):
        return self.topicTypeEnum.getValueByKey('SHORT')

    def getLength(self):
        return 2

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
