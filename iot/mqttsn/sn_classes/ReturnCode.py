class returnCode():
    def __init__(self):
        self.dict = {'ACCEPTED': 0, 'CONGESTION': 1, 'INVALID_TOPIC_ID': 2, 'NOT_SUPPORTED': 3}

    def getValueByKey(self, key):
        return self.dict.get(key)

    def getKeyByValue(self, valueSearch):
        for key, value in self.dict.items():
            if value == valueSearch:
                return key