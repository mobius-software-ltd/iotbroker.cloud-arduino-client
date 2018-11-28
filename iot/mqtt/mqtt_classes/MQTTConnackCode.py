class mqttConnackCode():
    def __init__(self):
        self.dict = {'MQ_ACCEPTED': 0, 'MQ_UNACCEPTABLE_PROTOCOL_VERSION': 1, 'MQ_IDENTIFIER_REJECTED': 2, 'MQ_SERVER_UNAVALIABLE': 3, 'MQ_BAD_USER_OR_PASS': 4, 'MQ_NOT_AUTHORIZED': 5}

    def getValueByKey(self, key):
        return self.dict.get(key)

    def getKeyByValue(self, valueSearch):
        for key, value in self.dict.items():
            if value == valueSearch:
                return key