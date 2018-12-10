class terminusExpiryPolicy():
    def __init__(self):
        self.dict = {'LINK_DETACH':'link-detach','SESSION_END':'session-end','CONNETION_CLOSE':'connection-close','NEVER':'never'}

    def getValueByKey(self, key):
        return self.dict.get(key)

    def getKeyByValue(self, valueSearch):
        for key, value in self.dict.items():
            if value == valueSearch:
                return key


