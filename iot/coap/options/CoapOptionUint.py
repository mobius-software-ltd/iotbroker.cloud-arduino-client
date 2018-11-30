class coapOptionUint():
    def __init__(self, type, length, value):
        self.type = type
        self.length = length
        self.value = value

    def getIntegerValue(self):
        return (int(self.value) & 0x00FFFFFFFF)

    def getType(self):
        return self.type

    def getLength(self):
        return self.length

    def getValue(self):
        return self.value
