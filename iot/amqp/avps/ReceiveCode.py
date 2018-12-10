class receiveCode():
    def __init__(self):
        self.dict = {'FIRST':0,'SECOND':1}

    def getValueByKey(self, key):
        return self.dict.get(key)

    def getKeyByValue(self, valueSearch):
        for key, value in self.dict.items():
            if value == valueSearch:
                return key
