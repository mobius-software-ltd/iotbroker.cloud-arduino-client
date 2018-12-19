import iot.amqp.avps.AMQPType as AMQPType
import iot.amqp.constructor.SimpleConstructor as SimpleConstructor
import iot.amqp.numeric.NumericUtil as NumericUtil

class tlvVariable():
    def __init__(self, code, value):
        self.value = value
        if len(value) > 255:
            self.width = 4
        else:
            self.width = 1
        self.constructor = SimpleConstructor.simpleConstructor(code)

    def getBytes(self):
        constructorBytes = self.constructor.getBytes()
        widthBytes = bytearray()
        if self.width == 1:
            widthBytes.append(len(self.value))
        elif self.width == 4:
            widthBytes = NumericUtil.util.addInt(widthBytes, len(self.value))

        data = bytearray()
        if self.constructor.getType() == 'described':
            data += constructorBytes
        else:
            data.append(constructorBytes)

        data += widthBytes
        if len(self.value) > 0:
            data += self.value
        return data

    def getLength(self):
        return len(self.value) + self.constructor.getLength() + self.width

    def getValue(self):
        return self.value

    def getCode(self):
        return self.constructor.getCode()

    def getConstructor(self):
        return self.constructor

    def isNull(self):
        if self.constructor.getType() == 'simple': 
            code = self.constructor.getCode()
            if code == AMQPType.amqpType.getValueByKey('NULL'):
                return True
            else:
                return False
        else:
            return False

    def setCode(self, arg):
        pass

    def setConstructor(self, constructor):
        self.constructor = constructor
    
    def toString(self):
        return "TLVVariable"