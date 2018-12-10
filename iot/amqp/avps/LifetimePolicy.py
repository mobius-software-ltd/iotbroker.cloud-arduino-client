class lifetimePolicy():
    def __init__(self):
        self.dict = {'DELETE_ON_CLOSE':0x2b,'DELETE_ON_NO_LINKS':0x2c,'DELETE_ON_NO_MESSAGES':0x2d,'DELETE_ON_NO_LINKS_OR_MESSAGES':0x2e}

    def getValueByKey(self, key):
        return self.dict.get(key)

    def getKeyByValue(self, valueSearch):
        for key, value in self.dict.items():
            if value == valueSearch:
                return key

