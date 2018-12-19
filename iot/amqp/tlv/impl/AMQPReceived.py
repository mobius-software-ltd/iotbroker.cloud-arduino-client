import iot.amqp.avps.AMQPType as AMQPType
import iot.amqp.constructor.DescribedConstructor as DescribedConstructor
import iot.amqp.header.api.AMQPUnwrapper as AMQPUnwrapper
import iot.amqp.header.api.AMQPWrapper as AMQPWrapper
import iot.amqp.tlv.impl.TLVList as TLVList
import iot.amqp.tlv.impl.TLVFixed as TLVFixed

class amqpReceived():
    def __init__(self, sectionNumber, sectionOffset):
        self.sectionNumber = sectionNumber
        self.sectionOffset = sectionOffset

    def toArgumentsList(self):
        list = TLVList.tlvList(None,None)
        wrapper = AMQPWrapper.amqpWrapper()
        if self.sectionNumber is not None:
            list.addElement(0, wrapper.wrap(self.sectionNumber))
        if self.sectionOffset is not None:
            list.addElement(1, wrapper.wrap(self.sectionOffset))

        constructor = DescribedConstructor.describedConstructor(list.getCode(),TLVFixed.tlvFixed(AMQPType.amqpType.getValueByKey('SMALL_ULONG'), 0x23))
        list.setConstructor(constructor)
        return list

    def fromArgumentsList(self, list):
        unwrapper = AMQPUnwrapper.amqpUnwrapper()
        if len(list.getList()) > 0 :
            element = list.getList()[0]
            if element is not None:
                self.sectionNumber = unwrapper.unwrapUInt(element)
        if len(list.getList()) > 1 :
            element = list.getList()[1]
            if element is not None:
                self.sectionOffset = unwrapper.unwrapULong(element)

    def toString(self):
        return 'AMQPReceived [sectionNumber='+ str(self.sectionNumber) + ', sectionOffset=' + str(self.sectionOffset) + ']'

    def getSectionNumber(self):
        return self.sectionNumber

    def setSectionNumber(self, sectionNumber):
        self.sectionNumber = sectionNumber

    def getSectionOffset(self):
        return self.sectionOffset

    def setSectionOffset(self, sectionOffset):
        self.sectionOffset = sectionOffset
        
    def isNull(self):
        return False
