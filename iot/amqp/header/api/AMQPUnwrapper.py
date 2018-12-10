import iot.amqp.wrappers.AMQPDecimal as AMQPDecimal
import iot.amqp.wrappers.AMQPSymbol as AMQPSymbol
import iot.amqp.avps.AMQPType as AMQPType 
import iot.amqp.numeric.NumericUtil as NumericUtil

class amqpUnwrapper():
    def __init__(self):
        pass

    def unwrapUByte(self, tlv):
        if tlv.getCode() != AMQPType.amqpType.getValueByKey('UBYTE'):
            print('Error trying to parse UBYTE: received ' + str(tlv.getCode()))
        return tlv.getValue()

    def unwrapByte(self, tlv):
        if tlv.getCode() != AMQPType.amqpType.getValueByKey('BYTE'):
            print('Error trying to parse BYTE: received ' + str(tlv.getCode()))
        return tlv.getValue()

    def unwrapUShort(self, tlv):
        if tlv.getCode() != AMQPType.amqpType.getValueByKey('USHORT'):
            print('Error trying to parse USHORT: received ' + str(tlv.getCode()))
        return (NumericUtil.util.getShort(tlv.getValue()) & 0xffff)

    def unwrapShort(self, tlv):
        if tlv.getCode() != AMQPType.amqpType.getValueByKey('SHORT'):
            print('Error trying to parse SHORT: received ' + str(tlv.getCode()))
        return NumericUtil.util.getShort(tlv.getValue())

    def unwrapUInt(self, tlv):
        code = tlv.getCode()
        if code not in (AMQPType.amqpType.getValueByKey('UINT'),AMQPType.amqpType.getValueByKey('SMALL_UINT'),AMQPType.amqpType.getValueByKey('UINT_0')):
            print('Error trying to parse UINT: received ' + str(tlv.getCode()))
        value = bytes(tlv.getValue())
        if len(value) == 0:
            return 0
        elif len(value) == 1:
            return (tlv.getValue() & 0xff)
        return (tlv.getValue())

    def unwrapInt(self, tlv):
        code = tlv.getCode()
        if code not in (AMQPType.amqpType.getValueByKey('INT'),AMQPType.amqpType.getValueByKey('SMALL_INT')):
            print('Error trying to parse INT: received ' + str(tlv.getCode()))
        value = bytes(tlv.getValue())
        if len(value) == 0:
            return 0
        return tlv.getValue()

    def unwrapULong(self, tlv):
        code = tlv.getCode()
        if code not in (AMQPType.amqpType.getValueByKey('ULONG'),AMQPType.amqpType.getValueByKey('SMALL_ULONG'),AMQPType.amqpType.getValueByKey('ULONG_0')):
            print('Error trying to parse ULONG: received ' + str(tlv.getCode()))
        value = bytes(tlv.getValue())
        if len(value) == 0:
            return 0
        return (tlv.getValue())

    def unwrapLong(self, tlv):
        code = tlv.getCode()
        if code not in (AMQPType.amqpType.getValueByKey('LONG'),AMQPType.amqpType.getValueByKey('SMALL_LONG')):
            print('Error trying to parse LONG: received ' + str(tlv.getCode()))
        value = bytes(tlv.getValue())
        if len(value) == 0:
            return 0
        return tlv.getValue()[0]

    def unwrapBool(self, tlv):
        code = tlv.getCode()
        if code  == AMQPType.amqpType.getValueByKey('BOOLEAN'):
            val = tlv.getValue()
            if val == 0:
                return False
            elif val == 1:
                return True
            else:
                print('Invalid Boolean type value: ' + str(tlv.getCode()))
        if code == AMQPType.amqpType.getValueByKey('BOOLEAN_TRUE'):
            return True
        elif code == AMQPType.amqpType.getValueByKey('BOOLEAN_FALSE'):
            return False
        else:
            print('Error trying to parse BOOLEAN: received ' + str(tlv.getCode()))

    def unwrapDouble(self, tlv):
        code = tlv.getCode()
        if code != AMQPType.amqpType.getValueByKey('DOUBLE'):
            print('Error trying to parse DOUBLE: received ' + str(tlv.getCode()))
        return NumericUtil.util.getDouble(tlv.getValue())

    def unwrapFloat(self, tlv):
        code = tlv.getCode()
        if code != AMQPType.amqpType.getValueByKey('FLOAT'):
            print('Error trying to parse FLOAT: received ' + str(tlv.getCode()))
        return NumericUtil.util.getFloat(tlv.getValue())

    def unwrapTimastamp(self, tlv):
        code = tlv.getCode()
        if code != AMQPType.amqpType.getValueByKey('TIMESTAMP'):
            print('Error trying to parse TIMESTAMP: received ' + str(tlv.getCode()))
        return NumericUtil.util.getLong(tlv.getValue())

    def unwrapDecimal(self, tlv):
        code = tlv.getCode()
        if code not in (AMQPType.amqpType.getValueByKey('DECIMAL_32'),AMQPType.amqpType.getValueByKey('DECIMAL_64'),AMQPType.amqpType.getValueByKey('DECIMAL_128')):
            print('Error trying to parse DECIMAL: received ' + str(tlv.getCode()))
        return AMQPDecimal.amqpDecimal(tlv.getValue())

    def unwrapChar(self, tlv):
        code = tlv.getCode()
        if code != AMQPType.amqpType.getValueByKey('CHAR'):
            print('Error trying to parse CHAR: received ' + str(tlv.getCode()))
        return NumericUtil.util.getInt(tlv.getValue())

    def unwrapString(self, tlv):
        code = tlv.getCode()
        if code not in (AMQPType.amqpType.getValueByKey('STRING_8'),AMQPType.amqpType.getValueByKey('STRING_32')):
            print('Error trying to parse STRING: received ' + str(tlv.getCode()))
        return str(NumericUtil.util.getString(tlv.getValue()))

    def unwrapSymbol(self, tlv):
        code = tlv.getCode()
        if code not in (AMQPType.amqpType.getValueByKey('SYMBOL_8'),AMQPType.amqpType.getValueByKey('SYMBOL_32')):
            print('Error trying to parse SYMBOL: received ' + str(tlv.getCode()))
        return AMQPSymbol.amqpSymbol(str(NumericUtil.util.getString(tlv.getValue())))

    def unwrapBinary(self, tlv):
        code = tlv.getCode()
        if code not in (AMQPType.amqpType.getValueByKey('BINARY_8'),AMQPType.amqpType.getValueByKey('BINARY_32')):
            print('Error trying to parse BINARY: received ' + str(tlv.getCode()))
        return tlv.getValue()

    def unwrapUuid(self, tlv):
        code = tlv.getCode()
        if code != AMQPType.amqpType.getValueByKey('UUID'):
            print('Error trying to parse UUID: received ' + str(tlv.getCode()))
        return tlv.getValue()

    def unwrapList(self, tlv):
        code = tlv.getCode()
        if code not in (AMQPType.amqpType.getValueByKey('LIST_0'),AMQPType.amqpType.getValueByKey('LIST_8'),AMQPType.amqpType.getValueByKey('LIST_32')):
            print('Error trying to parse LIST: received ' + str(tlv.getCode()))
        result = []
        for value in tlv.getList():
            result.append(self.unwrap(value))
        return result

    def unwrapMap(self, tlv):
        code = tlv.getCode()
        if code not in (AMQPType.amqpType.getValueByKey('MAP_8'),AMQPType.amqpType.getValueByKey('MAP_32')):
            print('Error trying to parse MAP: received ' + str(tlv.getCode()))
        result = {}
        for key, value in tlv.getMap().items():
            k = self.unwrap(key)
            v = self.unwrap(value)
            result[k] = v
        return result

    def unwrapArray(self, tlv):
        code = tlv.getCode()
        if code not in (AMQPType.amqpType.getValueByKey('ARRAY_8'),AMQPType.amqpType.getValueByKey('ARRAY_32')):
            print('Error trying to parse ARRAY: received ' + str(code))
        result = []
        for value in tlv.getElements():
            result.append(self.unwrap(value))
        return result

    def unwrap(self, value):
        code = value.getCode()
        if code == AMQPType.amqpType.getValueByKey('NULL'):
            return None
        if code in(AMQPType.amqpType.getValueByKey('ARRAY_8'),AMQPType.amqpType.getValueByKey('ARRAY_32')):
            return self.unwrapArray(value)
        if code in(AMQPType.amqpType.getValueByKey('BINARY_8'),AMQPType.amqpType.getValueByKey('BINARY_32')):
            return self.unwrapBinary(value)
        if code == AMQPType.amqpType.getValueByKey('UBYTE'):
            return self.unwrapUByte(value)
        if code in(AMQPType.amqpType.getValueByKey('BOOLEAN'),AMQPType.amqpType.getValueByKey('BOOLEAN_TRUE'),AMQPType.amqpType.getValueByKey('BOOLEAN_FALSE')):
            return self.unwrapBool(value)
        if code == AMQPType.amqpType.getValueByKey('BYTE'):
            return self.unwrapByte(value)
        if code == AMQPType.amqpType.getValueByKey('CHAR'):
            return self.unwrapChar(value)
        if code == AMQPType.amqpType.getValueByKey('DOUBLE'):
            return self.unwrapDouble(value)
        if code == AMQPType.amqpType.getValueByKey('FLOAT'):
            return self.unwrapFloat(value)
        if code in (AMQPType.amqpType.getValueByKey('INT'),AMQPType.amqpType.getValueByKey('SMALL_INT')):
            return self.unwrapInt(value)
        if code in(AMQPType.amqpType.getValueByKey('LIST_0'),AMQPType.amqpType.getValueByKey('LIST_8'),AMQPType.amqpType.getValueByKey('LIST_32')):
            return self.unwrapList(value)
        if code in (AMQPType.amqpType.getValueByKey('LONG'), AMQPType.amqpType.getValueByKey('SMALL_LONG')):
            return self.unwrapLong(value)
        if code in (AMQPType.amqpType.getValueByKey('MAP_8'), AMQPType.amqpType.getValueByKey('MAP_32')):
            return self.unwrapMap(value)
        if code == AMQPType.amqpType.getValueByKey('SHORT'):
            return self.unwrapShort(value)
        if code in (AMQPType.amqpType.getValueByKey('STRING_8'), AMQPType.amqpType.getValueByKey('STRING_32')):
            return self.unwrapString(value)
        if code in (AMQPType.amqpType.getValueByKey('SYMBOL_8'), AMQPType.amqpType.getValueByKey('SYMBOL_32')):
            return self.unwrapSymbol(value)
        if code == AMQPType.amqpType.getValueByKey('TIMESTAMP'):
            return self.unwrapTimastamp(value)
        if code in(AMQPType.amqpType.getValueByKey('UINT'),AMQPType.amqpType.getValueByKey('SMALL_UINT'),AMQPType.amqpType.getValueByKey('UINT_0')):
            return self.unwrapUInt(value)
        if code in (AMQPType.amqpType.getValueByKey('ULONG'), AMQPType.amqpType.getValueByKey('SMALL_ULONG'), AMQPType.amqpType.getValueByKey('ULONG_0')):
            return self.unwrapULong(value)
        if code == AMQPType.amqpType.getValueByKey('USHORT'):
            return self.unwrapUShort(value)
        if code == AMQPType.amqpType.getValueByKey('UUID'):
            return self.unwrapUuid(value)
        if code in (AMQPType.amqpType.getValueByKey('DECIMAL_32'), AMQPType.amqpType.getValueByKey('DECIMAL_64'), AMQPType.amqpType.getValueByKey('DECIMAL_128')):
            return self.unwrapDecimal(value)
        print('Error received unrecognized type ' + str(code))

