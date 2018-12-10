class terminusDurability():
    def __init__(self):
        self.dict = {'NONE':0,'CONFIGURATION':1,'UNSETTLED_STATE':2}

    def getValueByKey(self, key):
        return self.dict.get(key)

    def getKeyByValue(self, valueSearch):
        for key, value in self.dict.items():
            if value == valueSearch:
                return key
