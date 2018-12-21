import socket
import ssl
import iot.network.wsUtil.Handshake as Handshake
import iot.network.wsUtil.WsMessage as WsMessage
import iot.network.wsUtil.OpCode as OpCode
import iot.network.wsUtil.WsParser as WsParser
import iot.classes.ConnectionState as ConnectionState

class wsTransport():
    def __init__(self, host, port, client):
        self.host = host
        self.port = port
        self.connection = None
        self.client = client
        self.connectionState = ConnectionState.connectionState()

    def connectSecure(self, ssl_keyfile, ssl_certfile):
        context = ssl.create_default_context(ssl.Purpose.SERVER_AUTH)
        context.load_cert_chain(certfile=ssl_certfile, keyfile=ssl_keyfile)
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.settimeout(10)
        if len(ssl_keyfile) > 0 and len(ssl_certfile) > 0:
            self.connection = context.wrap_socket(sock)
        else:
            self.connection = ssl.wrap_socket(sock)
        self.connection.connect((self.host, self.port))
        print("Connected (secured) to {0}:{1}".format(self.host, self.port))
        self.handshake()

    def connect(self):
        self.connection = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.connection.connect((self.host, self.port))
        print("Connected to {0}:{1}".format(self.host, self.port))
        self.handshake()

    def handshake(self):
        #SEND HANDSHAKE
        wskey = {'key': 'dGhlIHNhbXBsZSBub25jZQ=='}
        data = Handshake.handshake % wskey
        self.connection.send(bytes(data, 'utf-8'))

        #RESPONSE
        data = self.connection.recv(1024)
        if data is not None and data != b'':
            response = Handshake.util.response_decode(data)
            if response['upgrade'] == 'websocket' and response['connection'] == 'upgrade':
                if response['sec-websocket-accept'] == Handshake.util.get_accept(wskey['key']) :
                    self.client.setState(self.connectionState.getValueByKey('CONNECTION_ESTABLISHED'))
                else:
                    print('Sec-websocket-accept received from the server was wrong')
            else:
                print("Handshake was not completed because the server's handshake was bad")
        else:
            print('Handshake was not completed because the server is not responding')

    def sendMessage(self, message):
        self.connection.send(message)
        print("was sended: " + str(bytes(message)))
        data = self.connection.recv(2048)
        if data is not None and data != b'':
            self.dataReceived(data)
        else:
            print('Data was empty')

    def disconnect(self):
        self.connection.close()

    def dataReceived(self, data):
        print("Server said:", data)
        decoded = WsParser.Parser.decode(data)
        self.client.dataReceived(decoded)