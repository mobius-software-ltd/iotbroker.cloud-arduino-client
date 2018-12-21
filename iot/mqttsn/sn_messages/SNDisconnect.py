import iot.mqttsn.sn_classes.SNmessageType as SNmessageType

class snDisconnect():
    def __init__(self, duration):
        self.duration = duration
        self.snMessageType = SNmessageType.snMessageType()

    def getLength(self):
        length = 2
        if self.duration is not None and self.duration > 0:
            length += 2
        return length

    def getType(self):
        return self.snMessageType.getValueByKey('SN_DISCONNECT')

    def getDuration(self):
        return self.duration

    def setDuration(self, duration):
        self.duration = duration
