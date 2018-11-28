import iot.timers.TimerTask as TimerTask

class timersMap():
    def __init__(self, client):
        self.client = client
        self.connectTimer = None
        self.pingTimer = None
        self.timeoutTimer = None
        self.count = 0
        self.timersMap = {}

    def goConnectTimer(self, message):
        if self.connectTimer is not None:
            self.connectTimer.stop()
        self.connectTimer = TimerTask.timerTask(message, 3, self.client)
        self.connectTimer.start()

    def stopConnectTimer(self):
        if self.connectTimer is not None:
            self.connectTimer.stop()
            self.connectTimer = None

    def goPingTimer(self, message, keepalive):
        if self.pingTimer is not None:
            self.pingTimer.stop()

        self.pingTimer = TimerTask.timerTask(message, keepalive, self.client)
        self.pingTimer.start()

    def stopPingTimer(self):
        if self.pingTimer is not None:
            self.pingTimer.stop()
            self.pingTimer = None

    def goTimeoutTimer(self):
        if self.timeoutTimer is not None:
            self.timeoutTimer.stop()

        self.timeoutTimer = TimerTask.timerTask(None, 3, self.client)
        self.timeoutTimer.isTimeoutTask = True
        self.timeoutTimer.start()

    def stopTimeoutTimer(self):
        if self.timeoutTimer is not None:
            self.timeoutTimer.stop()
            self.timeoutTimer = None

    def goMessageTimer(self, message):
        if len(self.timersMap) == 1000:
            print('TimersMap : Outgoing identifier overflow')

        if message.getProtocol() == 4 and message.getType() == 'amqpTransfer':
            message.setDeliveryId(self.getNewPacketID()) #np.int64
            timer = TimerTask.timerTask(message, 3, self.client)
            self.timersMap[message.getDeliveryId()] = timer
            timer.start()
            return message.getDeliveryId()
        else:
            if str(type(message).__name__) != 'dict':
                if message.packetID == 0:
                    message.packetID = self.getNewPacketID()
                    if message.getProtocol() == 3: #CoapMessage
                        message.token = str(message.packetID)

                timer = TimerTask.timerTask(message, 3, self.client)
                self.timersMap[message.packetID] = timer
                timer.start()
                return message.packetID
            else:
                if message['packetID'] == None:
                    message['packetID'] = self.getNewPacketID()

                timer = TimerTask.timerTask(message, 3, self.client)
                self.timersMap[message['packetID']] = timer
                timer.start()
                return message['packetID']

    def removeTimer(self, id):
        timer = self.timersMap.get(id)
        if timer is None:
            return None

        message = timer.getMessage()
        timer.stop()
        return message

    def stopTimer(self, id):
        timer = self.timersMap[id]
        if timer is not None:
            message = timer.getMessage()
            timer.stop()
            return message
        return None

    def stopAllTimers(self):
        self.stopConnectTimer()
        self.stopPingTimer()
        self.stopTimeoutTimer()

        for timer in self.timersMap.values():
            if timer is not None:
                timer.stop()

        self.timersMap = {}
        self.count = 0

    def getNewPacketID(self):
        self.count += 1

        if self.count > 65535:
            self.count = 1

        return self.count
