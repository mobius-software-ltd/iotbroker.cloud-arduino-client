import iot.coap.options.CoapOption as CoapOption

class coapMessage():
    def __init__(self, version, type, code, packetID, token, options, payload):
        self.version = version
        self.type = type
        self.code = code
        self.packetID = packetID
        self.token = token
        self.options = options
        self.payload = payload

    def equals(self, obj):
        if self == obj:
            return True
        return False

    def getVersion(self):
        return self.version

    def setVersion(self, version):
        self.version = version

    def getType(self):
        return self.type

    def setType(self, type):
        self.type = type

    def getCode(self):
        return self.code

    def setCode(self, code):
        self.code = code

    def getPacketID(self):
        return self.packetID

    def setPacketID(self, packetID):
        self.packetID = packetID

    def getToken(self):
        return self.token

    def setToken(self, token):
        self.token = token

    def getOptions(self):
        return self.sortOptions(self.options)
    
    def sortOptions(options):
        for i in range(1, len(options)):
            j = i
            while j > 0 and options[j].getType().value < options[j - 1].getType().value:
                options[j], options[j - 1] = options[j - 1], options[j]
                j -= 1
        return options

    def getOptionsDecode(self):
        return self.options

    def setOptions(self, options):
        self.options = options

    def getPayload(self):
        return self.payload

    def setPayload(self, payload):
        self.payload = payload
