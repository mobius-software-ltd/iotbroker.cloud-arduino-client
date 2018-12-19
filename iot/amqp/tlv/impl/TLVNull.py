import iot.amqp.avps.AMQPType as AMQPType
import iot.amqp.constructor.SimpleConstructor as SimpleConstructor

class tlvNull():
    def __init__(self):
        self.constructor = SimpleConstructor(AMQPType.amqpType.getValueByKey('NULL'))

    def getBytes(self):
        return self.constructor.getBytes()

    def getLength(self):
        return 1

    def getValue(self):
        return None

    def toString(self):
        return 'NULL'

    def getCode(self):
        return self.constructor.getCode()

    def getConstructor(self):
        return self.constructor

    def isNull(self):
        return True

    def setCode(self, arg):
        pass

    def setConstructor(self, constructor):
        self.constructor = constructor
    
    def toString(self):
        return "TLVNull"