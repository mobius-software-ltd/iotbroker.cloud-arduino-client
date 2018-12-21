import iot.mqttsn.sn_classes.SNmessageType as SNmessageType

class snPubrec():
    def __init__(self, packetID):
        self.packetID = packetID
        self.snMessageType = SNmessageType.snMessageType()

    def getLength(self):
        return 4

    def getType(self):
        return self.snMessageType.getValueByKey('SN_PUBREC')

    def getPacketID(self):
        return self.packetID

    def setPacketID(self, packetID):
        self.packetID = packetID
