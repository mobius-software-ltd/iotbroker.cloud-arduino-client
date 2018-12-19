import iot.amqp.avps.AMQPType as AMQPType
import iot.amqp.avps.ErrorCode as ErrorCode
import iot.amqp.constructor.DescribedConstructor as DescribedConstructor
import iot.amqp.header.api.AMQPUnwrapper as AMQPUnwrapper
import iot.amqp.header.api.AMQPWrapper as AMQPWrapper
import iot.amqp.wrappers.AMQPSymbol as AMQPSymbol
import iot.amqp.tlv.impl.TLVList as TLVList
import iot.amqp.tlv.impl.TLVFixed as TLVFixed

class amqpError():
    def __init__(self, condition, description, info):
        self.condition = condition
        self.description = description
        self.info = info

    def toArgumentsList(self):
        wrapper = AMQPWrapper.amqpWrapper()
        list = TLVList.tlvList(None,None)
        if self.condition is not None:
            list.addElement(0, wrapper.wrap(AMQPSymbol.amqpSymbol(self.condition)))
        if self.description is not None:
            list.addElement(1, wrapper.wrap(self.description))
        if self.info is not None:
            list.addElement(2, wrapper.wrap(self.info))

        constructor = DescribedConstructor.describedConstructor(list.getCode(),TLVFixed.tlvFixed(AMQPType.amqpType.getValueByKey('SMALL_ULONG'), 0x1D))
        list.setConstructor(constructor)
        return list

    def fromArgumentsList(self, list):
        unwrapper = AMQPUnwrapper.amqpUnwrapper()
        if len(list.getList()) > 0 :
            element = list.getList()[0]
            if element is not None:
                self.condition = ErrorCode.errorCode(unwrapper.unwrapSymbol(element).getValue())
                print('AMQPError ERROR OCCURED condition= ' + str(ErrorCode.errorCode(unwrapper.unwrapSymbol(element).getValue())))
        if len(list.getList()) > 1 :
            element = list.getList()[1]
            if element is not None:
                self.description = unwrapper.unwrapString(element)
        if len(list.getList()) > 2 :
            element = list.getList()[2]
            if element is not None:
                self.info = unwrapper.unwrapMap(element)

    def toString(self):
        return 'AMQPError [condition='+ str(self.condition) + ', description=' + str(self.description) + ', info=' + str(self.info) + ']'

    def getCondition(self):
        return self.condition

    def setCondition(self, condition):
        self.condition = condition

    def getDescription(self):
        return self.description

    def setDescription(self, description):
        self.description = description

    def getInfo(self):
        return self.info

    def setInfo(self, info):
        self.info = info

    def isNull(self):
        return False
