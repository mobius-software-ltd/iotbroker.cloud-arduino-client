import iot.amqp.avps.HeaderCode as HeaderCode

class saslState():
    def __init__(self):
        self.dict = {'NONE':'NONE','MECHANISMS_SENT':'MECHANISMS_SENT','INIT_RECEIVED':'INIT_RECEIVED','CHALLENGE_SENT':'CHALLENGE_SENT','RESPONSE_RECEIVED':'RESPONSE_RECEIVED','NEGOTIATED':'NEGOTIATED'}

    def getValueByKey(self, key):
        return self.dict.get(key)

    def getKeyByValue(self, valueSearch):
        for key, value in self.dict.items():
            if value == valueSearch:
                return key
    
    def validate(self, code):
        if code == HeaderCode.headerCode.getValueByKey('MECHANISMS'):
            return self.dict.get('NONE')
        elif code == HeaderCode.headerCode.getValueByKey('INIT'):
            return self.dict.get('MECHANISMS_SENT')
        elif code == HeaderCode.headerCode.getValueByKey('CHALLENGE'):
            return self.dict.get('INIT_RECEIVED')
        elif code == HeaderCode.headerCode.getValueByKey('RESPONSE'):
            return self.dict.get('CHALLENGE_SENT')
        elif code == HeaderCode.headerCode.getValueByKey('OUTCOME'):
            return self.dict.get('RESPONSE_RECEIVED')
        else:
            return self.dict.get('NEGOTIATED')



