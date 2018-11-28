class topicType():
    def __init__(self):
        self.dict = {'NAMED': 0, 'ID': 1, 'SHORT': 2, 'UNKNOWN': 3}

    def getValueByKey(self, key):
        return self.dict.get(key)

    def getKeyByValue(self, valueSearch):
        for key, value in self.dict.items():
            if value == valueSearch:
                return key