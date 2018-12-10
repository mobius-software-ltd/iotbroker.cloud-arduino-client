class stateCode():
    def __init__(self):
        self.dict = {'RECEIVED':0x23, 'ACCEPTED':0x24, 'REJECTED':0x25, 'RELEASED':0x26, 'MODIFIED':0x27}

    def getValueByKey(self, key):
        return self.dict.get(key)

    def getKeyByValue(self, valueSearch):
        for key, value in self.dict.items():
            if value == valueSearch:
                return key


