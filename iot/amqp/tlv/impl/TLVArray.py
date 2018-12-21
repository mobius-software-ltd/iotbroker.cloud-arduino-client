import iot.amqp.avps.AMQPType as AMQPType
import iot.amqp.constructor.SimpleConstructor as SimpleConstructor
import iot.amqp.numeric.NumericUtil as NumericUtil

class tlvArray():
    def __init__(self, code, values):
        self.amqpType = AMQPType.amqpType()
        if code is None or values is None:
            self.width = 1
            self.count = 0
            self.size = 0
            self.values = []
            self.elementConstructor = None
            self.constructor = SimpleConstructor.simpleConstructor(self.amqpType.getValueByKey('ARRAY_8'))
        else:
            self.constructor = SimpleConstructor.simpleConstructor(code)
            self.values = values
            self.size = 0
            self.elementConstructor = None
            if code == self.amqpType.getValueByKey('ARRAY_8'):
                self.width = 1
            else:
                self.width = 4
            self.size += self.width
            for tlv in values:
                self.size += tlv.getLength() - tlv.getConstructor().getLength()
                if self.elementConstructor is None and tlv is not None:
                    self.elementConstructor = tlv.getConstructor()
            self.size += self.elementConstructor.getLength()
            self.count = len(values)

    def getElementConstructor(self):
        return self.elementConstructor

    def getElemetsCode(self):
        return self.elementConstructor.getCode()

    def addElement(self, element):
        if self.values is not None and len(self.values) == 0:
            self.elementConstructor = element.getConstructor()
            self.size += self.width
            self.size += self.elementConstructor.getLength()
        self.values.append(element)
        self.count += 1
        self.size += element.getLength() - self.elementConstructor.getLength()
        if self.width == 1 and self.size > 255:
            self.constructor.setCode(self.amqpType.getValueByKey('ARRAY_32'))
            self.width = 4
            self.size += 3

    def getBytes(self):
        constructorBytes = self.constructor.getBytes()

        sizeBytes = bytearray()
        if self.width == 1:
            sizeBytes = NumericUtil.util.addByte(sizeBytes, self.size)
        elif self.width == 4:
            sizeBytes = NumericUtil.util.addInt(sizeBytes, self.size)

        countBytes = bytearray()
        if self.width == 1:
            countBytes = NumericUtil.util.addByte(countBytes, self.count)
        elif self.width != 0 and self.width == 4:
            countBytes = NumericUtil.util.addInt(countBytes, self.count)

        elementConstructorBytes = self.elementConstructor.getBytes()
        valueBytes = bytearray()
        pos = 0
        for tlv in self.values:
            tlvBytes = tlv.getBytes()
            valueBytes += tlvBytes[1:len(tlvBytes)]
            pos += len(tlvBytes) - len(str(elementConstructorBytes))-1
        data = bytearray()
        data.append(constructorBytes)
        if self.size > 0:
            data += sizeBytes
            data += countBytes
            data = NumericUtil.util.addByte(data,elementConstructorBytes)
            data += valueBytes
        return data

    def getElements(self):
        return self.values

    def getValue(self):
        return None

    def getLength(self):
        return self.constructor.getLength() + self.width + self.size

    def isNull(self):
        code = self.constructor.getCode()
        if code == self.amqpType.getValueByKey('NULL'):
            return True
        if code == self.amqpType.getValueByKey('ARRAY_8') or self.amqpType.getValueByKey('ARRAY_32'):
            if len(self.values) == 0:
                return True
        return False

    def getCode(self):
        return self.constructor.getCode()

    def getConstructor(self):
        return self.constructor

    def setCode(self, arg):
        pass

    def setConstructor(self, constructor):
        self.constructor = constructor
    
    def toString(self):
        return "TLVArray"
