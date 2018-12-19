import iot.amqp.avps.AMQPType as AMQPType
import iot.amqp.header.api.AMQPWrapper as AMQPWrapper
import iot.amqp.header.api.AMQPUnwrapper as AMQPUnwrapper
import iot.amqp.constructor.DescribedConstructor as DescribedConstructor
import iot.amqp.avps.SectionCode as SectionCode
import iot.amqp.wrappers.LongID as LongID
import iot.amqp.wrappers.StringID as StringID
import iot.amqp.wrappers.BinaryID as BinaryID
import iot.amqp.tlv.impl.TLVFixed as TLVFixed
import iot.amqp.tlv.impl.TLVList as TLVList

class amqpProperties():
    def __init__(self,messageId,userId,to,subject,replyTo,correlationId,contentType,contentEncoding,absoluteExpiryTime,creationTime,groupId,groupSequence,replyToGroupId):
        self.messageId = messageId
        self.userId = userId
        self.to = to
        self.subject = subject
        self.replyTo = replyTo
        self.correlationId = correlationId
        self.contentType = contentType
        self.contentEncoding = contentEncoding
        self.absoluteExpiryTime = absoluteExpiryTime
        self.creationTime = creationTime
        self.groupId = groupId
        self.groupSequence = groupSequence
        self.replyToGroupId = replyToGroupId

    def getValue(self):
        list  = TLVList.tlvList(None, None)
        wrapper = AMQPWrapper.amqpWrapper()

        if self.messageId is not None:
            value = None
            if self.messageId.getBinary() is not None:
                value = self.messageId.getBinary()
            elif self.messageId.getLong() is not None:
                value = self.messageId.getLong()
            elif self.messageId.getString() is not None:
                value = self.messageId.getString()
            elif self.messageId.getUuid() is not None:
                value = self.messageId.getUuid()
            list.addElement(0, wrapper.wrap(value))

        if self.userId is not None:
            list.addElement(1, wrapper.wrap(self.userId))
        if self.to is not None:
            list.addElement(2, wrapper.wrap(self.to))
        if self.subject is not None:
            list.addElement(3, wrapper.wrap(self.subject))
        if self.replyTo is not None:
            list.addElement(4, wrapper.wrap(self.replyTo))
        if self.correlationId is not None:
            list.addElement(5, wrapper.wrap(self.correlationId))
        if self.contentType is not None:
            list.addElement(6, wrapper.wrap(self.contentType))
        if self.contentEncoding is not None:
            list.addElement(7, wrapper.wrap(self.contentEncoding))
        if self.absoluteExpiryTime is not None:
            list.addElement(8, wrapper.wrap(self.absoluteExpiryTime))
        if self.creationTime is not None:
            list.addElement(9, wrapper.wrap(self.creationTime))
        if self.groupId is not None:
            list.addElement(10, wrapper.wrap(self.groupId))
        if self.groupSequence is not None:
            list.addElement(11, wrapper.wrap(self.groupSequence))
        if self.replyToGroupId is not None:
            list.addElement(12, wrapper.wrap(self.replyToGroupId))

        constructor = DescribedConstructor.describedConstructor(list.getCode(), TLVFixed.tlvFixed(AMQPType.amqpType.getValueByKey('SMALL_ULONG'), 0x73))
        list.setConstructor(constructor)
        return list

    def fill(self, value):
        list = value
        unwrapper = AMQPUnwrapper.amqpUnwrapper()

        if len(list.getList()) > 0:
            element = list.getList()[0]
            if element is not None:
                code = element.getCode()
                if code in (AMQPType.amqpType.getValueByKey('ULONG_0'),AMQPType.amqpType.getValueByKey('SMALL_ULONG'),AMQPType.amqpType.getValueByKey('ULONG')):
                    self.messageId = LongID.longID(unwrapper.unwrapULong(element))
                elif code in (AMQPType.amqpType.getValueByKey('STRING_8'),AMQPType.amqpType.getValueByKey('STRING_32')):
                    self.messageId = StringID.stringID(unwrapper.unwrapString(element))
                elif code in (AMQPType.amqpType.getValueByKey('BINARY_8'),AMQPType.amqpType.getValueByKey('BINARY_32')):
                    self.messageId = BinaryID.binaryID(unwrapper.unwrapBinary(element))
                elif code in (AMQPType.amqpType.getValueByKey('UUID')):
                    self.messageId = BinaryID.binaryID(unwrapper.unwrapUuid(element))
                else:
                    print('Expected type MessageID received ' + str(element.getCode()))
        if len(list.getList()) > 1:
            element = list.getList()[1]
            if element is not None:
                self.userId = unwrapper.unwrapBinary(element)
        if len(list.getList()) > 2:
            element = list.getList()[2]
            if element is not None:
                self.to = unwrapper.unwrapString(element)
        if len(list.getList()) > 3:
            element = list.getList()[3]
            if element is not None:
                self.subject = unwrapper.unwrapString(element)
        if len(list.getList()) > 4:
            element = list.getList()[4]
            if element is not None:
                self.replyTo = unwrapper.unwrapString(element)
        if len(list.getList()) > 5:
            element = list.getList()[5]
            if element is not None:
                self.correlationId = unwrapper.unwrapBinary(element)
        if len(list.getList()) > 6:
            element = list.getList()[6]
            if element is not None:
                self.contentType = unwrapper.unwrapString(element)
        if len(list.getList()) > 7:
            element = list.getList()[7]
            if element is not None:
                self.contentEncoding = unwrapper.unwrapString(element)
        if len(list.getList()) > 8:
            element = list.getList()[8]
            if element is not None:
                self.absoluteExpiryTime = unwrapper.unwrapTimastamp(element)
        if len(list.getList()) > 9:
            element = list.getList()[9]
            if element is not None:
                self.creationTime = unwrapper.unwrapTimastamp(element)
        if len(list.getList()) > 10:
            element = list.getList()[10]
            if element is not None:
                self.groupId = unwrapper.unwrapString(element)
        if len(list.getList()) > 11:
            element = list.getList()[11]
            if element is not None:
                self.groupSequence = unwrapper.unwrapUInt(element)
        if len(list.getList()) > 12:
            element = list.getList()[12]
            if element is not None:
                self.replyToGroupId = unwrapper.unwrapString(element)

    def getCode(self):
        return SectionCode.sectionCode.getValueByKey('PROPERTIES')

    def toString(self):
        return 'AMQPProperties [messageId=' + self.messageId + ', userId=' + self.userId + ', to=' + self.to + ', subject=' + self.subject + ', replyTo=' + self.replyTo + ', correlationId=' + self.correlationId + ', contentType=' + self.contentType + ', contentEncoding=' + self.contentEncoding + ', absoluteExpiryTime=' + self.absoluteExpiryTime + ', creationTime=' + self.creationTime + ', groupId=' + self.groupId + ', groupSequence=' + self.groupSequence + ', replyToGroupId=' + self.replyToGroupId + ']'

    def getMessageId(self):
        return self.messageId

    def setMessageId(self, messageId):
        self.messageId = messageId

    def getUserId(self):
        return self.userId

    def setUserId(self, userId):
        self.userId = userId

    def getTo(self):
        return self.to

    def setTo(self, to):
        self.to = to

    def getSubject(self):
        return self.subject

    def setSubject(self, subject):
        self.subject = subject

    def getReplyTo(self):
        return self.replyTo

    def setReplyTo(self, replyTo):
        self.replyTo = replyTo

    def getCorrelationId(self):
        return self.correlationId

    def setCorrelationId(self, correlationId):
        self.correlationId = correlationId

    def getContentType(self):
        return self.contentType

    def setContentType(self, contentType):
        self.contentType = contentType

    def getContentEncoding(self):
        return self.contentEncoding

    def setContentEncoding(self, contentEncoding):
        self.contentEncoding = contentEncoding

    def getAbsoluteExpiryTime(self):
        return self.absoluteExpiryTime

    def setAbsoluteExpiryTime(self, absoluteExpiryTime):
        self.absoluteExpiryTime = absoluteExpiryTime

    def getCreationTime(self):
        return self.creationTime

    def setCreationTime(self, creationTime):
        self.creationTime = creationTime

    def getGroupId(self):
        return self.groupId

    def setGroupId(self, groupId):
        self.groupId = groupId

    def getGroupSequence(self):
        return self.groupSequence

    def setGroupSequence(self, groupSequence):
        self.groupSequence = groupSequence

    def getReplyToGroupId(self):
        return self.replyToGroupId

    def setReplyToGroupId(self, replyToGroupId):
        self.replyToGroupId = replyToGroupId
