class dynamicNodeProperty():
    def __init__(self):
        self.dict = {'SUPPORTED_DIST_MODES':'supported-dist-modes','DURABLE':'durable','AUTO_DELETE':'auto-delete','ALTERNATE_EXCHANGE':'alternate-exchange','EXCHANGE_TYPE':'exchange-type'}

    def getValueByKey(self, key):
        return self.dict.get(key)

    def getKeyByValue(self, valueSearch):
        for key, value in self.dict.items():
            if value == valueSearch:
                return key

