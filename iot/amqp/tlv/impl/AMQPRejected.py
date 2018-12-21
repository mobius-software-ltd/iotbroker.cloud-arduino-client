import iot.amqp.avps.AMQPType as AMQPType
import iot.amqp.constructor.DescribedConstructor as DescribedConstructor
import iot.amqp.header.api.AMQPUnwrapper as AMQPUnwrapper
import iot.amqp.header.api.AMQPWrapper as AMQPWrapper
import iot.amqp.tlv.impl.TLVList as TLVList
import iot.amqp.tlv.impl.TLVFixed as TLVFixed
import iot.amqp.tlv.impl.AMQPError as AMQPError

class amqpRejected():
    def __init__(self, error):
        self.error = error
        self.amqpType = AMQPType.amqpType()

    def toArgumentsList(self):
        list = TLVList.tlvList(None,None)
        if self.error is not None:
            list.addElement(0, self.error.toArgumentsList())

        constructor = DescribedConstructor.describedConstructor(list.getCode(),TLVFixed.tlvFixed(self.amqpType.getValueByKey('SMALL_ULONG'), 0x25))
        list.setConstructor(constructor)
        return list

    def fromArgumentsList(self, list):
        if len(list.getList()) > 0 :
            element = list.getList()[0]
            if element is not None:
                code = element.getCode()
                if code not in (self.amqpType.getValueByKey('LIST_0'),self.amqpType.getValueByKey('LIST_8'),self.amqpType.getValueByKey('LIST_32')):
                    print('Expected type Error received ' + str(element.getCode()))
                self.error = AMQPError.amqpError(None, None, None)
                self.error.fromArgumentsList(element)

    def toString(self):
        return 'AMQPRejected [error='+ str(self.error) + ']'

    def getError(self):
        return self.error

    def setError(self, error):
        self.error = error
    
    def isNull(self):
        return False
