import iot.amqp.avps.AMQPType as AMQPType 
import iot.amqp.avps.HeaderCode as HeaderCode
import iot.amqp.avps.SectionCode as SectionCode
import iot.amqp.tlv.api.TLVFactory as TLVFactory
import iot.amqp.sections.ApplicationProperties as ApplicationProperties
import iot.amqp.sections.AMQPData as AMQPData
import iot.amqp.sections.DeliveryAnnotations as DeliveryAnnotations
import iot.amqp.sections.AMQPFooter as AMQPFooter
import iot.amqp.sections.MessageHeader as MessageHeader
import iot.amqp.sections.MessageAnnotations as MessageAnnotations
import iot.amqp.sections.AMQPProperties as AMQPProperties
import iot.amqp.sections.AMQPSequence as AMQPSequence
import iot.amqp.sections.AMQPValue as AMQPValue

import iot.amqp.header.impl.SASLMechanisms as SASLMechanisms
import iot.amqp.header.impl.SASLChallenge as SASLChallenge
import iot.amqp.header.impl.SASLInit as SASLInit
import iot.amqp.header.impl.SASLOutcome as SASLOutcome
import iot.amqp.header.impl.SASLResponse as SASLResponse
import iot.amqp.header.impl.AMQPOpen as AMQPOpen
import iot.amqp.header.impl.AMQPBegin as AMQPBegin
import iot.amqp.header.impl.AMQPEnd as AMQPEnd
import iot.amqp.header.impl.AMQPClose as AMQPClose
import iot.amqp.header.impl.AMQPAttach as AMQPAttach
import iot.amqp.header.impl.AMQPTransfer as AMQPTransfer
import iot.amqp.header.impl.AMQPDetach as AMQPDetach
import iot.amqp.header.impl.AMQPDisposition as AMQPDisposition
import iot.amqp.header.impl.AMQPFlow as AMQPFlow

class headerFactory():
    def __init__(self, index):
        self.index = index
        self.tlvFactory = TLVFactory.tlvFactory(index)
        self.amqpType = AMQPType.amqpType()
        self.headerCode = HeaderCode.headerCode()
        self.sectionCode = SectionCode.sectionCode()

    def getIndex(self):
        return self.index

    def setIndex(self,index):
        self.index = index

    def getAMQP(self, buf):
        list = self.tlvFactory.getTlv(buf)
        self.index = self.tlvFactory.getIndex()


        if list is not None:
            code  = list.getCode()

            if code not in (self.amqpType.getValueByKey('LIST_0'),self.amqpType.getValueByKey('LIST_8'),self.amqpType.getValueByKey('LIST_32')):
                print('Received amqp-header with malformed arguments')

            byteCode = list.getConstructor().getDescriptorCode()
            code = HeaderCode.getKeyByValue(byteCode)

            if code == 'ATTACH':
                header = AMQPAttach.amqpAttach(None,None,None,None,None,None,None,None,None,None,None,None,None,None,None,None,None,None)
            elif code == 'BEGIN':
                header = AMQPBegin.amqpBegin(None,None,None,None,None,None,None,None,None,None,None,None)
            elif code == 'CLOSE':
                header = AMQPClose.amqpClose(None,None,None,None,None)
            elif code == 'DETACH':
                header = AMQPDetach.amqpDetach(None,None,None,None,None,None,None)
            elif code == 'DISPOSITION':
                header = AMQPDisposition.amqpDisposition(None,None,None,None,None,None,None,None,None,None)
            elif code == 'END':
                header = AMQPEnd.amqpEnd(None,None,None,None,None)
            elif code == 'FLOW':
                header = AMQPFlow.amqpFlow(None,None,None,None,None,None,None,None,None,None,None,None,None,None,None)
            elif code == 'OPEN':
                header = AMQPOpen.amqpOpen(None,None,None,None,None,None,None,None,None,None,None,None,None,None)
            elif code == 'TRANSFER':
                header = AMQPTransfer.amqpTransfer(None, None, None, None, None, None, None, None, None, None, None, None, None, None, None, None)
            header.fromArgumentsList(list)
            return header
        
        return None

    def getSASL(self, buf):
        list = self.tlvFactory.getTlv(buf)
        self.index = self.tlvFactory.getIndex()
        if list is not None:
            code  = list.getCode()
            if code not in (self.amqpType.getValueByKey('LIST_0'),self.amqpType.getValueByKey('LIST_8'),self.amqpType.getValueByKey('LIST_32')):
                print('Received sasl-header with malformed arguments')
            byteCode = list.getConstructor().getDescriptorCode()
            code = HeaderCode.getKeyByValue(byteCode)

            if code == 'CHALLENGE':
                header = SASLChallenge.saslChallenge(None,None,None,None,None)
            elif code == 'INIT':
                header = SASLInit.saslInit(None,None,None,None,None,None,None)
            elif code == 'MECHANISMS':
                header = SASLMechanisms.saslMechanisms(None,None,None,None,None)
            elif code == 'OUTCOME':
                header = SASLOutcome.saslOutcome(None,None,None,None,None,None)
            elif code == 'RESPONSE':
                header = SASLResponse.saslResponse(None,None,None,None,None)
            header.fromArgumentsList(list)
            return header

    def getSection(self, buf):
        value = self.tlvFactory.getTlv(buf)
        section = None
        self.index = self.tlvFactory.getIndex()
        byteCode = value.getConstructor().getDescriptorCode()
        code = self.sectionCode.getKeyByValue(byteCode)
        if code == 'APPLICATION_PROPERTIES':
            section = ApplicationProperties.applicationProperties(None)
        elif code == 'DATA':
            section = AMQPData.amqpData(None)
        elif code == 'DELIVERY_ANNOTATIONS':
            section = DeliveryAnnotations.deliveryAnnotations(None)
        elif code == 'FOOTER':
            section = AMQPFooter.amqpFooter(None)
        elif code == 'HEADER':
            section = MessageHeader.messageHeader(None)
        elif code == 'MESSAGE_ANNOTATIONS':
            section = MessageAnnotations.messageAnnotations(None)
        elif code == 'PROPERTIES':
            section = AMQPProperties.amqpProperties(None)
        elif code == 'SEQUENCE':
            section = AMQPSequence.amqpSequence(None)
        elif code == 'VALUE':
            section = AMQPValue.amqpValue(None)
        else:
            print('Received header with unrecognized message section code')

        section.fill(value)
        return section
