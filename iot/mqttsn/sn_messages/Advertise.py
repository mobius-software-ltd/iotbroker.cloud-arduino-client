import iot.mqttsn.sn_classes.SNmessageType as SNmessageType

class advertise():
    def __init__(self, gwID, duration):
        self.gwID = gwID
        self.duration = duration

    def getLength(self):
        return 5

    def getType(self):
        return SNmessageType.snMessageType.getValueByKey('SN_ADVERTISE')

    def getgwID(self):
        return self.gwID

    def setgwID(self, gwID):
        self.gwID = gwID

    def getDuration(self):
        return self.duration

    def setDuration(self, duration):
        self.duration = duration