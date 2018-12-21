import iot.mqttsn.sn_classes.SNmessageType as SNmessageType

class willTopicReq():
    def __init__(self):
        self.snMessageType = SNmessageType.snMessageType()

    def getLength(self):
        return 2

    def getType(self):
        return self.snMessageType.getValueByKey('SN_WILL_TOPIC_REQ')
