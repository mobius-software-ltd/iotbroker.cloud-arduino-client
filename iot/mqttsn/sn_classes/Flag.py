class flag():
    def __init__(self):
        self.dict = {'UNKNOWN': 0, 'ID_TOPIC': 1, 'SHORT_TOPIC': 2, 'RESERVED_TOPIC': 3, 'CLEAN_SESSION': 4, 'WILL': 8, 'RETAIN': 16, 'QOS_1': 32, 'QOS_2': 64, 'QOS_LEVEL_ONE': 96, 'DUPLICATE': 128}

    def getValueByKey(self, key):
        return self.dict.get(key)

    def getKeyByValue(self, valueSearch):
        for key, value in self.dict.items():
            if value == valueSearch:
                return key