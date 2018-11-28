class mqttConnack():
    def __init__(self, sessionPresent, returnCode):
        self.sessionPresent = sessionPresent
        self.returnCode = returnCode

    def getLength(self):
        return 2

    def getType(self):
        return 2

    def getProtocol(self):
        return 1

    def isValidReturnCode(code):
        if code>=0 & code<=5:
            return True
        return False