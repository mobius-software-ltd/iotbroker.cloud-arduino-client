class distributionMode():
    def __init__(self):
        self.dict = {'MOVE':'move','COPY':'copy'}

    def getValueByKey(self, key):
        return self.dict.get(key)

    def getKeyByValue(self, valueSearch):
        for key, value in self.dict.items():
            if value == valueSearch:
                return key
