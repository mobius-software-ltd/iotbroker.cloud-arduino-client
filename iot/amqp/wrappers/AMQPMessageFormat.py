import iot.amqp.numeric.NumericUtil as NumericUtil

class amqpMessageFormat():
    def __init__(self, value, messageFormat, version):
        if value != None:
            self.initValue(value)
        else:
            self.initFormat(messageFormat, version)

    def initValue(self, value):
        arr = bytearray()
        arr = NumericUtil.util.addInt(arr, value)
        mf = bytearray(1)
        mf += arr[0:3]
        self.messageFormat = NumericUtil.util.getInt(mf)
        self.version = NumericUtil.util.getByte(arr[3:4],0) & 0xff

    def initFormat(self, messageFormat, version):
        self.messageFormat = messageFormat
        self.version = version

    def getMessageFormat(self):
        return self.messageFormat

    def getVersion(self):
        return self.version

    def encode(self):
        arr = bytearray()
        mf = bytearray()
        mf = NumericUtil.util.addInt(mf, self.getMessageFormat())
        arr +=  mf[1:4]
        arr = NumericUtil.util.addByte(arr,self.getVersion())
        return NumericUtil.util.getInt(arr)
