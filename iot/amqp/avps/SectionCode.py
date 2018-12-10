class sectionCode():
    def __init__(self):
        self.dict = {'HEADER':0x70,'DELIVERY_ANNOTATIONS':0x71,'MESSAGE_ANNOTATIONS':0x72,'PROPERTIES':0x73,'APPLICATION_PROPERTIES':0x74,'DATA':0x75,'SEQUENCE':0x76,'VALUE':0x77,'FOOTER':0x78}

    def getValueByKey(self, key):
        return self.dict.get(key)

    def getKeyByValue(self, valueSearch):
        for key, value in self.dict.items():
            if value == valueSearch:
                return key


