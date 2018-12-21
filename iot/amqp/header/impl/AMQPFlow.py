import iot.amqp.avps.AMQPType as AMQPType
import iot.amqp.avps.HeaderCode as HeaderCode
import iot.amqp.constructor.DescribedConstructor as DescribedConstructor
import iot.amqp.header.api.AMQPUnwrapper as AMQPUnwrapper
import iot.amqp.header.api.AMQPWrapper as AMQPWrapper
import iot.amqp.tlv.impl.TLVFixed as TLVFixed
import iot.amqp.tlv.impl.TLVList as TLVList

class amqpFlow():
    def __init__(self,code,doff,type,channel,nextIncomingId,incomingWindow,nextOutgoingId,outgoingWindow,handle,deliveryCount,linkCredit,available,drain,echo,properties):
        self.headerCode = HeaderCode.headerCode()
        self.amqpType = AMQPType.amqpType()

        if code is not None:
            self.code = code
        else:
            self.code =  self.headerCode.getValueByKey('FLOW')
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

        self.nextIncomingId = nextIncomingId
        self.nextOutgoingId = nextOutgoingId
        self.incomingWindow = incomingWindow
        self.outgoingWindow = outgoingWindow
        self.handle = handle
        self.deliveryCount = deliveryCount
        self.linkCredit = linkCredit
        self.available = available
        self.drain = drain
        self.echo = echo
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
        if self.nextIncomingId is not None:
            list.addElement(0, wrapper.wrap(self.nextIncomingId))
        if self.incomingWindow is None:
            print("Flow header's incoming-window can't be null")
        list.addElement(1, wrapper.wrap(self.incomingWindow))
        if self.nextOutgoingId is None:
            print("Flow header's next-outgoing-id can't be null")
        list.addElement(2, wrapper.wrap(self.nextOutgoingId))
        if self.outgoingWindow is None:
            print("Flow header's outgoing-window can't be null")
        list.addElement(3, wrapper.wrap(self.outgoingWindow))
        if self.handle is not None:
            list.addElement(4, wrapper.wrap(self.handle))
        if self.deliveryCount is not None:
            if self.handle is not None:
                list.addElement(5, wrapper.wrap(self.deliveryCount))
            else:
                print("Flow headers delivery-count can't be assigned when handle is not specified")
        if self.linkCredit is not None:
            if self.handle is not None:
                list.addElement(6, wrapper.wrap(self.linkCredit))
            else:
                print("Flow headers link-credit can't be assigned when handle is not specified")
        if self.available is not None:
            if self.handle is not None:
                list.addElement(7, wrapper.wrap(self.available))
            else:
                print("Flow headers available can't be assigned when handle is not specified")
        if self.drain is not None:
            if self.handle is not None:
                list.addElement(8, wrapper.wrap(self.drain))
            else:
                print("Flow headers drain can't be assigned when handle is not specified")
        if self.echo is not None:
            list.addElement(9,wrapper.wrap(self.echo))
        if self.properties is not None and len(self.properties) > 0:
            list.addElement(10, wrapper.wrapMap(self.properties))

        constructor = DescribedConstructor.describedConstructor(list.getCode(),TLVFixed.tlvFixed(self.amqpType.getValueByKey('SMALL_ULONG'), self.code.value))
        list.setConstructor(constructor)
        return list

    def fromArgumentsList(self, list):
        unwrapper = AMQPUnwrapper.amqpUnwrapper()
        size = len(list.getList())
        if size < 4:
            print('Received malformed Flow header: mandatory fields incoming-window, next-outgoing-id and outgoing-window must not be null')
        if size > 11:
            print('Received malformed Flow header. Invalid number of arguments: ' + str(size))

        if size > 0:
            element = list.getList()[0]
            if element is not None and not element.isNull():
                self.nextIncomingId = unwrapper.unwrapUInt(element)
        if size > 1:
            element = list.getList()[1]
            if element is not None and not element.isNull():
                self.incomingWindow = unwrapper.unwrapUInt(element)
            else:
                print("Received malformed Flow header: incoming-window can't be null")
        if size > 2:
            element = list.getList()[2]
            if element is not None and not element.isNull():
                self.nextOutgoingId = unwrapper.unwrapUInt(element)
            else:
                print("Received malformed Begin header:next-outgoing-id can't be null")
        if size > 3:
            element = list.getList()[3]
            if element is not None and not element.isNull():
                self.outgoingWindow = unwrapper.unwrapUInt(element)
            else:
                print("Received malformed Begin header: outgoing-window can't be null")
        if size > 4:
            element = list.getList()[4]
            if element is not None and not element.isNull():
                self.handle = unwrapper.unwrapUInt(element)
        if size > 5:
            element = list.getList()[5]
            if element is not None:
                if self.handle is not None and not element.isNull():
                    self.deliveryCount = unwrapper.unwrapUInt(element)
                else:
                    print("Received malformed Flow header: delivery-count can't be present when handle is null")
        if size > 6:
            element = list.getList()[6]
            if element is not None:
                if self.handle is not None and not element.isNull():
                    self.linkCredit = unwrapper.unwrapUInt(element)
                else:
                    print("Received malformed Flow header: link-credit can't be present when handle is null")
        if size > 7:
            element = list.getList()[7]
            if element is not None:
                if self.handle is not None and not element.isNull():
                    self.available = unwrapper.unwrapUInt(element)
                else:
                    print("Received malformed Flow header: available can't be present when handle is null")
        if size > 8:
            element = list.getList()[8]
            if element is not None:
                if self.handle is not None and not element.isNull():
                    self.drain = unwrapper.unwrapBool(element)
                else:
                    print("Received malformed Flow header: drain can't be present when handle is null")
        if size > 9:
            element = list.getList()[9]
            if element is not None and not element.isNull():
                self.echo = unwrapper.unwrapBool(element)
        if size > 10:
            element = list.getList()[10]
            if element is not None and not element.isNull():
                self.properties = unwrapper.unwrapMap(element)

    def toString(self):
        return "AMQPFlow [nextIncomingId=" + str(self.nextIncomingId) + ", incomingWindow=" + str(self.incomingWindow) + ", nextOutgoingId=" + str(self.nextOutgoingId) + ", outgoingWindow=" + str(self.outgoingWindow) + ", handle=" + str(self.handle) + ", deliveryCount=" + str(self.deliveryCount) + ", linkCredit=" + str(self.linkCredit) + ", avaliable=" + str(self.avaliable) + ", drain=" + str(self.drain) + ", echo=" + str(self.echo) + ", properties=" + str(self.properties) + ", code=" + str(self.code) + ", doff=" + str(self.doff) + ", type=" + str(self.type) + ", channel=" + str(self.channel) + "]"

    def setNextIncomingId(self, nextIncomingId):
        self.nextIncomingId = nextIncomingId

    def getNextIncomingId(self):
        return self.nextIncomingId

    def setIncomingWindow(self, incomingWindow):
        self.incomingWindow = incomingWindow

    def getIncomingWindow(self):
        return self.incomingWindow

    def setNextOutgoingId(self, nextOutgoingId):
        self.nextOutgoingId = nextOutgoingId

    def getNextOutgoingId(self):
        return self.nextOutgoingId

    def setOutgoingWindow(self, outgoingWindow):
        self.outgoingWindow = outgoingWindow

    def getOutgoingWindow(self):
        return self.outgoingWindow

    def setHandle(self, handle):
        self.handle = handle

    def getHandle(self):
        return self.handle

    def setDeliveryCount(self, deliveryCount):
        self.deliveryCount = deliveryCount

    def getDeliveryCount(self):
        return self.deliveryCount

    def setLinkCredit(self, linkCredit):
        self.linkCredit = linkCredit

    def getLinkCredit(self):
        return self.linkCredit

    def setAvaliable(self, avaliable):
        self.avaliable = avaliable

    def getAvaliable(self):
        return self.avaliable

    def setDrain(self, drain):
        self.drain = drain

    def getDrain(self):
        return self.drain

    def setEcho(self, echo):
        self.echo = echo

    def getEcho(self):
        return self.echo

    def setProperties(self, properties):
        self.properties = properties

    def getProperties(self):
        return self.properties
