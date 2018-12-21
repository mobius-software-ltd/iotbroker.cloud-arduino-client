import iot.amqp.avps.AMQPType as AMQPType
import iot.amqp.constructor.DescribedConstructor as DescribedConstructor
import iot.amqp.tlv.impl.TLVList as TLVList
import iot.amqp.tlv.impl.TLVFixed as TLVFixed

class amqpReleased():
    def __init__(self):
        self.amqpType = AMQPType.amqpType()

    def toArgumentsList(self):
        list = TLVList.tlvList(None,None)
        constructor = DescribedConstructor.describedConstructor(list.getCode(),TLVFixed.tlvFixed(self.amqpType.getValueByKey('SMALL_ULONG'), 0x26))
        list.setConstructor(constructor)
        return list

    def fromArgumentsList(self, list):
        pass

    def toString(self):
        return 'AMQPReleased []'

    def getError(self):
        return self.error

    def setError(self, error):
        self.error = error
