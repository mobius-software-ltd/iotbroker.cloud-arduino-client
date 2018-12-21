import iot.amqp.avps.AMQPType as AMQPType
import iot.amqp.constructor.SimpleConstructor as SimpleConstructor
import iot.amqp.numeric.NumericUtil as NumericUtil

class tlvFixed():
    def __init__(self, code, value):
        self.value = value
        self.constructor = SimpleConstructor.simpleConstructor(code)
        self.amqpType = AMQPType.amqpType()

    def getBytes(self):
        constructorBytes = self.constructor.getBytes()
        data = bytearray()
        if self.constructor.getType() == 'described':
            data += constructorBytes
        else:
            data.append(constructorBytes)
        if len(str(self.value)) > 0:
            if (self.getCode() in (self.amqpType.getValueByKey('INT'),self.amqpType.getValueByKey('BYTE'),self.amqpType.getValueByKey('SHORT'),self.amqpType.getValueByKey('LONG'))):
                    data.append(self.value)
                    return data
            elif (self.getCode() in (self.amqpType.getValueByKey('UINT'),self.amqpType.getValueByKey('UINT_0'),self.amqpType.getValueByKey('SMALL_UINT'))):
                data += self.value
                return data
            elif self.getCode() in (self.amqpType.getValueByKey('BOOLEAN_TRUE'),self.amqpType.getValueByKey('BOOLEAN_FALSE')):
                return data
            else:
                data.append(len(self.value))
                data += self.value
                return data

    def getLength(self):
        if self.value == b'':
            return 1
        elif (self.getCode() in (self.amqpType.getValueByKey('INT'),self.amqpType.getValueByKey('BYTE'),self.amqpType.getValueByKey('SHORT'),self.amqpType.getValueByKey('LONG'))):
            return self.constructor.getLength() + 1
        elif (self.getCode() in (self.amqpType.getValueByKey('UINT'),self.amqpType.getValueByKey('UINT_0'),self.amqpType.getValueByKey('SMALL_UINT'))):
            return self.constructor.getLength() + len(self.value)
        elif self.getCode() in (self.amqpType.getValueByKey('BOOLEAN_TRUE'),self.amqpType.getValueByKey('BOOLEAN_FALSE')):
            return self.constructor.getLength()
        else:
            return self.constructor.getLength() + len(self.value) + 1

    def getValue(self):
        return self.value

    def toString(self):
        code = self.constructor.getCode()
        s = None
        if code == self.amqpType.getValueByKey('BOOLEAN_TRUE'):
            s = '1'
        elif code in (self.amqpType.getValueByKey('BOOLEAN_FALSE'),self.amqpType.getValueByKey('UINT_0'),self.amqpType.getValueByKey('ULONG_0')):
            s = '0'
        elif code in (self.amqpType.getValueByKey('BOOLEAN'),self.amqpType.getValueByKey('BYTE'),self.amqpType.getValueByKey('UBYTE'),self.amqpType.getValueByKey('SMALL_INT'),self.amqpType.getValueByKey('SMALL_LONG'),self.amqpType.getValueByKey('SMALL_UINT'),self.amqpType.getValueByKey('ULONG')):
            s = str(self.value[0])
        elif code in (self.amqpType.getValueByKey('SHORT'), self.amqpType.getValueByKey('USHORT')):
            s = str(NumericUtil.util.getShort(self.value))
        elif code in (self.amqpType.getValueByKey('CHAR'), self.amqpType.getValueByKey('DECIMAL_32'),self.amqpType.getValueByKey('FLOAT'),self.amqpType.getValueByKey('INT'),self.amqpType.getValueByKey('UINT')):
            s = str(NumericUtil.util.getInt(self.value))
        elif code in (self.amqpType.getValueByKey('DECIMAL_64'), self.amqpType.getValueByKey('DOUBLE'),self.amqpType.getValueByKey('LONG'),self.amqpType.getValueByKey('ULONG'),self.amqpType.getValueByKey('TIMESTAMP')):
            s = str(NumericUtil.util.getLong(self.value))
        if code == self.amqpType.getValueByKey('DECIMAL_128'):
            s = 'decimal-128'
        if code == self.amqpType.getValueByKey('UUID'):
            s = str(self.value)
        return s

    def getCode(self):
        return self.constructor.getCode()

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

    def setCode(self, arg):
        pass

    def setConstructor(self, constructor):
        self.constructor = constructor
    
    def toString(self):
        return "TLVFixed"
