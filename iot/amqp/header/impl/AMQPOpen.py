import iot.amqp.avps.AMQPType as AMQPType
import iot.amqp.avps.HeaderCode as HeaderCode
import iot.amqp.constructor.DescribedConstructor as DescribedConstructor
import iot.amqp.header.api.AMQPUnwrapper as AMQPUnwrapper
import iot.amqp.header.api.AMQPWrapper as AMQPWrapper
import iot.amqp.tlv.impl.TLVFixed as TLVFixed
import iot.amqp.tlv.impl.TLVList as TLVList

class amqpOpen():
    def __init__(self,code,doff,type,channel,containerId,hostname,maxFrameSize,channelMax,idleTimeout,outgoingLocales,incomingLocales,offeredCapabilities,desiredCapabilities,properties):
        if code is None:
            self.code = HeaderCode.headerCode.getValueByKey('OPEN')
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

        self.containerId = containerId
        self.hostname = hostname
        self.maxFrameSize = maxFrameSize
        self.channelMax = channelMax
        self.idleTimeout = idleTimeout
        self.outgoingLocales = outgoingLocales
        self.incomingLocales = incomingLocales
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
        if self.containerId is None:
            print("Detach header's container id can't be null")
        list.addElement(0, wrapper.wrap(self.containerId))
        if self.hostname is not None:
            list.addElement(1, wrapper.wrap(self.hostname))
        if self.maxFrameSize is not None:
            list.addElement(2, wrapper.wrap(self.maxFrameSize))
        if self.channelMax is not None:
            list.addElement(3, wrapper.wrap(self.channelMax))
        if self.idleTimeout is not None:
            list.addElement(4, wrapper.wrap(self.idleTimeout))
        if self.outgoingLocales is not None and len(self.outgoingLocales) > 0:
            list.addElement(5, wrapper.wrapArray(self.outgoingLocales))
        if self.incomingLocales is not None and len(self.incomingLocales) > 0:
            list.addElement(6, wrapper.wrapArray(self.incomingLocales))
        if self.offeredCapabilities is not None and len(self.offeredCapabilities) > 0:
            list.addElement(7, wrapper.wrapArray(self.offeredCapabilities))
        if self.desiredCapabilities is not None and len(self.desiredCapabilities) > 0:
            list.addElement(8, wrapper.wrapArray(self.desiredCapabilities))
        if self.properties is not None and len(self.properties) > 0:
            list.addElement(9, wrapper.wrapMap(self.properties))

        constructor = DescribedConstructor.describedConstructor(list.getCode(),TLVFixed.tlvFixed(AMQPType.amqpType.getValueByKey('SMALL_ULONG'), self.code.value))
        list.setConstructor(constructor)
        return list

    def fromArgumentsList(self, list):
        unwrapper = AMQPUnwrapper.amqpUnwrapper()
        size = len(list.getList())
        if size  == 0:
            print("Received malformed Open header: container id can't be null")
        if size > 10:
            print("Received malformed Open header. Invalid number of arguments: " + str(size))

        element = list.getList()[0]

        if element is None:
            print("Received malformed Open header: container id can't be null")
        self.containerId = unwrapper.unwrapString(element)

        if size > 1:
            element = list.getList()[1]
            if element is not None and not element.isNull():
                self.hostname = unwrapper.unwrapString(element)
        if size > 2:
            element = list.getList()[2]
            if element is not None and not element.isNull():
                self.maxFrameSize = unwrapper.unwrapUInt(element) 
        if size > 3:
            element = list.getList()[3]
            if element is not None and not element.isNull():
                self.channelMax = unwrapper.unwrapUShort(element)
        if size > 4:
            element = list.getList()[4]
            if element is not None and not element.isNull():
                self.idleTimeout = unwrapper.unwrapUInt(element)
        if size > 5:
            element = list.getList()[5]
            if element is not None and not element.isNull():
                self.outgoingLocales = unwrapper.unwrapArray(element)
        if size > 6:
            element = list.getList()[6]
            if element is not None and not element.isNull():
                self.incomingLocales = unwrapper.unwrapArray(element)
        if size > 7:
            element = list.getList()[7]
            if element is not None and not element.isNull():
                self.offeredCapabilities = unwrapper.unwrapArray(element)
        if size > 8:
            element = list.getList()[8]
            if element is not None and not element.isNull():
                self.desiredCapabilities = unwrapper.unwrapArray(element)
        if size > 9:
            element = list.getList()[9]
            if element is not None and not element.isNull():
                self.properties = unwrapper.unwrapMap(element)

    def toString(self):
        return "AMQPOpen [containerId=" + str(self.containerId) + ", hostname=" + str(self.hostname) + ", maxFrameSize=" + str(self.maxFrameSize) + ", channelMax=" + str(self.channelMax) + ", idleTimeout=" + str(self.idleTimeout) + ", outgoingLocales=" + str(self.outgoingLocales) + ", incomingLocales=" + str(self.incomingLocales) + ", offeredCapabilities=" + str(self.offeredCapabilities) + ", desiredCapabilities=" + str(self.desiredCapabilities) + ", properties=" + str(self.properties) + ", code=" + str(self.code) + ", doff=" + str(self.doff) + ", type=" + str(self.type) + ", channel=" + str(self.channel) + "]"

    def setContainerId(self, containerId):
        self.containerId = containerId

    def getContainerId(self):
        return self.containerId

    def setHostname(self, hostname):
        self.hostname = hostname

    def getHostname(self):
        return self.hostname

    def setMaxFrameSize(self, maxFrameSize):
        self.maxFrameSize = maxFrameSize

    def getMaxFrameSize(self):
        return self.maxFrameSize

    def setChannelMax(self, channelMax):
        self.channelMax = channelMax

    def getChannelMax(self):
        return self.channelMax

    def setIdleTimeout(self, idleTimeout):
        self.idleTimeout = idleTimeout

    def getIdleTimeout(self):
        return self.idleTimeout

    def setOutgoingLocales(self, outgoingLocales):
        self.outgoingLocales = outgoingLocales

    def getOutgoingLocales(self):
        return self.outgoingLocales

    def setIncomingLocales(self, incomingLocales):
        self.incomingLocales = incomingLocales

    def getIncomingLocales(self):
        return self.incomingLocales

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
