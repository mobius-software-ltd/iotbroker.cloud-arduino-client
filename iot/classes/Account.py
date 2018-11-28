class account():
    def __init__(self, protocol, username, password, clientID, host, port, isClean, keepAlive, will, willTopic, retain, qos, enable, cert_path, key_path, topics, timeout):
        self.protocol = protocol 
        self.username = username 
        self.password = password 
        self.clientID = clientID 
        self.host = host 
        self.port = port 
        self.isClean = isClean 
        self.keepAlive = keepAlive 
        self.will = will 
        self.willTopic = willTopic 
        self.retain = retain 
        self.qos = qos 
        self.enable = enable 
        self.cert_path = cert_path 
        self.key_path = key_path 
        self.topics = topics
        self.timeout = timeout
    
    def setProtocol(self, protocol):
        self.protocol = protocol
    def getProtocol(self):
        return self.protocol
    def setUsername(self, username):
        self.username = username
    def getUsername(self):
        return self.username
    def setPassword(self, password):
        self.password = password
    def getPassword(self):
        return self.password
    def setClientID(self, clientID):
        self.clientID = clientID
    def getClientID(self):
        return self.clientID
    def setHost(self, host):
        self.host = host
    def getHost(self):
        return self.host
    def setPort(self, port):
        self.port = port
    def getPort(self):
        return self.port
    def setIsClean(self, isClean):
        self.isClean = isClean
    def getIsClean(self):
        return self.isClean
    def setKeepAlive(self, keepAlive):
        self.keepAlive = keepAlive
    def getKeepAlive(self):
        return self.keepAlive
    def setWill(self, will):
        self.will = will
    def getWill(self):
        return self.will
    def setWillTopic(self, willTopic):
        self.willTopic = willTopic
    def getWillTopic(self):
        return self.willTopic
    def setRetain(self, retain):
        self.retain = retain
    def getRetain(self):
        return self.retain
    def setQos(self, qos):
        self.qos = qos
    def getQos(self):
        return self.qos
    def setEnable(self, enable):
        self.enable = enable
    def getEnable(self):
        return self.enable
    def setCert_path(self, cert_path):
        self.cert_path = cert_path
    def getCert_path(self):
        return self.cert_path
    def setKey_path(self, key_path):
        self.key_path = key_path
    def getKey_path(self):
        return self.key_path
    def setTopics(self, topics):
        self.topics = topics
    def getTopics(self):
        return self.topics
    def setTimeout(self, timeout):
        self.timeout = timeout
    def getTimeout(self):
        return self.timeout