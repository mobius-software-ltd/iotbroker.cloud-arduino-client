class sendCode():
    def __init__(self):
        self.dict = {'UNSETTLED':0,'SETTLED':1,'MIXED':2}

    def getValueByKey(self, key):
        return self.dict.get(key)

    def getKeyByValue(self, valueSearch):
        for key, value in self.dict.items():
            if value == valueSearch:
                return key


