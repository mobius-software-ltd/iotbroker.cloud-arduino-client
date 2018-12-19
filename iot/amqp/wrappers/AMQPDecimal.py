import iot.amqp.numeric.NumericUtil as NumericUtil

class amqpDecimal():
    def __init__(self, numeric):
        data = bytearray()
        if numeric.getType() == 'bytearray':
            data = numeric.getValue()
        if numeric.getType() == 'byte':
            data = NumericUtil.util.addByte(data, numeric.getValue())
        if numeric.getType() == 'short':
            data = NumericUtil.util.addShort(data, numeric.getValue())
        if numeric.getType() == 'int':
            data = NumericUtil.util.addInt(data, numeric.getValue())
        if numeric.getType() == 'long':
            data = NumericUtil.util.addLong(data, numeric.getValue())
        if numeric.getType() == 'float':
            data = NumericUtil.util.addFloat(data, numeric.getValue())
        if numeric.getType() == 'double':
            data = NumericUtil.util.addDouble(data, numeric.getValue())
        self.value = data

    def getByte(self):
        return NumericUtil.util.getByte(self.value, 0)

    def getShort(self):
        return NumericUtil.util.getShort(self.value)

    def getInt(self):
        return NumericUtil.util.getInt(self.value)

    def getLong(self):
        return NumericUtil.util.getLong(self.value)

    def getFloat(self):
        return NumericUtil.util.getFloat(self.value)

    def getDouble(self):
        return NumericUtil.util.getDouble(self.value)

    def getValue(self):
        return self.value
