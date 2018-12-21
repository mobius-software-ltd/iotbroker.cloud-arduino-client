import iot.mqttsn.sn_classes.SNmessageType as SNmessageType

class encapsulated():
    def __init__(self, radius, wirelessNodeID, message):
        self.radius = radius
        self.wirelessNodeID = wirelessNodeID
        self.message = message
        self.snMessageType = SNmessageType.snMessageType()

    def getLength(self):
        length = 3
        if self.wirelessNodeID is not None & len(self.wirelessNodeID)>0:
            length += len(self.wirelessNodeID)
        return length

    def getType(self):
        return self.snMessageType.getValueByKey('SN_ENCAPSULATED')

    def getRadius(self):
        return self.radius

    def setRadius(self, radius):
        self.radius = radius

    def getWirelessNodeID(self):
        return self.wirelessNodeID

    def setWirelessNodeID(self, wirelessNodeID):
        self.wirelessNodeID = wirelessNodeID

    def getMessage(self):
        return self.message

    def setMessage(self, message):
        self.message = message
