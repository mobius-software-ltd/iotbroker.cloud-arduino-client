import iot.amqp.header.api.AMQPWrapper as AMQPWrapper
import iot.amqp.header.api.AMQPUnwrapper as AMQPUnwrapper
import iot.amqp.constructor.DescribedConstructor as DescribedConstructor
import iot.amqp.avps.SectionCode as SectionCode
import iot.amqp.tlv.impl.TLVFixed as TLVFixed
import iot.amqp.tlv.impl.TLVList as TLVList
import iot.amqp.avps.AMQPType as AMQPType

class messageHeader():
    def __init__(self,durable,priority,milliseconds,firstAquirer,deliveryCount):
        self.durable = durable
        self.priority = priority
        self.milliseconds = milliseconds
        self.firstAquirer = firstAquirer
        self.deliveryCount = deliveryCount
        self.amqpType = AMQPType.amqpType()
        self.sectionCode = SectionCode.sectionCode()

    def getValue(self):
        list = TLVList.tlvList(None, None)
        wrapper = AMQPWrapper.amqpWrapper()
        if self.durable is not None:
            list.addElement(0, wrapper.wrap(self.durable))
        if self.priority is not None:
            list.addElement(1, wrapper.wrap(self.priority))
        if self.milliseconds is not None:
            list.addElement(2, wrapper.wrap(self.milliseconds))
        if self.firstAquirer is not None:
            list.addElement(3, wrapper.wrap(self.firstAquirer))
        if self.deliveryCount is not None:
            list.addElement(4, wrapper.wrap(self.deliveryCount))

        constructor = DescribedConstructor.describedConstructor(list.getCode(), TLVFixed.tlvFixed(self.amqpType.getValueByKey('SMALL_ULONG'), 0x70))
        list.setConstructor(constructor)
        return list

    def fill(self, value):
        list = value
        unwrapper = AMQPUnwrapper.amqpUnwrapper()
        if len(list.getList()) > 0:
            element = list.getList()[0]
            if element is not None:
                self.durable = unwrapper.unwrapBool(element)
        if len(list.getList()) > 1:
            element = list.getList()[1]
            if element is not None:
                self.priority = unwrapper.unwrapUByte(element)
        if len(list.getList()) > 2:
            element = list.getList()[2]
            if element is not None:
                self.milliseconds = unwrapper.unwrapUInt(element)
        if len(list.getList()) > 3:
            element = list.getList()[3]
            if element is not None:
                self.firstAquirer = unwrapper.unwrapBool(element)
        if len(list.getList()) > 4:
            element = list.getList()[4]
            if element is not None:
                self.deliveryCount = unwrapper.unwrapUInt(element)

    def getCode(self):
        return self.sectionCode.getValueByKey('HEADER')

    def toString(self):
        return 'MessageHeader [durable=' + str(self.durable) + ', priority=' + str(self.priority) + ', milliseconds=' + str(self.milliseconds) + ', firstAquirer=' + str(self.firstAquirer) + ', deliveryCount=' + str(self.deliveryCount) + ']'

    def getDurable(self):
        return self.durable

    def setDurable(self, durable):
        self.durable = durable

    def getPriority(self):
        return self.priority

    def setPriority(self, priority):
        self.priority = priority

    def getMilliseconds(self):
        return self.milliseconds

    def setMilliseconds(self, milliseconds):
        self.milliseconds = milliseconds

    def getFirstAquirer(self):
        return self.firstAquirer

    def setFirstAquirer(self, firstAquirer):
        self.firstAquirer = firstAquirer

    def getDeliveryCount(self):
        return self.deliveryCount

    def setDeliveryCount(self, deliveryCount):
        self.deliveryCount = deliveryCount
