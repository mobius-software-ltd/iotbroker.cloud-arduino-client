import iot.amqp.avps.AMQPType as AMQPType
import iot.amqp.avps.HeaderCode as HeaderCode
import iot.amqp.constructor.DescribedConstructor as DescribedConstructor
import iot.amqp.header.api.AMQPUnwrapper as AMQPUnwrapper
import iot.amqp.header.api.AMQPWrapper as AMQPWrapper
import iot.amqp.header.api.HeaderFactoryOutcome as HeaderFactoryOutcome
import iot.amqp.tlv.impl.TLVFixed as TLVFixed
import iot.amqp.tlv.impl.TLVList as TLVList

class amqpDisposition():
    def __init__(self,code,doff,type,channel,role,first,last,settled,state,batchable):
        if code is not None:
            self.code = code
        else:
            self.code = HeaderCode.headerCode.getValueByKey('DISPOSITION')
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
        self.role = role
        self.first = first
        self.last = last
        self.settled = settled
        self.state = state
        self.batchable = batchable
    
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
        if self.role is None:
            print("Disposition header's role can't be null")
        list.addElement(0, wrapper.wrap(self.role.value))
        if self.first is None:
            print("Disposition header's first can't be null")
        list.addElement(1, wrapper.wrap(self.first))
        if self.last is not None:
            list.addElement(2, wrapper.wrap(self.last))
        if self.settled is not None:
            list.addElement(3, wrapper.wrap(self.settled))
        if self.state is not None:
            list.addElement(4, self.state.toArgumentsList())
        if self.batchable is not None and len(self.outgoingLocales) > 0:
            list.addElement(5, wrapper.wrap(self.batchable))

        constructor = DescribedConstructor.describedConstructor(list.getCode(),TLVFixed.tlvFixed(AMQPType.amqpType.getValueByKey('SMALL_ULONG'), self.code.value))
        list.setConstructor(constructor)
        return list

    def fromArgumentsList(self, list):
        unwrapper = AMQPUnwrapper.amqpUnwrapper()
        size = len(list.getList())
        if size  < 2:
            print("Received malformed Disposition header: role and first can't be null")
        if size > 6:
            print("Received malformed Disposition header. Invalid number of arguments: " + str(size))

        if size > 0:
            element = list.getList()[0]
            if element is None and not element.isNull():
                print("Received malformed Disposition header: role can't be null")
            self.role = unwrapper.unwrapBool(element)
        if size > 1:
            element = list.getList()[1]
            if element is None and not element.isNull():
                print("Received malformed Disposition header: first can't be null")
            self.first = unwrapper.unwrapUInt(element)
        if size > 2:
            element = list.getList()[2]
            if element is not None and not element.isNull():
                self.last = unwrapper.unwrapUInt(element)
        if size > 3:
            element = list.getList()[3]
            if element is not None and not element.isNull():
                self.settled = unwrapper.unwrapBool(element)
        if size > 4:
            element = list.getList()[4]
            if element is not None and not element.isNull():
                code  = element.getCode()
                if code not in (AMQPType.amqpType.getValueByKey('LIST_0'),AMQPType.amqpType.getValueByKey('LIST_8'),AMQPType.amqpType.getValueByKey('LIST_32')):
                    print('Expected type STATE - received: ' + str(element.getCode()))
                self.state = HeaderFactoryOutcome.headerFactoryOutcome.getState(element)
                self.state.fromArgumentsList(element)
        if size > 5:
            element = list.getList()[5]
            if element is not None and not element.isNull():
                self.batchable = unwrapper.unwrapBool(element)

    def toString(self):
        return "AMQPDisposition [role=" + str(self.role) + ", first=" + str(self.first) + ", last=" + str(self.last) + ", settled=" + str(self.settled) + ", state=" + str(self.state) + ", batchable=" + str(self.batchable) + ", code=" + str(self.code) + ", doff=" + str(self.doff) + ", type=" + str(self.type) + ", channel=" + str(self.channel) + "]"

    def setRole(self, role):
        self.role = role

    def getRole(self):
        return self.role

    def setFirst(self, first):
        self.first = first

    def getFirst(self):
        return self.first

    def setLast(self, last):
        self.last = last

    def getLast(self):
        return self.last

    def setSettled(self, settled):
        self.settled = settled

    def getSettled(self):
        return self.settled

    def setState(self, state):
        self.state = state

    def getState(self):
        return self.state

    def setBatchable(self, batchable):
        self.batchable = batchable

    def getBatchable(self):
        return self.batchable
