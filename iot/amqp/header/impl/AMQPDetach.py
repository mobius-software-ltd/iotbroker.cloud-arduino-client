import iot.amqp.avps.AMQPType as AMQPType
import iot.amqp.avps.HeaderCode as HeaderCode
import iot.amqp.constructor.DescribedConstructor as DescribedConstructor
import iot.amqp.header.api.AMQPUnwrapper as AMQPUnwrapper
import iot.amqp.header.api.AMQPWrapper as AMQPWrapper
import iot.amqp.tlv.impl.TLVFixed as TLVFixed
import iot.amqp.tlv.impl.TLVList as TLVList
import iot.amqp.tlv.impl.AMQPError as AMQPError

class amqpDetach():
    def __init__(self,code,doff,type,channel,handle,closed,error):
        if code is not None:
            self.code = code
        else:
            self.code = HeaderCode.headerCode.getValueByKey('DETACH')
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
        self.closed = closed
        self.error = error
    
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
        if self.handle is None:
            print("Detach header's handle can't be null")
        list.addElement(0, wrapper.wrap(self.handle))
        if self.closed is not None:
            list.addElement(1, wrapper.wrap(self.closed))
        if self.error is not None:
            list.addElement(2, self.error.toArgumentsList())

        constructor = DescribedConstructor.describedConstructor(list.getCode(),TLVFixed.tlvFixed(AMQPType.amqpType.getValueByKey('SMALL_ULONG'), self.code.value))
        list.setConstructor(constructor)
        return list

    def fromArgumentsList(self, list):
        unwrapper = AMQPUnwrapper.amqpUnwrapper()
        size = len(list.getList())
        if size  == 0:
            print("Received malformed Detach header: handle can't be null")
        if size > 3:
            print("Received malformed Detach header. Invalid number of arguments: " + str(size))
        if size > 0:
            element = list.getList()[0]
            if element is None and not element.isNull():
                print("Received malformed Detach header: handle can't be null")
            self.handle = unwrapper.unwrapUInt(element)
        if size > 1:
            element = list.getList()[1]
            if element is not None and not element.isNull():
                self.closed = unwrapper.unwrapBool(element)
        if size > 2:
            element = list.getList()[2]
            if element is not None and not element.isNull():
                code = element.getCode()
                if code not in (AMQPType.amqpType.getValueByKey('LIST_0'),AMQPType.amqpType.getValueByKey('LIST_8'),AMQPType.amqpType.getValueByKey('LIST_32')):
                    print("Expected type 'ERROR' - received: " + str(element.getCode()))
                self.error = AMQPError.amqpError(None, None, None)
                self.error.fromArgumentsList(element)


    def toString(self):
        return "AMQPDetach [handle=" + str(self.handle) + ", closed=" + str(self.closed) + ", error=" + str(self.error) + ", code=" + str(self.code) + ", doff=" + str(self.doff) + ", type=" + str(self.type) + ", channel=" + str(self.channel) + "]"

    def setHandle(self, handle):
        self.handle = handle

    def getHandle(self):
        return self.handle

    def setClosed(self, closed):
        self.closed = closed

    def getClosed(self):
        return self.closed

    def setError(self, error):
        self.error = error

    def getError(self):
        return self.error
