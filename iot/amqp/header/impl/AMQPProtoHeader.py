import iot.amqp.avps.HeaderCode as HeaderCode
import iot.amqp.numeric.NumericUtil as NumericUtil

class amqpProtoHeader():
    def __init__(self,protocolId):
        self.headerCode = HeaderCode.headerCode()
        self.protocol = 'AMQP'
        self.code = self.headerCode.getValueByKey('PROTO')
        self.doff = 2
        self.type = 0
        self.channel = 0
        self.protocolId = protocolId
        self.versionMajor = 1
        self.versionMinor = 0
        self.versionRevision = 0

    def getBytes(self):
        data = bytearray()
        data = NumericUtil.util.addString(data,self.protocol)
        data = NumericUtil.util.addByte(self.protocolId)
        data = NumericUtil.util.addByte(self.versionMajor)
        data = NumericUtil.util.addByte(self.versionMinor)
        data = NumericUtil.util.addByte(self.versionRevision)
        return data
    
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
        return "AMQPProtoHeader [protocol=" + str(self.protocol) + ", protocolId=" + str(self.protocolId) + ", versionMajor=" + str(self.versionMajor) + ", versionMinor=" + str(self.versionMinor) + ", versionRevision=" + str(self.versionRevision) + "]"

    def getProtocol(self):
        return self.protocol

    def getProtocolId(self):
        return self.protocolId

    def getVersionMajor(self):
        return self.versionMajor

    def getVersionMinor(self):
        return self.versionMinor

    def getVersionRevision(self):
        return self.versionRevision
        
    def toStringShort(self):
        return 'AMQPProtoHeader'
