import socket
import ssl
import iot.classes.ConnectionState as ConnectionState

class tcpClient():
    def __init__(self, host, port, client):
        self.host = host
        self.port = port
        self.client = client
        self.connection = None
        self.connectionState = ConnectionState.connectionState()

    def connectSecure(self, ssl_keyfile, ssl_certfile):
        context = ssl.create_default_context(ssl.Purpose.SERVER_AUTH)
        context.load_cert_chain(certfile = ssl_certfile, keyfile = ssl_keyfile)
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.settimeout(10)
        if len(ssl_keyfile)>0 and len(ssl_certfile)>0:
            self.connection = context.wrap_socket(sock)
        else:
            self.connection = ssl.wrap_socket(sock)
        self.connection.connect((self.host, self.port))
        print("Connected (secured) to {0}:{1}".format(self.host, self.port))
        self.client.setState(self.connectionState.getValueByKey('CONNECTION_ESTABLISHED'))

    def connect(self):
        self.connection = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.connection.connect((self.host, self.port))
        print("Connected to {0}:{1}".format(self.host,self.port))
        self.client.setState(self.connectionState.getValueByKey('CONNECTION_ESTABLISHED'))

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


