import iot.amqp.avps.AMQPType as AMQPType
import iot.amqp.avps.LifetimePolicy as LifetimePolicy
import iot.amqp.constructor.DescribedConstructor as DescribedConstructor
import iot.amqp.tlv.impl.TLVList as TLVList
import iot.amqp.tlv.impl.TLVFixed as TLVFixed

class amqpLifetimePolicy():
    def __init__(self, code):
        self.code = code
        self.amqpType = AMQPType.amqpType()

    def getList(self):
        list = TLVList.tlvList(None, None)
        constructor = DescribedConstructor.describedConstructor(list.getCode(), TLVFixed.tlvFixed(self.amqpType.getValueByKey('SMALL_ULONG'), self.code.value))
        list.setConstructor(constructor)
        return list

    def fill(self,list):
        if list is not None:
            constructor = list.getConstructor()
            self.code = LifetimePolicy.lifetimePolicy(constructor.getDescriptorCode() & 0xff).value

    def getCode(self):
        return self.code

    def isNull(self):
        return False
