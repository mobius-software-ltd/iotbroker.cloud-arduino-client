class qosType():
    def __init__(self):
        self.dict = {'AT_MOST_ONCE': 0, 'AT_LEAST_ONCE': 1, 'EXACTLY_ONCE': 2, 'LEVEL_ONE': 3}

    def getValueByKey(self, key):
        return self.dict.get(key)

    def getKeyByValue(self, valueSearch):
        for key, value in self.dict.items():
            if value == valueSearch:
                return key