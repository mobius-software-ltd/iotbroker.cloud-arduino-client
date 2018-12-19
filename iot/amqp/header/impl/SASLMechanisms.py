import iot.amqp.avps.AMQPType as AMQPType
import iot.amqp.avps.HeaderCode as HeaderCode
import iot.amqp.constructor.DescribedConstructor as DescribedConstructor
import iot.amqp.header.api.AMQPUnwrapper as AMQPUnwrapper
import iot.amqp.header.api.AMQPWrapper as AMQPWrapper
import iot.amqp.tlv.impl.TLVFixed as TLVFixed
import iot.amqp.tlv.impl.TLVList as TLVList

class saslMechanisms():
    def __init__(self,code,doff,type,channel,mechanisms):

        if code is not None:
            self.code = code
        else:
            self.code = HeaderCode.headerCode.getValueByKey('MECHANISMS')
        if doff is not None:
            self.doff = doff
        else:
            self.doff = 2
        if type is not None:
            self.type = type
        else:
            self.type = 1
        if channel is not None:
            self.channel = channel
        else:
            self.channel = 0
        self.mechanisms = mechanisms

    def setDoff(self,doff):
        self.doff = doff

    def getDoff(self):
        return self.doff

    def getType(self):
        return self.type

    def setType(self, type):
        self.type = type

    def getChannel(self):
        return self.channel

    def setChannel(self, channel):
        self.channel = channel

    def getCode(self):
        return self.code

    def toArgumentsList(self):
        list = TLVList.tlvList(None,None)

        if self.mechanisms == None:
            print("At least one SASL Mechanism must be specified")
        wrapper = AMQPWrapper.amqpWrapper()
        list.addElement(0,wrapper.wrapArray(self.mechanisms))
        constructor = DescribedConstructor.describedConstructor(list.getCode(), TLVFixed.tlvFixed(AMQPType.amqpType.getValueByKey('SMALL_ULONG'), 0x40))
        list.setConstructor(constructor)
        return list

    def fromArgumentsList(self, list):
        size = len(list.getList())
        if size > 0:
            element = list.getList()[0]
            if element is None and not element.isNull():
                print("Received malformed SASL-Init header: mechanism can't be null")
            unwrapper = AMQPUnwrapper.amqpUnwrapper()
            self.mechanisms = unwrapper.unwrapArray(element)

    def toString(self):
        return "SASLMechanisms [mechanisms=" + str(self.mechanisms) + ", code=" + str(self.code) + ", doff=" + str(self.doff) + ", type=" + str(self.type) + ", channel=" + str(self.channel) + "]"

    def setMechanisms(self, mechanisms):
        self.mechanisms = mechanisms

    def getMechanisms(self):
        return self.mechanisms

