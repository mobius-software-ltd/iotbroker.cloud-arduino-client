import iot.amqp.avps.AMQPType as AMQPType
import iot.amqp.avps.HeaderCode as HeaderCode
import iot.amqp.constructor.DescribedConstructor as DescribedConstructor
import iot.amqp.tlv.impl.TLVFixed as TLVFixed
import iot.amqp.tlv.impl.TLVList as TLVList
import iot.amqp.tlv.impl.TLVNull as TLVNull
import iot.amqp.tlv.impl.AMQPError as AMQPError

class amqpClose():
    def __init__(self,code,doff,type,channel,error):
        if code is not None:
            self.code = code
        else:
            self.code = HeaderCode.headerCode.getValueByKey('CLOSE')
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

        if self.error is not None:
            list.addElement(0, self.error.toArgumentsList())
        else:
            list.addElement(0, TLVNull.tlvNull())

        constructor = DescribedConstructor.describedConstructor(list.getCode(),TLVFixed.tlvFixed(AMQPType.amqpType.getValueByKey('SMALL_ULONG'), self.code.value))
        list.setConstructor(constructor)
        return list

    def fromArgumentsList(self, list):
        size = len(list.getList())
        if size > 0:
            element = list.getList()[0]
            if element is not None and element.isNull() != True:
                code = element.getCode()
                if code not in (AMQPType.amqpType.getValueByKey('LIST_0'),AMQPType.amqpType.getValueByKey('LIST_8'),AMQPType.amqpType.getValueByKey('LIST_32')):
                    print("Expected type 'ERROR' - received: " + str(element.getCode()))
                self.error = AMQPError.amqpError(None,None,None)
                self.error.fromArgumentsList(element)

    def toString(self):
        return "AMQPClose [error=" + str(self.error) + ", code=" + str(self.code) + ", doff=" + str(self.doff) + ", type=" + str(self.type) + ", channel=" + str(self.channel) + "]"

    def setError(self, error):
        self.error = error

    def getError(self):
        return self.error
