class opCode():
    def __init__(self):
        self.dict = {'CONTINUATION': '0x0', 'TEXT': '0x1', 'BINARY': '0x2', 'CLOSE': '0x8', 'PING': '0x9', 'PONG': '0xA'}

    def getValueByKey(self, key):
        return self.dict.get(key)

    def getKeyByValue(self, valueSearch):
        for key, value in self.dict.items():
            if value == valueSearch:
                return key
