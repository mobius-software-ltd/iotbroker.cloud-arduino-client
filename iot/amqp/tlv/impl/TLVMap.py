import iot.amqp.avps.AMQPType as AMQPType
import iot.amqp.constructor.SimpleConstructor as SimpleConstructor
import iot.amqp.numeric.NumericUtil as NumericUtil

class tlvMap():
    def __init__(self, code, map):
        if code is None or map is None:
            self.width = 1
            self.count = 0
            self.size = 1
            self.map = None
            self.constructor = SimpleConstructor.simpleConstructor(AMQPType.amqpType.getValueByKey('MAP_8'))
        else:
            self.map = map
            if code == AMQPType.amqpType.getValueByKey('MAP_8'):
                self.width = 1
            else:
                self.width = 4
            self.size += self.width
            for key, value in map.items():
                self.size += key.getLength()
                self.size += value.getLength()
            self.count = len(self.map)
            self.constructor = SimpleConstructor.simpleConstructor(code)

    def update(self):
        if self.width == 1 and self.size > 255:
            self.constructor.setCode(AMQPType.amqpType.getValueByKey('MAP_32'))
            self.width = 4
            self.size += 3

    def putElement(self, key, value):
        self.map[key] = value
        self.size += key.getLength() + value.getLength()
        self.count += 1
        self.update()

    def getBytes(self):
        constructorBytes = self.constructor.getBytes()
        sizeBytes = bytearray()
        if self.width == 1:
            sizeBytes = NumericUtil.util.addByte(sizeBytes, self.size)
        else:
            sizeBytes = NumericUtil.util.addInt(sizeBytes, self.size)
        countBytes = bytearray()
        if self.width == 1:
            countBytes = NumericUtil.util.addByte(countBytes, self.count*2)
        else:
            countBytes = NumericUtil.util.addInt(countBytes, self.count*2)
        valueBytes = bytearray()
        pos = 0
        for key, value in self.map.items():
            keyBytes = key.getBytes()
            valBytes = value.getBytes()
            valueBytes.append(keyBytes)
            pos += len(keyBytes)
            valueBytes.append(valBytes)
            pos += len(valBytes)
        data = bytearray()
        data.append(constructorBytes)
        if self.size > 0:
            data += sizeBytes
            data += countBytes
            data += valueBytes
        return data

    def getMap(self):
        return self.map

    def getValue(self):
        return None

    def getLength(self):
        return self.constructor.getLength() + self.width + self.size

    def getCode(self):
        return self.constructor.getCode()

    def getConstructor(self):
        return self.constructor

    def isNull(self):
        code = self.constructor.getCode()
        if code == AMQPType.amqpType.getValueByKey('NULL'):
            return True
        if code == AMQPType.amqpType.getValueByKey('ARRAY_8') or AMQPType.amqpType.getValueByKey('ARRAY_32'):
            if len(self.values) == 0:
                return True
        return False

    def setCode(self, arg):
        pass

    def setConstructor(self, constructor):
        self.constructor = constructor
    
    def toString(self):
        return "TLVMap"