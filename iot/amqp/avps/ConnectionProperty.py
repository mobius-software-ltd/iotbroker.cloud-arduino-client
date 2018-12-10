class connectionProperty():
    def __init__(self):
        self.dict = {'PLATFORM':'platform','PRODUCT':'product','QPID_CLIENT_PID':'qpid.client_pid','QPID_CLIENT_PPID':'qpid.client_ppid','QPID_CLIENT_PROCESS':'qpid.client_process','VERSION':'version'}

    def getValueByKey(self, key):
        return self.dict.get(key)

    def getKeyByValue(self, valueSearch):
        for key, value in self.dict.items():
            if value == valueSearch:
                return key
