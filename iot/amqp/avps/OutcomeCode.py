class outcomeCode():
    def __init__(self):
        self.dict = {'OK':0,'AUTH':1,'SYS':2,'SYS_PERM':3,'SYS_TEMP':4}

    def getValueByKey(self, key):
        return self.dict.get(key)

    def getKeyByValue(self, valueSearch):
        for key, value in self.dict.items():
            if value == valueSearch:
                return key
