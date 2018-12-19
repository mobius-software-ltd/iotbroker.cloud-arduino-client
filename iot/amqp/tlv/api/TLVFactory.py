import iot.amqp.avps.AMQPType as AMQPType
import iot.amqp.constructor.DescribedConstructor as DescribedConstructor
import iot.amqp.constructor.SimpleConstructor as SimpleConstructor
import iot.amqp.tlv.impl.TLVArray as TLVArray
import iot.amqp.tlv.impl.TLVList as TLVList
import iot.amqp.tlv.impl.TLVMap as TLVMap
import iot.amqp.tlv.impl.TLVFixed as TLVFixed
import iot.amqp.tlv.impl.TLVVariable as TLVVariable
import iot.amqp.tlv.impl.TLVNull as TLVNull
import iot.amqp.numeric.NumericUtil as NumericUtil

class tlvFactory():
    def __init__(self, index):
        self.index = index

    def getIndex(self):
        return self.index

    def getTlv(self, buf):
        constructor = self.getConstructor(buf)
        tlv = self.getElement(constructor, buf)
        return tlv

    def getConstructor(self, buf):
        code = None
        constructor = None
        codeByte = NumericUtil.util.getByte(buf, self.index)
        self.index += 1
        if codeByte == 0:
            descriptor = self.getTlv(buf)
            code = AMQPType.amqpType.getValueByKey((NumericUtil.util.getByte(buf, self.index) & 0xff))
            self.index += 1
            constructor = DescribedConstructor.describedConstructor(code, descriptor)
        else:
            code = AMQPType.amqpType.getValueByKey((codeByte & 0xff))
            constructor = SimpleConstructor.simpleConstructor(code)
        return constructor

    def getElement(self, constructor, buf):
        tlv = None
        code = constructor.getCode()
        if code == AMQPType.amqpType.getValueByKey('NULL'):
            tlv = TLVNull.tlvNull()
        elif code in (AMQPType.amqpType.getValueByKey('BOOLEAN_TRUE'),AMQPType.amqpType.getValueByKey('BOOLEAN_FALSE'),AMQPType.amqpType.getValueByKey('UINT_0'),AMQPType.amqpType.getValueByKey('ULONG_0')):
            tlv = TLVFixed.tlvFixed(code, bytearray())
        elif code in (AMQPType.amqpType.getValueByKey('BOOLEAN'),AMQPType.amqpType.getValueByKey('UBYTE'),AMQPType.amqpType.getValueByKey('BYTE'),AMQPType.amqpType.getValueByKey('SMALL_UINT'),AMQPType.amqpType.getValueByKey('SMALL_INT'),AMQPType.amqpType.getValueByKey('SMALL_ULONG'),AMQPType.amqpType.getValueByKey('SMALL_LONG')):
            value1 = NumericUtil.util.getByte(buf,self.index)
            self.index += 1
            tlv = TLVFixed.tlvFixed(code, value1)
        elif code in (AMQPType.amqpType.getValueByKey('SHORT'),AMQPType.amqpType.getValueByKey('USHORT')):
            value2 = buf[self.index:self.index + 2]
            self.index += 2
            tlv = TLVFixed.tlvFixed(code, value2)
        elif code in (AMQPType.amqpType.getValueByKey('UINT'),AMQPType.amqpType.getValueByKey('INT'),AMQPType.amqpType.getValueByKey('FLOAT'),AMQPType.amqpType.getValueByKey('DECIMAL_32'),AMQPType.amqpType.getValueByKey('CHAR')):
            value4 = buf[self.index: self.index+4]
            self.index += 4
            tlv = TLVFixed.tlvFixed(code, value4)
        elif code in (AMQPType.amqpType.getValueByKey('ULONG'),AMQPType.amqpType.getValueByKey('LONG'),AMQPType.amqpType.getValueByKey('DECIMAL_64'),AMQPType.amqpType.getValueByKey('DOUBLE'),AMQPType.amqpType.getValueByKey('TIMESTAMP')):
            value8 = buf[self.index: self.index+8]
            self.index += 8
            tlv = TLVFixed.tlvFixed(code, value8)
        elif code in (AMQPType.amqpType.getValueByKey('DECIMAL_128'), AMQPType.amqpType.getValueByKey('UUID')):
            value16 = buf[self.index: self.index + 16]
            self.index += 16
            tlv = TLVFixed.tlvFixed(code, value16)
        elif code in (AMQPType.amqpType.getValueByKey('STRING_8'), AMQPType.amqpType.getValueByKey('SYMBOL_8'), AMQPType.amqpType.getValueByKey('BINARY_8')):
            varlen = NumericUtil.util.getByte(buf,self.index) & 0xff
            self.index += 1
            varValue8 = buf[self.index: self.index + int(varlen)]
            self.index += int(varlen)
            tlv = TLVVariable.tlvVariable(code, varValue8)
        elif code in (AMQPType.amqpType.getValueByKey('STRING_32'), AMQPType.amqpType.getValueByKey('SYMBOL_32'), AMQPType.amqpType.getValueByKey('BINARY_32')):
            var32len = NumericUtil.util.getInt(buf[self.index:self.index+4])
            self.index += 4
            varValue32 = buf[self.index: self.index + int(var32len)]
            self.index += int(var32len)
            tlv = TLVVariable.tlvVariable(code, varValue32)
        elif code is AMQPType.amqpType.getValueByKey('LIST_0'):
            tlv = TLVList.tlvList(None, None)
        elif code is AMQPType.amqpType.getValueByKey('LIST_8'):
            list8size = NumericUtil.util.getByte(buf,self.index) & 0xff
            self.index += 1
            list8count = NumericUtil.util.getByte(buf,self.index) & 0xff
            self.index += 1
            list8values = []
            for i in range(0,list8count):
                entity = self.getTlv(buf)
                list8values.append(entity)
            tlv = TLVList.tlvList(code, list8values)
        elif code is AMQPType.amqpType.getValueByKey('LIST_32'):
            list32size = NumericUtil.util.getInt(buf[self.index:self.index+4])
            self.index += 4
            list32count = NumericUtil.util.getInt(buf[self.index:self.index+4])
            self.index += 4
            list32values = []
            for i in range(0, list32count):
                list32values.append(self.getTlv(buf))
            tlv = TLVList.tlvList(code, list32values)
        elif code is AMQPType.amqpType.getValueByKey('MAP_8'):
            map8size = NumericUtil.util.getByte(buf,self.index) & 0xff
            self.index += 1
            map8count = NumericUtil.util.getByte(buf,self.index) & 0xff
            self.index += 1
            stop8 = self.index + map8size - 1
            map8 = TLVMap.tlvMap(None,None)
            while self.index < stop8:
                map8.putElement(self.getTlv(buf), self.getTlv(buf))
            tlv = TLVMap.tlvMap(code, map8)
        elif code is AMQPType.amqpType.getValueByKey('MAP_32'):
            map32size = NumericUtil.util.getInt(buf[self.index:self.index + 4])
            self.index += 4
            map32count = NumericUtil.util.getInt(buf[self.index:self.index + 4])
            self.index += 4
            stop32 = self.index + map32size - 4
            map32 = TLVMap.tlvMap(None, None)
            while self.index < stop32:
                map32.putElement(self.getTlv(buf), self.getTlv(buf))
            tlv = TLVMap.tlvMap(code, map32)
        elif code is AMQPType.amqpType.getValueByKey('ARRAY_8'):
            array8size = NumericUtil.util.getByte(buf,self.index) & 0xff
            self.index += 1
            array8count = NumericUtil.util.getByte(buf,self.index) & 0xff
            self.index += 1
            arr8 = []
            arr8constructor = self.getConstructor(buf)
            for i in range(0,array8count):
                arr8.append(self.getElement(arr8constructor,buf))
            tlv = TLVArray.tlvArray(code, arr8)
        elif code is AMQPType.amqpType.getValueByKey('ARRAY_32'):
            arr32size = NumericUtil.util.getInt(buf[self.index:self.index+4])
            self.index += 4
            arr32count = NumericUtil.util.getInt(buf[self.index:self.index+4])
            self.index += 4
            arr32 = []
            arr32constructor = self.getConstructor(buf)
            for i in range(0, arr32count):
                arr32.append(self.getElement(arr32constructor, buf))
            tlv = TLVArray.tlvArray(code, arr32)

            if constructor.getType() == 'described':
                tlv.setConstructor(constructor)

            return tlv
