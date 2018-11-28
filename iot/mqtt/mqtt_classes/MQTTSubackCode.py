class mqttSubackCode():
    def __init__(self):
        self.dict = {'ACCEPTED_QOS0': 0, 'ACCEPTED_QOS1': 1, 'ACCEPTED_QOS2': 2, 'FAILURE': 128}

    def getValueByKey(self, key):
        return self.dict.get(key)

    def getKeyByValue(self, valueSearch):
        for key, value in self.dict.items():
            if value == valueSearch:
                return key