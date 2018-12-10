class simpleConstructor():
    def __init__(self, code):
        self.code = code

    def getCode(self):
        return self.code

    def setCode(self, code):
        self.code = code

    def getLength(self):
        return 1

    def getBytes(self):
        return self.code.value

    def getDescriptorCode(self):
        return None
    
    def getType():
        return 'simple'
