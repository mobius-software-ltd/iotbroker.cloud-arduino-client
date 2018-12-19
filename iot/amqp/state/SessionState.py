class sessionState():
    def __init__(self):
        self.dict = {'UNMAPPED':'UNMAPPED','BEGIN_SENT':'BEGIN_SENT','BEGIN_RCVD':'BEGIN_RCVD','MAPPED':'MAPPED','END_SENT':'END_SENT','END_RCVD':'END_RCVD','DISCARDING':'DISCARDING'}

    def getValueByKey(self, key):
        return self.dict.get(key)

    def getKeyByValue(self, valueSearch):
        for key, value in self.dict.items():
            if value == valueSearch:
                return key


