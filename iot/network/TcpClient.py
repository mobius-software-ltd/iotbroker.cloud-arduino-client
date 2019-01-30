import socket
import ssl

class tcpClient():
    def __init__(self, host, port, client):
        self.host = host
        self.port = port
        self.client = client
        self.connection = None

    def connectSecure(self, certfile, keyfile):
        addr = (self.host, self.port)
        context = ssl.create_ssl_context(certfile, None, keyfile, addr, ssl.SERVER_AUTH)
        self.connection = ssl.sslsocket(socket.AF_INET, socket.SOCK_STREAM, socket.IPPROTO_TCP, context)
        #self.connection = ssl.sslsocket(socket.SOCK_STREAM)
        self.connection.connect((self.host, self.port))
        print("Connected (secured) to {0}:{1}".format(self.host, self.port))
        self.client.setState(5) #CONNECTION_ESTABLISHED

    def connect(self):
        self.connection = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.connection.connect((self.host, self.port))
        print("Connected to {0}:{1}".format(self.host,self.port))
        self.client.setState(5) #CONNECTION_ESTABLISHED

    def sendMessage(self, message):
        self.connection.send(message)
        print("was sended: " + str(bytes(message)))
        data = self.connection.recv(1024)
        if data is not None:
            self.dataReceived(data)
        else:
            print('Data was empty')

    def disconnect(self):
        self.connection.close()

    def dataReceived(self, data):
        print("Server said:", data)
        self.client.dataReceived(data)
