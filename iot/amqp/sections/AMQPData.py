import iot.amqp.avps.AMQPType as AMQPType
import iot.amqp.header.api.AMQPWrapper as AMQPWrapper
import iot.amqp.header.api.AMQPUnwrapper as AMQPUnwrapper
import iot.amqp.constructor.DescribedConstructor as DescribedConstructor
import iot.amqp.avps.SectionCode as SectionCode
import iot.amqp.tlv.impl.TLVNull as TLVNull
import iot.amqp.tlv.impl.TLVFixed as TLVFixed

class amqpData():
    def __init__(self, data):
        self.data = data
        self.amqpType = AMQPType.amqpType()
        self.sectionCode = SectionCode.sectionCode()

    def getValue(self):
        wrapper = AMQPWrapper.amqpWrapper()
        bin = None
        if self.data is not None:
            bin = wrapper.wrap(self.data)
        else:
            bin = TLVNull.tlvNull()
        constructor = DescribedConstructor.describedConstructor(bin.getCode(), TLVFixed.tlvFixed(self.amqpType.getValueByKey('SMALL_ULONG'), 0x75))
        bin.setConstructor(constructor)
        return bin

    def fill(self, value):
        unwrapper = AMQPUnwrapper.amqpUnwrapper()
        if value is not None:
            self.data = unwrapper.unwrapBinary(value)

    def getCode(self):
        return self.sectionCode.getValueByKey('DATA')

    def toString(self):
        return 'AMQPData [data=' + str(self.data) + ']'

    def getData(self):
        return self.data

    def setValue(self, data):
        self.data = data
