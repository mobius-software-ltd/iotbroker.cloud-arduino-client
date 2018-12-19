import iot.amqp.avps.AMQPType as AMQPType
import iot.amqp.avps.HeaderCode as HeaderCode
import iot.amqp.constructor.DescribedConstructor as DescribedConstructor
import iot.amqp.header.api.AMQPUnwrapper as AMQPUnwrapper
import iot.amqp.header.api.AMQPWrapper as AMQPWrapper
import iot.amqp.tlv.impl.TLVFixed as TLVFixed
import iot.amqp.tlv.impl.TLVList as TLVList

class saslChallenge():
    def __init__(self,code,doff,type,channel,challenge):
        if code is not None:
            self.code = code
        else:
            self.code = HeaderCode.headerCode.getValueByKey('CHALLENGE')
        if doff is not None:
            self.doff = doff
        else:
            self.doff = 2
        if type is not None:
            self.type = type
        else:
            self.type = 1
        if channel is not None:
            self.channel = channel
        else:
            self.channel = 0
        self.challenge = challenge

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

        if self.challenge == None:
            print("SASL-Challenge header's challenge can't be null")
        list.addElement(0,AMQPWrapper.amqpWrapper.wrap(self.challenge))

        constructor = DescribedConstructor.describedConstructor(list.getCode(), TLVFixed.tlvFixed(AMQPType.amqpType.getValueByKey('SMALL_ULONG'), 0x42))
        list.setConstructor(constructor)
        return list

    def fromArgumentsList(self, list):
        size = len(list.getList())
        if size == 0:
            print("Received malformedSASL-Challenge header: challenge can't be null")
        if size > 1:
            print('Received malformed SASL-Challenge header. Invalid number of arguments: ' + str(size))
        if size > 0:
            element = list.getList()[0]
            if element is None or element.isNull():
                print("Received malformed SASL-Challenge header: challenge can't be null")
            self.challenge = AMQPUnwrapper.amqpUnwrapper.unwrapBinary(element)


    def toString(self):
        return "SASLChallenge [challenge=" + str(self.challenge) + ", code=" + str(self.code) + ", doff=" + str(self.doff) + ", type=" + str(self.type) + ", channel=" + str(self.channel) + "]"

    def setChallenge(self, challenge):
        self.challenge = challenge

    def getChallenge(self):
        return self.challenge
