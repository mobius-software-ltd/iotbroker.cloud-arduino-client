import iot.amqp.avps.AMQPType as AMQPType
import iot.amqp.constructor.SimpleConstructor as SimpleConstructor
import iot.amqp.numeric.NumericUtil as NumericUtil
import iot.amqp.tlv.impl.TLVNull as TLVNull
import iot.amqp.tlv.impl.TLVMap as TLVMap
import iot.amqp.tlv.impl.TLVArray as TLVArray
import iot.amqp.tlv.impl.TLVList as TLVList

class tlvList():
    def __init__(self, code, values):
        self.amqpType = AMQPType.amqpType()
        if code is None or values is None:
            self.width = 0
            self.count = 0
            self.size = 0
            self.values = []
            self.constructor = SimpleConstructor.simpleConstructor(self.amqpType.getValueByKey('LIST_0'))
        else:
            self.values = values
            self.size = 0
            if code == self.amqpType.getValueByKey('LIST_8'):
                self.width = 1
            else:
                self.width = 4
            self.size += self.width
            for tlv in values:
                self.size += tlv.getLength()
            self.count = len(values)
            self.constructor = SimpleConstructor.simpleConstructor(code)

    def update(self):
        if self.width == 1 and self.size > 255:
            self.constructor.setCode(self.amqpType.getValueByKey('LIST_32'))
            self.width = 4
            self.size += 3

    def addElement(self, index, element):
        if index is None or index == 0:
            if self.size == 0:
                self.constructor.setCode(self.amqpType.getValueByKey('LIST_8'))
                self.width = 1
                self.size += 1
            self.count += 1
            self.size += element.getLength()
            self.values.append(element)
            self.update()
        else:
            diff = index - len(self.values)
            while diff >= 0:
                self.addElement(None, element=TLVNull.tlvNull())
                diff -= 1
            self.setElement(index, element)

    def setElement(self, index, element):
        if index < len(self.values):
            self.size -= self.values[index].getLength()
            self.values[index] = element
            self.size += element.getLength()
            self.update()

    def addToList(self, index, elemIndex, element):
        if self.count < index:
            self.addElement(index, element = TLVList.tlvList(None,None))
        list = self.values[index]
        if list is None:
            self.setElement(index, element = TLVList.tlvList(None,None))
        values = self.values[index]
        values.addElement(elemIndex, element)
        self.size += element.getLength()
        self.update()

    def addToMap(self, index, key, value):
        if self.count < index:
            self.addElement(index, element = TLVMap.tlvMap(None,None))
        map = self.values[index]
        if map is None:
            self.setElement(index, element = TLVMap.tlvMap(None,None))
        values = self.values[index]
        values.putElement(key, value)
        self.size += key.getLength() + value.getLength()
        self.update()

    def addToArray(self, index, element):
        if self.count < index:
            self.addElement(index, element = TLVArray.tlvArray(None,None))
        array = self.values[index]
        if array is None:
            self.setElement(index, element = TLVArray.tlvArray(None,None))
        values = self.values[index]
        values.addElement(element)
        self.size += element.getLength()
        self.update()

    def getBytes(self):
        constructorBytes = self.constructor.getBytes()

        sizeBytes = bytearray()
        if self.width == 1:
            sizeBytes = NumericUtil.util.addByte(sizeBytes, self.size)
        elif self.width != 0:
            sizeBytes = NumericUtil.util.addInt(sizeBytes, self.size)

        countBytes = bytearray()
        if self.width == 1:
            countBytes = NumericUtil.util.addByte(countBytes, self.count)
        elif self.width != 0:
            countBytes = NumericUtil.util.addInt(countBytes, self.count)

        valueBytes = bytearray()
        pos = 0
        if self.values is not None:
            for tlv in self.values:
                tlvBytes = tlv.getBytes()
                valueBytes += tlvBytes
                pos += len(tlvBytes)
        data = bytearray()
        data += constructorBytes
        if self.size > 0:
            data += sizeBytes
            data += countBytes
            data += valueBytes
        return data

    def getList(self):
        return self.values

    def getValue(self):
        return None

    def getLength(self):
        return self.constructor.getLength() + self.width + self.size

    def getCode(self):
        return self.getConstructor().getCode()

    def getConstructor(self):
        return self.constructor

    def isNull(self):
        if self.constructor.getType() == 'simple': 
            code = self.constructor.getCode()
            if code == self.amqpType.getValueByKey('NULL'):
                return True
            else:
                return False
        else:
            return False

    def setCode(self):
        pass

    def setConstructor(self, constructor):
        self.constructor = constructor
        
    def toString(self):
        return "TLVList"
