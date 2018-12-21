import iot.mqttsn.sn_classes.SNmessageType as SNmessageType

class willMsgResp():
    def __init__(self, code):
        self.code = code
        self.snMessageType = SNmessageType.snMessageType()

    def getLength(self):
        return 3

    def getType(self):
        return self.snMessageType.getValueByKey('SN_WILL_MSG_RESP')

    def getCode(self):
        return self.code

    def setCode(self, code):
        self.code = code
