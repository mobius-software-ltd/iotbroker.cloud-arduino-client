import iot.amqp.avps.AMQPType as AMQPType
import iot.amqp.avps.HeaderCode as HeaderCode
import iot.amqp.constructor.DescribedConstructor as DescribedConstructor
import iot.amqp.header.api.AMQPUnwrapper as AMQPUnwrapper
import iot.amqp.header.api.AMQPWrapper as AMQPWrapper
import iot.amqp.tlv.impl.TLVFixed as TLVFixed
import iot.amqp.tlv.impl.TLVList as TLVList
from crypto.hash import md5 as md5

class saslResponse():
    def __init__(self,code,doff,type,channel,response):
        self.headerCode = HeaderCode.headerCode()
        self.amqpType = AMQPType.amqpType()

        if code is not None:
            self.code = code
        else:
            self.code = self.headerCode.getValueByKey('RESPONSE')
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
        self.response = response
        
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
        if self.response == None:
            print("SASL-Response header's challenge can't be null")
        list.addElement(0,wrapper.wrap(self.response))

        constructor = DescribedConstructor.describedConstructor(list.getCode(), TLVFixed.tlvFixed(self.amqpType.getValueByKey('SMALL_ULONG'), 0x43))
        list.setConstructor(constructor)
        return list

    def fromArgumentsList(self, list):
        size = len(list.getList())
        unwrapper = AMQPUnwrapper.amqpUnwrapper()
        if size == 0:
            print("Received malformed SASL-Response header: challenge can't be null")
        if size > 1:
            print('Received malformed SASL-Response header. Invalid number of arguments: ' + str(size))

        if size > 0:
            element = list.getList()[0]
            if element is None or element.isNull():
                print("Received malformed SASL-Response header: challenge can't be null")
            self.response = unwrapper.unwrapBinary(element)

    def toString(self):
        return "SASLResponse [response=" + str(self.response) + ", code=" + str(self.code) + ", doff=" + str(self.doff) + ", type=" + str(self.type) + ", channel=" + str(self.channel) + "]"

    def getResponse(self):
        return self.response

    def calcCramMD5(self,challenge,user):
        data = bytearray()
        if challenge is not None and len(challenge) > 0:
            m = md5.MD5()
            m.update(challenge)
            data = m.hexdigest()
            hash = user + ' ' + data
            return bytes(hash,'utf-8')
        else:
            return data

    def setCramMD5Response(self,challenge,user):
        if user is None:
            print("CramMD5 response generator must be provided with a non-null username value")
        if challenge is None:
            print("CramMD5 response generator must be provided with a non-null challenge value")
        self.response = self.calcCramMD5(challenge,user)
