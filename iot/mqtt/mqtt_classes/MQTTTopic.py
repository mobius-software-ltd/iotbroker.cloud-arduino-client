class mqttTopic():
    def __init__(self, name, qos):
        self.name = name
        self.qos = qos

    def getType(self):
        return 'MQTT_TOPIC_TYPE'

    def getQoS(self):
        return self.qos

    def encode(self):
        return self.name

    def getLength(self):
        return len(self.name)

    def getName(self):
        return self.name