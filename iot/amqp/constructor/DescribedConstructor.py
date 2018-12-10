class describedConstructor():
    def __init__(self, code, descriptor):
        self.code = code
        self.descriptor = descriptor

    def getDescriptor(self):
        return self.descriptor
    
    def getCode(self):
        return self.code
        
    def setCode(self, code):
        self.code = code

    def getLength(self):
        return self.descriptor.getLength() + 2

    def getBytes(self):
        data = bytearray(1)
        descriptorBytes = self.descriptor.getBytes()
        data += descriptorBytes
        data.append(self.code.value)
        return data

    def getDescriptorCode(self):
        return self.descriptor.getBytes()[1]
        
    def getType():
        return 'described'
