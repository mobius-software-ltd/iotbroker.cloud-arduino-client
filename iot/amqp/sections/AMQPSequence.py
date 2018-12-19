import iot.amqp.avps.AMQPType as AMQPType
import iot.amqp.header.api.AMQPWrapper as AMQPWrapper
import iot.amqp.header.api.AMQPUnwrapper as AMQPUnwrapper
import iot.amqp.constructor.DescribedConstructor as DescribedConstructor
import iot.amqp.avps.SectionCode as SectionCode
import iot.amqp.tlv.impl.TLVFixed as TLVFixed
import iot.amqp.tlv.impl.TLVList as TLVList

class amqpSequence():
    def __init__(self, sequence):
        self.sequence = sequence

    def getValue(self):
        list = TLVList.tlvList(None, None)
        wrapper = AMQPWrapper.amqpWrapper()
        if self.sequence is not None and len(self.sequence) > 0:
            list = wrapper.wrapList(self.sequence)

        constructor = DescribedConstructor.describedConstructor(list.getCode(), TLVFixed.tlvFixed(AMQPType.amqpType.getValueByKey('SMALL_ULONG'), 0x76))
        list.setConstructor(constructor)
        return list

    def fill(self, list):
        unwrapper = AMQPUnwrapper.amqpUnwrapper()
        if list is not None:
            self.sequence = unwrapper.unwrapList(list)

    def getCode(self):
        return SectionCode.sectionCode.getValueByKey('SEQUENCE')

    def toString(self):
        return 'AMQPSequence [sequence=' + str(self.sequence) + ']'

    def getSequence(self):
        return self.sequence

    def setSequence(self, sequence):
        self.sequence = sequence
