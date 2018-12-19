class endpointState():
    def __init__(self):
        self.dict = {'HDR_RCV':'HDR_RCV','HDR_SENT':'HDR_SENT','HDR_EXCH':'HDR_EXCH','OPEN_PIPE':'OPEN_PIPE','OC_PIPE':'OC_PIPE','OPEN_RCVD':'OPEN_RCVD','OPEN_SENT':'OPEN_SENT','CLOSE_PIPE':'CLOSE_PIPE','CLOSE_RCVD':'CLOSE_RCVD','CLOSE_SENT':'CLOSE_SENT','DISCARDING':'DISCARDING','END':'END','UNMAPPED':'UNMAPPED','BEGIN_SENT':'BEGIN_SENT','BEGIN_RCVD':'BEGIN_RCVD','MAPPED':'MAPPED','END_SENT':'END_SENT','END_RCVD':'END_RCVD','START':'START','OPENED':'OPENED'}

    def getValueByKey(self, key):
        return self.dict.get(key)

    def getKeyByValue(self, valueSearch):
        for key, value in self.dict.items():
            if value == valueSearch:
                return key




