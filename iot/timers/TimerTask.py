import timers
import iot.classes.ConnectionState as ConnectionState

class timerTask():
    def __init__(self, message, period, client):
        self.message = message
        self.period = period
        self.timer = timers.timer(self.period, self.handle_function)
        self.status = None
        self.isTimeoutTask = False
        self.client = client
        self.connectionState = ConnectionState.connectionState()
        if self.client.connectionState == self.connectionState.getValueByKey('CONNECTION_ESTABLISHED'):
            self.client.send(self.message)
        self.count = 5

    def handle_function(self):
        self.onTimedEvent()
        self.timer = timers.timer(self.period, self.handle_function)
        self.timer.start()
        self.count -= 1
        message = self.message
        if self.count == 0 and (message.getProtocol() == 1 and message.getType() == 12) or (message.getProtocol() == 2 and message.getType() == 22) or (message.getProtocol() == 4 and message.getType() == 'amqpPing'):
            self.client.timeoutMethod()

    def getPeriod(self):
        return self.period

    def getMessage(self):
        return self.message

    def setIsTimeoutTask(self, value):
        self.isTimeoutTask = value

    def start(self):
        self.timer.start()

    def onTimedEvent(self):
        if self.isTimeoutTask == True:
            self.client.timeoutMethod()
        if self.client.connectionState == self.connectionState.getValueByKey('CONNECTION_ESTABLISHED'):
            if self.status == True:
                if (self.message.getProtocol() == 1 and self.message.getType() == 3): #mqttPublish
                    self.message.dup = True
            self.client.send(self.message)
            self.status = True

    def stop(self):
        self.timer.cancel()
