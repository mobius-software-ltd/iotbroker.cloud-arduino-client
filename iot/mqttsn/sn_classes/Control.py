class control():
    def __init__(self):
        self.dict = {'BROADCAST': 0, 'RADIUS_1': 1, 'RADIUS_2': 2, 'RADIUS_3': 3}

    def getValueByKey(self, key):
        return self.dict.get(key)

    def getKeyByValue(self, valueSearch):
        for key, value in self.dict.items():
            if value == valueSearch:
                return key