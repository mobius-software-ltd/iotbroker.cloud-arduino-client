import iot.amqp.avps.AMQPType as AMQPType
import iot.amqp.avps.HeaderCode as HeaderCode
import iot.amqp.avps.OutcomeCode as OutcomeCode
import iot.amqp.constructor.DescribedConstructor as DescribedConstructor
import iot.amqp.header.api.AMQPUnwrapper as AMQPUnwrapper
import iot.amqp.header.api.AMQPWrapper as AMQPWrapper
import iot.amqp.tlv.impl.TLVFixed as TLVFixed
import iot.amqp.tlv.impl.TLVList as TLVList

class saslOutcome():
    def __init__(self,code,doff,type,channel,outcomeCode,additionalData):
        self.headerCode = HeaderCode.headerCode()
        self.amqpType = AMQPType.amqpType()

        if code is not None:
            self.code = code
        else:
            self.code = self.headerCode.getValueByKey('OUTCOME')
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
        self.outcomeCode = outcomeCode
        self.additionalData = additionalData

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

        if self.outcomeCode == None:
            print("SASL-Outcome header's code can't be null")
        list.addElement(0,wrapper.wrap(self.outcomeCode.value))

        if self.additionalData is not None:
            list.addElement(1, wrapper.wrap(self.additionalData))

        constructor = DescribedConstructor.describedConstructor(list.getCode(), TLVFixed.tlvFixed(self.amqpType.getValueByKey('SMALL_ULONG'), 0x44))
        list.setConstructor(constructor)
        return list

    def fromArgumentsList(self, list):
        unwrapper = AMQPUnwrapper.amqpUnwrapper()
        size = len(list.getList())
        if size == 0:
            print("Received malformed SASL-Outcome header: code can't be null")
        if size > 2:
            print('Received malformed SASL-Outcome header. Invalid number of arguments: ' + str(size))

        if size > 0:
            element = list.getList()[0]
            if element is None or element.isNull():
                print("Received malformed SASL-Outcome header: code can't be null")
            self.outcomeCode = OutcomeCode.outcomeCode(unwrapper.unwrapUByte(element)).value

        if size > 1:
            element = list.getList()[1]
            if element is not None:
                self.additionalData = unwrapper.unwrapBinary(element)


    def toString(self):
        return "SASLOutcome [outcomeCode=" + str(self.outcomeCode) + ", additionalData=" + str(self.additionalData) + ", code=" + str(self.code) + ", doff=" + str(self.doff) + ", type=" + str(self.type) + ", channel=" + str(self.channel) + "]"

    def setOutcomeCode(self, outcomeCode):
        self.outcomeCode = outcomeCode

    def getOutcomeCode(self):
        return self.outcomeCode

    def setAdditionalData(self, additionalData):
        self.additionalData = additionalData

    def getAdditionalData(self):
        return self.additionalData
