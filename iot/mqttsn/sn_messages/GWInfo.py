import iot.mqttsn.sn_classes.SNmessageType as SNmessageType

class gwInfo():
    def __init__(self, gwID, gwAddress):
        self.gwID = gwID
        self.gwAddress = gwAddress

    def getLength(self):
        length = 3
        if self.gwAddress is not None and len(self.gwAddress)>0:
            length += len(self.gwAddress)
        return length

    def getType(self):
        return SNmessageType.snMessageType.getValueByKey('SN_GWINFO')

    def getgwID(self):
        return self.gwID

    def setgwID(self, gwID):
        self.gwID = gwID

    def getgwAddress(self):
        return self.gwAddress

    def setgwAddress(self, gwAddress):
        self.gwAddress = gwAddress