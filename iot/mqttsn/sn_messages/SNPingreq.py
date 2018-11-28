import iot.mqttsn.sn_classes.SNmessageType as SNmessageType

class snPingreq():
    def __init__(self, clientID):
        self.clientID = clientID

    def getLength(self):
        length = 2
        if self.clientID is not None and len(self.clientID) > 0:
            length += len(self.clientID)
        return length

    def getType(self):
        return SNmessageType.snMessageType.getValueByKey('SN_PINGREQ')

    def getClientID(self):
        return self.clientID

    def setClientID(self, clientID):
        self.clientID = clientID