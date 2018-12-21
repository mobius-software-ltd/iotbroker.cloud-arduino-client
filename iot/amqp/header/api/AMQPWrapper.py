import iot.amqp.avps.AMQPType as AMQPType 
import iot.amqp.tlv.impl.TLVNull as TLVNull
import iot.amqp.tlv.impl.TLVArray as TLVArray 
import iot.amqp.tlv.impl.TLVList as TLVList
import iot.amqp.tlv.impl.TLVMap as TLVMap
import iot.amqp.tlv.impl.TLVFixed as TLVFixed
import iot.amqp.tlv.impl.TLVVariable as TLVVariable
import iot.amqp.numeric.NumericUtil as NumericUtil

class amqpWrapper():
    def __init__(self):
        self.amqpType = AMQPType.amqpType()

    def wrap(self, obj):
        result = None
        if obj is None:
            return TLVNull.tlvNull()

        if obj.getType() == 'ubyte':
            result = self.wrapByte(obj.getValue())
        elif obj.getType() == 'ushort':
            if obj.getValue() >= 0:
                result = self.wrapUByte(obj.getValue())
            else:
                result = self.wrapShort(obj.getValue())
        elif obj.getType() == 'uint':
            if obj.getValue() > 0:
                result = self.wrapUShort(obj.getValue())
            else:
                result = self.wrapInt(obj.getValue())
        elif obj.getType() == 'ulong':
            if obj.getValue() >= 0:
                result = self.wrapUInt(obj.getValue())
            else:
                result = self.wrapLong(obj.getValue())
        elif obj.getType() == 'decimal128':
            result = self.wrapULong(obj.getValue())
        elif obj.getType() == 'string':
            result = self.wrapString(obj.getValue())
        elif obj.getType() == 'AMQPSymbol':
            result = self.wrapSymbol(obj.getValue())
        elif obj.getType() == 'bytearray':
            result = self.wrapBinary(obj.getValue())
        elif obj.getType() == 'bool':
            result = self.wrapBool(obj.getValue())
        elif obj.getType() == 'chararray':
            result = self.wrapChar(obj.getValue())
        elif obj.getType() == 'double':
            result = self.wrapDouble(obj.getValue())
        elif obj.getType() == 'float':
            result = self.wrapFloat(obj.getValue())
        elif obj.getType() == 'uuid':
            result = self.wrapUuid(obj.getValue())
        elif obj.getType() == 'timestamp':
            result = self.wrapTimestamp(obj.getValue())
        elif obj.getType() == 'AMQPDecimal':
            val = obj.getValue()
            if len(val) == 4:
                result = self.wrapDecimal32(val)
            elif len(val) == 8:
                result = self.wrapDecimal64(val)
            elif len(val) == 16:
                result = self.wrapDecimal128(val)
        else:
            print('Wrapper received unrecognized type ' + str(obj))

        return result

    def wrapBool(self, bool):
        value = bytearray()
        if bool:
            code = self.amqpType.getValueByKey('BOOLEAN_TRUE')
        else:
            code = self.amqpType.getValueByKey('BOOLEAN_FALSE')
        return TLVFixed.tlvFixed(code, value)

    def wrapUByte(self, bt):
        if bt < 0:
            print('Error negative value of ' + str(bt) + ' cannot be assigned to UBYTE type')
        return TLVFixed.tlvFixed(self.amqpType.getValueByKey('UBYTE'), bt)

    def wrapByte(self, bt):
        return TLVFixed.tlvFixed(self.amqpType.getValueByKey('BYTE'), bt)

    def wrapUInt(self, i):
        if i < 0:
            print('Error negative value of ' + str(i) + ' cannot be assigned to UINT type')
        value = self.convertUInt(i)
        code = None
        if len(value) == 0:
            code = self.amqpType.getValueByKey('UINT_0')
        elif len(value) == 1:
            code = self.amqpType.getValueByKey('SMALL_UINT')
        elif len(value) > 1:
            code = self.amqpType.getValueByKey('UINT')
        return TLVFixed.tlvFixed(code, value)

    def wrapInt(self, i):
        value = self.convertUInt(i)
        code = None
        if len(value) > 0:
            code = self.amqpType.getValueByKey('INT')
        else:
            code = self.amqpType.getValueByKey('SMALL_INT')
        return TLVFixed.tlvFixed(code, value)

    def wrapULong(self, l):
        if l is None:
            print('Wrapper cannot wrap ulong null')
        if l < 0:
            print('negative value of ' + str(l) + ' cannot be assignet to ULONG type')
        value = self.convertULong(l)
        code = None
        if len(value) == 0:
            code = self.amqpType.getValueByKey('ULONG_0')
        elif len(value) == 1:
            code = self.amqpType.getValueByKey('SMALL_ULONG')
        else:
            code = self.amqpType.getValueByKey('ULONG')
        return TLVFixed.tlvFixed(code, value)

    def wrapLong(self, l):
        value = self.convertULong(l)
        code = None
        if len(value) > 1:
            code = self.amqpType.getValueByKey('LONG')
        else:
            code = self.amqpType.getValueByKey('SMALL_LONG')
        return TLVFixed.tlvFixed(code, value)

    def wrapBinary(self, bt):
        if bt is None:
            print('Wrapper cannot wrap binary null')
        code = None
        if len(bt) > 255:
            code = self.amqpType.getValueByKey('BINARY_32')
        else:
            code = self.amqpType.getValueByKey('BINARY_8')
        return TLVFixed.tlvFixed(code, bt)

    def wrapUuid(self, uuid):
        if uuid is None:
            print('Wrapper cannot wrap uuid null')
        return TLVFixed.tlvFixed(self.amqpType.getValueByKey('UUID'), bytes(uuid, 'utf-8'))

    def wrapUShort(self, sh):
        if sh < 0:
            print('negative value of ' + str(sh) + ' cannot be assignet to UShort type')
        data = bytearray()
        data = NumericUtil.util.addShort(data, sh)
        return TLVFixed.tlvFixed(self.amqpType.getValueByKey('USHORT'), data)

    def wrapShort(self, sh):
        data = bytearray()
        data = NumericUtil.util.addShort(data, sh)
        return TLVFixed.tlvFixed(self.amqpType.getValueByKey('USHORT'), data)

    def wrapDouble(self, db):
        data = bytearray()
        data = NumericUtil.util.addDouble(data, db)
        return TLVFixed.tlvFixed(self.amqpType.getValueByKey('DOUBLE'), data)

    def wrapFloat(self, f):
        data = bytearray()
        data = NumericUtil.util.addFloat(data, f)
        return TLVFixed.tlvFixed(self.amqpType.getValueByKey('FLOAT'), data)

    def wrapChar(self, ch):
        data = bytearray()
        data = NumericUtil.util.addInt(data, ch)
        return TLVFixed.tlvFixed(self.amqpType.getValueByKey('CHAR'), data)

    def wrapTimestamp(self, stamp):
        if stamp is None:
            print('Wrapper cannot wrap timestamp null')
        data = bytearray()
        data = NumericUtil.util.addLong(data, stamp)
        return TLVFixed.tlvFixed(self.amqpType.getValueByKey('TIMESTAMP'), data)

    def wrapDecimal32(self, d):
        if d is None:
            print('Wrapper cannot wrap decimal32 null')
        return TLVFixed.tlvFixed(self.amqpType.getValueByKey('DECIMAL_32'), d.getValue())

    def wrapDecimal64(self, d):
        if d is None:
            print('Wrapper cannot wrap decimal64 null')
        return TLVFixed.tlvFixed(self.amqpType.getValueByKey('DECIMAL_64'), d.getValue())

    def wrapDecimal128(self, d):
        if d is None:
            print('Wrapper cannot wrap decimal128 null')
        return TLVFixed.tlvFixed(self.amqpType.getValueByKey('DECIMAL_128'), d.getValue())

    def wrapString(self, s):
        if s is None:
            print('Wrapper cannot wrap string null')
        value = bytes(s,'utf-8')
        code = None
        if len(value) > 255:
            code = self.amqpType.getValueByKey('STRING_32')
        else:
            code = self.amqpType.getValueByKey('STRING_8')
        return TLVVariable.tlvVariable(code, value)

    def wrapSymbol(self, s):
        if s is None:
            print('Wrapper cannot wrap symbol null')
        value = bytes(s.getValue(),'utf-8')
        code = None
        if len(value) > 255:
            code = self.amqpType.getValueByKey('SYMBOL_32')
        else:
            code = self.amqpType.getValueByKey('SYMBOL_8')
        return TLVVariable.tlvVariable(code, value)

    def wrapList(self, input):
        if input is None:
            print('Wrapper cannot wrap null list')
        list = TLVList.tlvList(None,None)
        for obj in input:
            list.addElement(self.wrap(obj))
        return list

    def wrapMap(self, input):
        if input is None:
            print('Wrapper cannot wrap null map')
        map = TLVMap.tlvMap(None,None)
        if isinstance(input, dict):
            for key, value in input.items():
                map[self.wrap(key)] = self.wrap(value)
        return map

    def wrapArray(self, input):
        if input is None:
            print('Wrapper cannot wrap null array')
        array = TLVArray.tlvArray(None,None)
        for obj in input:
            res = self.wrap(obj)
            array.addElement(res)
        return array

    def convertUInt(self, i):
        data = bytearray()
        if i == 0:
            return data
        elif i > 0 and i <= 255:
            data = NumericUtil.util.addByte(data, i)
            return data
        else:
            data = NumericUtil.util.addInt(data, i)
            return data

    def convertInt(self, i):
        data = bytearray()
        if i == 0:
            return data
        elif i >= -128 and i <= 127:
            return i
        else:
            data = NumericUtil.util.addInt(data, i)
            return data

    def convertULong(self, l):
        data = bytearray()
        if l == 0:
            return data
        elif l > 0 and l <= 255:
            return l
        else:
            data = NumericUtil.util.addLong(data, l)
            return data

    def convertLong(self, l):
        data = bytearray()
        if l == 0:
            return data
        elif l >= -128 and l <= 127:
            return l
        else:
            data = NumericUtil.util.addLong(data, l)
            return data


