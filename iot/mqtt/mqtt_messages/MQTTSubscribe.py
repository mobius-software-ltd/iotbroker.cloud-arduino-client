class mqttSubscribe():
    def __init__(self,packetID,listMQTopics):
        self.packetID = packetID
        self.listMQTopics = listMQTopics

    def getLength(self):
        length = 0
        if self.packetID is not None:
            length += 2
        for item in self.listMQTopics:
            length += len(item.name) + 3
        return length

    def getType(self):
        return 8

    def getProtocol(self):
        return 1

    def isValidCode(self, code):
        if code == 0 or code == 1 or code == 2:
            return True
        return False