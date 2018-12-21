import iot.amqp.avps.HeaderCode as HeaderCode

class amqpPing():
    def __init__(self):
        self.headerCode = HeaderCode.headerCode()
        self.code = self.headerCode.getValueByKey('PING')
        self.doff = 2
        self.type = 0
        self.channel = 0
    
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
    
    def toArgumentsList(self):
        return None

    def fromArgumentsList(self, list):
        pass

    def toString(self):
        return "AMQPPing"
