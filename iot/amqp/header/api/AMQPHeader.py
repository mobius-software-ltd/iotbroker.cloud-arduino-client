class amqpHeader():
    def __init__(self, code, doff, type, channel):
        self.code = code
        self.doff = doff
        self.type = type
        self.channel = channel

    def setDoff(self,doff):
        self.doff = doff

    def getDoff(self):
        return self.doff

    def getType(self):
        return self.type

    def setType(self, type):
        self.type = type

    def getChannel(self):
        return self.channel

    def setChannel(self, channel):
        self.channel = channel

    def getCode(self):
        return self.code