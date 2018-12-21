from crypto.hash import sha1 as sha1
import base64

handshake = (
        "GET /ws HTTP/1.1\r\n"
        "Upgrade: WebSocket\r\n"
        "Connection: Upgrade\r\n"
        "Sec-Websocket-Key: %(key)s\r\n"
        "Sec-Websocket-Version: 13\r\n"
        "\r\n"
    )

class util():
    def response_decode(self, data):
        arr = data.decode("utf-8").split("\r\n")
        arr = arr[1:]
        arr = set(arr)
        arr.remove('')
        map = {}
        for item in arr:
            key, value = item.split(':')
            map[key.strip()] = value.strip()
        return map

    def get_accept(self, key):
       m = sha1.SHA1()
       concat = key + '258EAFA5-E914-47DA-95CA-C5AB0DC85B11' #Globally Unique Identifier (GUID, [RFC4122])
       m.update(concat.encode())
       digest = m.digest()
       encoded = base64.standard_b64encode(digest)
       return encoded.decode()
