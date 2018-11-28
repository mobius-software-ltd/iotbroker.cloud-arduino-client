import iot.mqttsn.sn_classes.SNmessageType as SNmessageType

class willTopicResp():
    def __init__(self, code):
        self.code = code

    def getLength(self):
        return 3

    def getType(self):
        return SNmessageType.snMessageType.getValueByKey('SN_WILL_TOPIC_RESP')

    def getCode(self):
        return self.code

    def setCode(self, code):
        self.code = code