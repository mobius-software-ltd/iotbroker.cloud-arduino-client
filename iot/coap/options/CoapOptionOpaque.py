class coapOptionOpaque():
    def __init__(self, type, length, value):
        self.type = type
        self.length = length
        self.value = value
    
    def getType(self):
        return self.type

    def getLength(self):
        return self.length

    def getValue(self):
        return self.value
