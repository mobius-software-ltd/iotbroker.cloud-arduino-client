import iot.mqttsn.sn_classes.SNmessageType as SNmessageType

class snPingresp():
    def __init__(self):
        pass

    def getLength(self):
        return 2

    def getType(self):
        return SNmessageType.snMessageType.getValueByKey('SN_PINGRESP')