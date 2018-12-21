import iot.amqp.avps.AMQPType as AMQPType
import iot.amqp.constructor.DescribedConstructor as DescribedConstructor
import iot.amqp.header.api.AMQPUnwrapper as AMQPUnwrapper
import iot.amqp.header.api.AMQPWrapper as AMQPWrapper
import iot.amqp.tlv.impl.TLVList as TLVList
import iot.amqp.tlv.impl.TLVFixed as TLVFixed

class amqpModified():
    def __init__(self, deliveryFailed, undeliverableHere, messageAnnotations):
        self.deliveryFailed = deliveryFailed
        self.undeliverableHere = undeliverableHere
        self.messageAnnotations = messageAnnotations
        self.amqpType = AMQPType.amqpType()

    def toArgumentsList(self):
        list = TLVList.tlvList(None,None)
        wrapper = AMQPWrapper.amqpWrapper()
        if self.deliveryFailed is not None:
            list.addElement(0, wrapper.wrap(self.deliveryFailed))
        if self.undeliverableHere is not None:
            list.addElement(1, wrapper.wrap(self.undeliverableHere))
        if self.messageAnnotations is not None:
            if len(self.messageAnnotations) > 0:
                list.addElement(2, wrapper.wrapMap(self.messageAnnotations))

        constructor = DescribedConstructor.describedConstructor(list.getCode(),TLVFixed.tlvFixed(self.amqpType.getValueByKey('SMALL_ULONG'), 0x27))
        list.setConstructor(constructor)
        return list

    def fromArgumentsList(self, list):
        unwrapper = AMQPUnwrapper.amqpUnwrapper()
        if len(list.getList()) > 0 :
            element = list.getList()[0]
            if element is not None:
                self.deliveryFailed = unwrapper.unwrapBool(element)
        if len(list.getList()) > 1 :
            element = list.getList()[1]
            if element is not None:
                self.undeliverableHere = unwrapper.unwrapBool(element)
        if len(list.getList()) > 2 :
            element = list.getList()[2]
            if element is not None:
                self.messageAnnotations = unwrapper.unwrapMap(element)

    def toString(self):
        return 'AMQPError [condition='+ str(self.condition) + ', description=' + str(self.description) + ', info=' + str(self.info) + ']'

    def getDeliveryFailed(self):
        return self.deliveryFailed

    def setDeliveryFailed(self, deliveryFailed):
        self.deliveryFailed = deliveryFailed

    def getUndeliverableHere(self):
        return self.undeliverableHere

    def setUndeliverableHere(self, undeliverableHere):
        self.undeliverableHere = undeliverableHere

    def getMessageAnnotations(self):
        return self.messageAnnotations

    def setMessageAnnotations(self, messageAnnotations):
        self.messageAnnotations = messageAnnotations

    def isNull(self):
        return False
