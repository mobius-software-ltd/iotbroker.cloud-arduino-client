class connectionState():
    def __init__(self):
        self.dict = {'START':'START','HDR_CRV':'HDR_CRV','YDR_SENT':'YDR_SENT','HDR_EXCH':'HDR_EXCH','OPEN_PIPE':'OPEN_PIPE','OC_PIPE':'OC_PIPE','OPEN_RCVD':'OPEN_RCVD','OPEN_SENT':'OPEN_SENT','CLOSE_PIPE':'CLOSE_PIPE','OPENED':'OPENED','CLOSE_RCVD':'CLOSE_RCVD','CLOSE_SENT':'CLOSE_SENT','DISCARDING':'DISCARDING','END':'END'}

    def getValueByKey(self, key):
        return self.dict.get(key)

    def getKeyByValue(self, valueSearch):
        for key, value in self.dict.items():
            if value == valueSearch:
                return key



