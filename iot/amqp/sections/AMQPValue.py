import iot.amqp.header.api.AMQPWrapper as AMQPWrapper
import iot.amqp.header.api.AMQPUnwrapper as AMQPUnwrapper
import iot.amqp.constructor.DescribedConstructor as DescribedConstructor
import iot.amqp.avps.SectionCode as SectionCode
import iot.amqp.tlv.impl.TLVFixed as TLVFixed
import iot.amqp.tlv.impl.TLVNull as TLVNull
import iot.amqp.avps.AMQPType as AMQPType

class amqpValue():
    def __init__(self, value):
        self.value = value

    def getValue(self):
        val = None
        wrapper = AMQPWrapper.amqpWrapper() 
        if self.value is not None:
            val = wrapper.wrap(self.value)
        else:
            val = TLVNull.tlvNull()

        if val is not None:
            constructor = DescribedConstructor.describedConstructor(val.getCode(), TLVFixed.tlvFixed(AMQPType.amqpType.getValueByKey('SMALL_ULONG'), 0x77))
            val.setConstructor(constructor)
        return val

    def fill(self, value):
        unwrapper = AMQPUnwrapper.amqpUnwrapper()
        if value is not None:
            self.value = unwrapper.unwrap(value)

    def getCode(self):
        return SectionCode.sectionCode.getValueByKey('VALUE')

    def toString(self):
        return 'AMQPValue [value=' + str(self.value) + ']'

    def getValue(self):
        return self.value

    def setValue(self, value):
        self.value = value
