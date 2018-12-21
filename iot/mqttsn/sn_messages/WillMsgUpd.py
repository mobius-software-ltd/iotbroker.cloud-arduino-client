import iot.mqttsn.sn_classes.SNmessageType as SNmessageType

class willMsgUpd():
    def __init__(self, content):
        self.content = content
        self.snMessageType = SNmessageType.snMessageType()

    def getLength(self):
        length = 2
        if self.content is not None and len(self.content) > 0:
            length += len(self.content)
        if len(self.content) > 253:
            length += 2
        return length

    def getType(self):
        return self.snMessageType.getValueByKey('SN_WILL_MSG_UPD')

    def getContent(self):
        return self.content

    def setContent(self, content):
        self.content = content
