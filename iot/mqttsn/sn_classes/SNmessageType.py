class snMessageType():
    def __init__(self):
        self.dict = {'SN_ADVERTISE':0,'SN_SEARCHGW':1,'SN_GWINFO':2,'SN_CONNECT':4,'SN_CONNACK':5,'SN_WILL_TOPIC_REQ':6,'SN_WILL_TOPIC':7,'SN_WILL_MSG_REQ':8,'SN_WILL_MSG':9,'SN_REGISTER':10,'SN_REGACK':11,'SN_PUBLISH':12,'SN_PUBACK':13,'SN_PUBCOMP':14,'SN_PUBREC':15,'SN_PUBREL':16,'SN_SUBSCRIBE':18,'SN_SUBACK':19,'SN_UNSUBSCRIBE':20,'SN_UNSUBACK':21,'SN_PINGREQ':22,'SN_PINGRESP':23,'SN_DISCONNECT':24,'SN_WILL_TOPIC_UPD':26,'SN_WILL_TOPIC_RESP':27,'SN_WILL_MSG_UPD':28,'SN_WILL_MSG_RESP':29,'SN_ENCAPSULATED':254}

    def getValueByKey(self, key):
        return self.dict.get(key)

    def getKeyByValue(self, valueSearch):
        for key, value in self.dict.items():
            if value == valueSearch:
                return key
            