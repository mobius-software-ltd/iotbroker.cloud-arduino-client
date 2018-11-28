import iot.classes.Account as Account

class Parser():
    def getConfig(configPath):
        ff = open(configPath)
        while True:
            line = ff.readline()
            if line.startswith('protocol'):
                protocol = line.split(":")[1].strip()
            if line.startswith('username'):
                username = line.split(":")[1].strip()
            if line.startswith('password'):
                password = line.split(":")[1].strip()
            if line.startswith('clientid'):
                clientID = line.split(":")[1].strip()
            if line.startswith('host'):
                host = line.split(":")[1].strip()
            if line.startswith('port'):
                port = line.split(":")[1].strip()
            if line.startswith('cleanSession'):
                isClean = line.split(":")[1].strip()
                if isClean == 'True':
                    isClean = True
                else:
                    isClean = False
            if line.startswith('keepAlive'):
                keepAlive = line.split(":")[1].strip()
            if line.startswith('will'):
                will = line.split(":")[1].strip()
            if line.startswith('willTopic'):
                willTopic = line.split(":")[1].strip()
            if line.startswith('retain'):
                retain = line.split(":")[1].strip()
                if retain == 'True':
                    retain = True
                else:
                    retain = False
            if line.startswith('qos'):
                qos = line.split(":")[1].strip()
            if line.startswith('enable'):
                enable = line.split(":")[1].strip()
                if enable == 'True':
                    enable = True
                else:
                    enable = False
            if line.startswith('cert_path'):
                cert_path = line.split(":")[1].strip()
            if line.startswith('key_path'):
                key_path = line.split(":")[1].strip()
            if line.startswith('topics'):
                topics = line.split(":")[1].strip()
            if line.startswith('timeout'):
                timeout = line.split(":")[1].strip()
            if line.startswith('#END') or not line :
                break
        userAccount = Account.account(protocol, username, password, clientID, host, port, isClean, keepAlive, will, willTopic, retain, qos, enable, cert_path, key_path, topics, timeout)
        return userAccount