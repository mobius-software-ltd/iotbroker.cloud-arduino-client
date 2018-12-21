import iot.amqp.numeric.NumericUtil as NumericUtil
import struct
import json

class wsParser():

    def encode(message):
        data = bytearray()
        if message.getFin():
            firstByte = 128
        else:
            firstByte = 0

        firstByte = firstByte + int(message.getOpcode(), 16)
        data.append(firstByte)

        # second byte (mask always True)
        length = message.getLength()
        if length < 128:
            data.append(128+length)
        else:
            data.append(254)
            NumericUtil.util.addShort(data, length)

        # masking key
        mask = bytearray()
        mask.append(random(1, 255))
        mask.append(random(1, 255))
        mask.append(random(1, 255))
        mask.append(random(1, 255))
        data += mask

        #payload
        masked = bytearray()
        payload = message.getPayload()
        payload = json.dumps(payload)
        NumericUtil.util.addString(masked, payload)
        for i in range(len(payload)):
            masked[i] = masked[i] ^ mask[i % 4]
        data += masked

        return data

    def decode(data):
        lengthTuple = struct.unpack('B', data[1:2])
        length = lengthTuple[0]
        payload = data[2:len(data)].decode('utf8')
        return payload
