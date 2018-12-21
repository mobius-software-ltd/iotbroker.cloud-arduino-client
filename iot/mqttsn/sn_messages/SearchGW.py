import iot.mqttsn.sn_classes.SNmessageType as SNmessageType

class searchGW():
    def __init__(self, radius):
        self.radius = radius
        self.snMessageType = SNmessageType.snMessageType()

    def getLength(self):
        return 3

    def getType(self):
        return self.snMessageType.getValueByKey('SN_SEARCHGW')

    def getRadius(self):
        return self.radius

    def setRadius(self, radius):
        self.radius = radius
