import iot.amqp.avps.AMQPType as AMQPType
import iot.amqp.avps.HeaderCode as HeaderCode
import iot.amqp.avps.ReceiveCode as ReceiveCode
import iot.amqp.avps.SectionCode as SectionCode
import iot.amqp.constructor.DescribedConstructor as DescribedConstructor
import iot.amqp.header.api.AMQPUnwrapper as AMQPUnwrapper
import iot.amqp.header.api.AMQPWrapper as AMQPWrapper
import iot.amqp.header.api.HeaderFactoryOutcome as HeaderFactoryOutcome
import iot.amqp.tlv.impl.TLVFixed as TLVFixed
import iot.amqp.tlv.impl.TLVList as TLVList
import iot.amqp.wrappers.AMQPMessageFormat as AMQPMessageFormat

class amqpTransfer():
    def __init__(self,code,doff,type,channel,handle,deliveryId,deliveryTag,messageFormat,settled,more,rcvSettleMode,state,resume,aborted,batchable,sections):
        if code is not None:
            self.code = code
        else:
            self.code = HeaderCode.headerCode.getValueByKey('TRANSFER')
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

        self.handle = handle
        self.deliveryId = deliveryId
        self.deliveryTag = deliveryTag
        self.messageFormat = messageFormat
        self.settled = settled
        self.more = more
        self.rcvSettleMode = rcvSettleMode
        self.state = state
        self.resume = resume
        self.aborted = aborted
        self.batchable = batchable
        self.sections = sections

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
        if self.handle == None:
            print("Transfer header's handle can't be null")
        list.addElement(0,wrapper.wrap(self.handle))
        if self.deliveryId is not None:
            list.addElement(1, wrapper.wrap(self.deliveryId))
        if self.deliveryTag is not None:
            list.addElement(2, wrapper.wrap(self.deliveryTag))
        if self.messageFormat is not None:
            list.addElement(3, wrapper.wrap(self.messageFormat.encode()))
        if self.settled is not None:
            list.addElement(4, wrapper.wrap(self.settled))
        if self.more is not None:
            list.addElement(5, wrapper.wrap(self.more))
        if self.rcvSettleMode is not None:
            list.addElement(6, wrapper.wrap(self.rcvSettleMode.value))
        if self.state is not None:
            list.addElement(7, wrapper.wrap(self.state.toArgumentsList()))
        if self.resume is not None:
            list.addElement(8, wrapper.wrap(self.resume))
        if self.aborted is not None:
            list.addElement(9, wrapper.wrap(self.aborted))
        if self.batchable is not None:
            list.addElement(10, wrapper.wrap(self.batchable))

        constructor = DescribedConstructor.describedConstructor(list.getCode(),TLVFixed.tlvFixed(AMQPType.amqpType.getValueByKey('SMALL_ULONG'), self.code.value))
        list.setConstructor(constructor)
        return list

    def fromArgumentsList(self, list):
        unwrapper = AMQPUnwrapper.amqpUnwrapper()
        size = len(list.getList())
        if size == 0:
            print("Received malformed Transfer header: handle can't be null")
        if size > 11:
            print('Received malformed Transfer header. Invalid number of arguments: ' + str(size))
        if size > 0:
            element = list.getList()[0]
            if element is None and not element.isNull():
                print("Received malformed Transfer header: handle can't be null")
            self.handle = unwrapper.unwrapUInt(element)
        if size > 1:
            element = list.getList()[1]
            if element is not None and not element.isNull():
                self.deliveryId = unwrapper.unwrapUInt(element)
        if size > 2:
            element = list.getList()[2]
            if element is not None and not element.isNull():
                self.deliveryTag = unwrapper.unwrapBinary(element)
        if size > 3:
            element = list.getList()[3]
            if element is not None and not element.isNull():
                self.messageFormat = AMQPMessageFormat.amqpMessageFormat(unwrapper.unwrapUInt(element))
        if size > 4:
            element = list.getList()[4]
            if element is not None and not element.isNull():
                self.settled = unwrapper.unwrapBool(element)
        if size > 5:
            element = list.getList()[5]
            if element is not None and not element.isNull():
                self.more = unwrapper.unwrapBool(element)
        if size > 6:
            element = list.getList()[6]
            if element is not None and not element.isNull():
                self.rcvSettleMode = ReceiveCode.receiveCode(unwrapper.unwrapUByte(element))
        if size > 7:
            element = list.getList()[7]
            if element is not None and not element.isNull():
                code = element.getCode()
                if code not in (AMQPType.amqpType.getValueByKey('LIST_0'),AMQPType.amqpType.getValueByKey('LIST_8'),AMQPType.amqpType.getValueByKey('LIST_32')):
                    print("Expected type 'STATE' - received: " + str(element.getCode()))
                self.state = HeaderFactoryOutcome.headerFactoryOutcome.getState(element)
                self.state.fromArgumentsList(element)
        if size > 8:
            element = list.getList()[8]
            if element is not None and not element.isNull():
                self.resume = unwrapper.unwrapBool(element)
        if size > 9:
            element = list.getList()[9]
            if element is not None and not element.isNull():
                self.aborted = unwrapper.unwrapBool(element)
        if size > 10:
            element = list.getList()[10]
            if element is not None and not element.isNull():
                self.batchable = unwrapper.unwrapBool(element)

    def toString(self):
        return "AMQPTransfer [handle=" + str(self.handle) + ", deliveryId=" + str(self.deliveryId) + ", deliveryTag=" + str(self.deliveryTag) + ", messageFormat=" + str(self.messageFormat) + ", settled=" + str(self.settled) + ", more=" + str(self.more) + ", rcvSettleMode=" + str(self.rcvSettleMode) + ", state=" + str(self.state) + ", resume=" + str(self.resume) + ", aborted=" + str(self.aborted) + ", batchable=" + str(self.batchable) + ", sections=" + str(self.sections) + ", code=" + str(self.code) + ", doff=" + str(self.doff) + ", type=" + str(self.type) + ", channel=" + str(self.channel) + "]"

    def setHandle(self, handle):
        self.handle = handle

    def getHandle(self):
        return self.handle

    def setDeliveryId(self, deliveryId):
        self.deliveryId = deliveryId

    def getDeliveryId(self):
        return self.deliveryId

    def setDeliveryTag(self, deliveryTag):
        self.deliveryTag = deliveryTag

    def getDeliveryTag(self):
        return self.deliveryTag

    def setMessageFormat(self, messageFormat):
        self.messageFormat = messageFormat

    def getMessageFormat(self):
        return self.messageFormat

    def setSettled(self, settled):
        self.settled = settled

    def getSettled(self):
        return self.settled

    def setMore(self, more):
        self.more = more

    def getMore(self):
        return self.more

    def setRcvSettleMode(self, rcvSettleMode):
        self.rcvSettleMode = rcvSettleMode

    def getRcvSettleMode(self):
        return self.rcvSettleMode

    def setState(self, state):
        self.state = state

    def getState(self):
        return self.state

    def setResume(self, resume):
        self.resume = resume

    def getResume(self):
        return self.resume

    def setAborted(self, aborted):
        self.aborted = aborted

    def getAborted(self):
        return self.aborted

    def setBatchable(self, batchable):
        self.batchable = batchable

    def getBatchable(self):
        return self.batchable

    def setSections(self, sections):
        self.sections = sections

    def getSections(self):
        return self.sections

    def getHeader(self):
        if self.sections is not None:
            return self.sections[SectionCode.sectionCode.getValueByKey('HEADER')]
        else:
            return None

    def getDeliveryAnnotations(self):
        if self.sections is not None:
            return self.sections[SectionCode.sectionCode.getValueByKey('DELIVERY_ANNOTATIONS')]
        else:
            return None

    def getMessageAnnotations(self):
        if self.sections is not None:
            return self.sections[SectionCode.sectionCode.getValueByKey('MESSAGE_ANNOTATIONS')]
        else:
            return None

    def getProperties(self):
        if self.sections is not None:
            return self.sections[SectionCode.sectionCode.getValueByKey('PROPERTIES')]
        else:
            return None

    def getApplicationProperties(self):
        if self.sections is not None:
            return self.sections[SectionCode.sectionCode.getValueByKey('APPLICATION_PROPERTIES')]
        else:
            return None

    def getData(self):
        if self.sections is not None:
            return self.sections[SectionCode.sectionCode.getValueByKey('DATA')]
        else:
            return None

    def getSequence(self):
        if self.sections is not None:
            return self.sections[SectionCode.sectionCode.getValueByKey('SEQUENCE')]
        else:
            return None

    def getValue(self):
        if self.sections is not None:
            return self.sections[SectionCode.sectionCode.getValueByKey('VALUE')]
        else:
            return None

    def getFooter(self):
        if self.sections is not None:
            return self.sections[SectionCode.sectionCode.getValueByKey('FOOTER')]
        else:
            return None
