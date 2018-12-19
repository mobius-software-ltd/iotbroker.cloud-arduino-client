import iot.amqp.avps.AMQPType as AMQPType
import iot.amqp.avps.HeaderCode as HeaderCode
import iot.amqp.constructor.DescribedConstructor as DescribedConstructor
import iot.amqp.header.api.AMQPUnwrapper as AMQPUnwrapper
import iot.amqp.header.api.AMQPWrapper as AMQPWrapper
import iot.amqp.tlv.impl.TLVFixed as TLVFixed
import iot.amqp.tlv.impl.TLVList as TLVList

class saslInit():
    def __init__(self,code,doff,type,channel,mechanism,initialRespone,hostName):
        if code is not None:
            self.code = code
        else:
            self.code = HeaderCode.headerCode.getValueByKey('INIT')
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
        self.mechanism = mechanism
        self.initialRespone = initialRespone
        self.hostName = hostName

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
        wrapper = AMQPWrapper.amqpWrapper()
        if self.mechanism == None:
            print("SASL-Init header's mechanism can't be null")
        list.addElement(0,wrapper.wrap(self.mechanism))
        if self.initialRespone is not None:
            list.addElement(1,wrapper.wrap(self.initialRespone))
        if self.hostName is not None:
            list.addElement(2, wrapper.wrap(self.hostName))

        constructor = DescribedConstructor.describedConstructor(list.getCode(), TLVFixed.tlvFixed(AMQPType.amqpType.getValueByKey('SMALL_ULONG'), 0x41))
        list.setConstructor(constructor)
        return list

    def fromArgumentsList(self, list):
        unwrapper = AMQPUnwrapper.amqpUnwrapper()
        size = len(list.getList())
        if size == 0:
            print("Received malformed SASL-Init header: mechanism can't be null")
        if size > 3:
            print('Received malformed SASL-Init header. Invalid number of arguments: ' + str(size))
        if size > 0:
            element = list.getList()[0]
            if element is None or element.isNull():
                print("Received malformed SASL-Init header: mechanism can't be null")
            self.mechanism = unwrapper.unwrapSymbol(element)
        if size > 1:
            element = list.getList()[1]
            if element is not None and not element.isNull():
                self.initialRespone = unwrapper.unwrapBinary(element)
        if size > 2:
            element = list.getList()[2]
            if element is not None and not element.isNull():
                self.hostName = unwrapper.unwrapString(element)

    def toString(self):
        return "SASLInit [mechanism=" + str(self.mechanism) + ", initialResponse=" + str(self.initialResponse) + ", hostName=" + str(self.hostName) + ", code=" + str(self.code) + ", doff=" + str(self.doff) + ", type=" + str(self.type) + ", channel=" + str(self.channel) + "]"

    def setMechanism(self, mechanism):
        self.mechanism = mechanism

    def getMechanism(self):
        return self.mechanism

    def setInitialResponse(self, initialResponse):
        self.initialResponse = initialResponse

    def getInitialResponse(self):
        return self.initialResponse

    def setHostName(self, hostName):
        self.hostName = hostName

    def getHostName(self):
        return self.hostName
