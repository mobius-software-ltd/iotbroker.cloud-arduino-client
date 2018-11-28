class сonnectionState():
    def __init__(self):
        self.dict = {'NONE': 0, 'CHANNEL_CREATING': 1, 'CHANNEL_ESTABLISHED': 2, 'CHANNEL_FAILED': 3, 'CONNECTING': 4, 'CONNECTION_ESTABLISHED': 5, 'CONNECTION_FAILED': 6, 'CONNECTION_LOST':7}

    def getValueByKey(self, key):
        return self.dict.get(key)

    def getKeyByValue(self, valueSearch):
        for key, value in self.dict.items():
            if value == valueSearch:
                return key