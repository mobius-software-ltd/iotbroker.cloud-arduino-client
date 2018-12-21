import iot.amqp.avps.AMQPType as AMQPType
import iot.amqp.avps.HeaderCode as HeaderCode
import iot.amqp.constructor.DescribedConstructor as DescribedConstructor
import iot.amqp.header.api.AMQPUnwrapper as AMQPUnwrapper
import iot.amqp.header.api.AMQPWrapper as AMQPWrapper
import iot.amqp.tlv.impl.TLVFixed as TLVFixed
import iot.amqp.tlv.impl.TLVList as TLVList

class amqpBegin():
    def __init__(self,code,doff,type,channel,remoteChannel,nextOutgoingId,incomingWindow,outgoingWindow,handleMax,offeredCapabilities,desiredCapabilities,properties):
        self.headerCode = HeaderCode.headerCode()
        self.amqpType = AMQPType.amqpType() 

        if code is None:
            self.code = self.headerCode.getValueByKey('BEGIN')
        else:
            self.code = code

        if doff is not None:
            self.doff = doff
        else:
            self.doff = 2

        if type is not None:
            self.type = type
        else:
            self.type = 0

        if channel is not None:
            self.channel = channel
        else:
            self.channel = 0

        self.remoteChannel = remoteChannel
        self.nextOutgoingId = nextOutgoingId
        self.incomingWindow = incomingWindow
        self.outgoingWindow = outgoingWindow
        self.handleMax = handleMax
        self.offeredCapabilities = offeredCapabilities
        self.desiredCapabilities = desiredCapabilities
        self.properties = properties
     
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
        if self.remoteChannel is not None:
            list.addElement(0, wrapper.wrap(self.remoteChannel))
        if self.nextOutgoingId is None:
            print("Begin header's next-outgoing-id can't be null")
        list.addElement(1, wrapper.wrap(self.nextOutgoingId))
        if self.incomingWindow is None:
            print("Begin header's incoming-window can't be null")
        list.addElement(2, wrapper.wrap(self.incomingWindow))
        if self.outgoingWindow is None:
            print("Begin header's outgoing-window can't be null")
        list.addElement(3, wrapper.wrap(self.outgoingWindow))
        if self.handleMax is not None:
            list.addElement(4, wrapper.wrap(self.handleMax))
        if self.offeredCapabilities is not None and len(self.offeredCapabilities) > 0:
            list.addElement(5, wrapper.wrapArray(self.offeredCapabilities))
        if self.desiredCapabilities is not None and len(self.desiredCapabilities) > 0:
            list.addElement(6, wrapper.wrapArray(self.desiredCapabilities))
        if self.properties is not None and len(self.properties) > 0:
            list.addElement(7, wrapper.wrapMap(self.properties))

        constructor = DescribedConstructor.describedConstructor(list.getCode(),TLVFixed.tlvFixed(self.amqpType.getValueByKey('SMALL_ULONG'), self.code.value))
        list.setConstructor(constructor)
        return list

    def fromArgumentsList(self, list):
        unwrapper = AMQPUnwrapper.amqpUnwrapper()
        size = len(list.getList())
        if size < 4:
            print('Received malformed Begin header: mandatory fields next-outgoing-id, incoming-window and outgoing-window must not be null')
        if size > 8:
            print('Received malformed Begin header. Invalid number of arguments: ' + str(size))
        if size > 0:
            element = list.getList()[0]
            if element is not None and not element.isNull():
                self.remoteChannel = unwrapper.unwrapUShort(element)
        if size > 1:
            element = list.getList()[1]
            if element is not None and not element.isNull():
                self.nextOutgoingId = unwrapper.unwrapUInt(element)
            else:
                print("Received malformed Begin header: next-outgoing-id can't be null")
        if size > 2:
            element = list.getList()[2]
            if element is not None and not element.isNull():
                self.incomingWindow = unwrapper.unwrapUInt(element)
            else:
                print("Received malformed Begin header: incoming-window can't be null")
        if size > 3:
            element = list.getList()[3]
            if element is not None and not element.isNull():
                self.outgoingWindow = unwrapper.unwrapUInt(element)
            else:
                print("Received malformed Begin header: outgoing-window can't be null")
        if size > 4:
            element = list.getList()[4]
            if element is not None and not element.isNull():
                self.handleMax = unwrapper.unwrapUInt(element)
        if size > 5:
            element = list.getList()[5]
            if element is not None and not element.isNull():
                self.offeredCapabilities = unwrapper.unwrapArray(element)
        if size > 6:
            element = list.getList()[6]
            if element is not None and not element.isNull():
                self.desiredCapabilities = unwrapper.unwrapArray(element)
        if size > 7:
            element = list.getList()[7]
            if element is not None and not element.isNull():
                self.properties = unwrapper.unwrapMap(element)

    def toString(self):
        return "AMQPBegin [remoteChannel=" + str(self.remoteChannel) + ", nextOutgoingId=" + str(self.nextOutgoingId) + ", incomingWindow=" + str(self.incomingWindow) + ", outgoingWindow=" + str(self.outgoingWindow) + ", handleMax=" + str(self.handleMax) + ", offeredCapabilities=" + str(self.offeredCapabilities) + ", desiredCapabilities=" + str(self.desiredCapabilities) + ", properties=" + str(self.properties) + ", code=" + str(self.code) + ", doff=" + str(self.doff) + ", type=" + str(self.type) + ", channel=" + str(self.channel) + "]"

    def setRemoteChannel(self, remoteChannel):
        self.remoteChannel = remoteChannel

    def getRemoteChannel(self):
        return self.remoteChannel

    def setNextOutgoingId(self, nextOutgoingId):
        self.nextOutgoingId = nextOutgoingId

    def getNextOutgoingId(self):
        return self.nextOutgoingId

    def setIncomingWindow(self, incomingWindow):
        self.incomingWindow = incomingWindow

    def getIncomingWindow(self):
        return self.incomingWindow

    def setOutgoingWindow(self, outgoingWindow):
        self.outgoingWindow = outgoingWindow

    def getOutgoingWindow(self):
        return self.outgoingWindow

    def setHandleMax(self, handleMax):
        self.handleMax = handleMax

    def getHandleMax(self):
        return self.handleMax

    def setOfferedCapabilities(self, offeredCapabilities):
        self.offeredCapabilities = offeredCapabilities

    def getOfferedCapabilities(self):
        return self.offeredCapabilities

    def setDesiredCapabilities(self, desiredCapabilities):
        self.desiredCapabilities = desiredCapabilities

    def getDesiredCapabilities(self):
        return self.desiredCapabilities

    def setProperties(self, properties):
        self.properties = properties

    def getProperties(self):
        return self.properties
