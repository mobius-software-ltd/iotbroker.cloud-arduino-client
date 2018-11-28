class Controls():
    def __init__(self, radius):
        self.radius = radius

    def getRadius(self):
        return self.radius

    def setRadius(self, radius):
        self.radius = radius

    def encode(self):
        ctrByte = 0
        ctrByte |= self.radius
        return ctrByte

    def decode(self, ctrByte):
        if(ctrByte > 3 or ctrByte <0):
            print('Invalid Encapsulated message control encoding: ' + str(ctrByte))
        return Controls(ctrByte)