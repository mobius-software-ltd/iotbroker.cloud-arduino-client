class coapType():
    def __init__(self):
        self.dict = {'CONFIRMABLE':0,'NON_CONFIRMABLE':1,'ACKNOWLEDGEMENT':2,'RESET':3}

    def getValueByKey(self, key):
        return self.dict.get(key)

    def getKeyByValue(self, valueSearch):
        for key, value in self.dict.items():
            if value == valueSearch:
                return key
