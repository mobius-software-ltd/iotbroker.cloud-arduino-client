import iot.amqp.avps.AMQPType as AMQPType
import iot.amqp.constructor.DescribedConstructor as DescribedConstructor
import iot.amqp.tlv.impl.TLVList as TLVList
import iot.amqp.tlv.impl.TLVFixed as TLVFixed

class amqpAccepted():
    def __init__(self):
        self.amqpType = AMQPType.amqpType()

    def toArgumentsList(self):
        list = TLVList.tlvList(None,None);
        constructor = DescribedConstructor.describedConstructor(list.getCode(),TLVFixed.tlvFixed(self.amqpType.getValueByKey('SMALL_ULONG'), 0x24))
        list.setConstructor(constructor)
        return list

    def fromArgumentsList(self, list):
        pass

    def toString(self):
        return 'AMQPAccepted []'

    def isNull(self):
        return False
