import iot.coap.options.CoapOption as CoapOption
import iot.coap.options.CoapOptionType as CoapOptionType
import struct

class optionParser():
    def __init__(self):
        self.coapOptionType = CoapOptionType.coapOptionType()
        self.coapOption = CoapOption.coapOption()

    def encode(self, type, value):
        encoded = self.encodeWithType(type, value)
        option = CoapOption.coapOption(type,len(encoded),encoded)
        return option

    def encodeWithType(self, type, value):
        encoded = bytearray()
        if type == self.coapOptionType.getValueByKey('URI_PORT') or type == self.coapOptionType.getValueByKey('ACCEPT') or type == self.coapOptionType.getValueByKey('CONTENT_FORMAT'):
            encoded = addShort(encoded, value)
        if type == self.coapOptionType.getValueByKey('MAX_AGE') or type == self.coapOptionType.getValueByKey('SIZE1') or type == self.coapOptionType.getValueByKey('OBSERVE'):
            encoded = addInt(encoded, value)
        if type == self.coapOptionType.getValueByKey('IF_MATCH') or type == self.coapOptionType.getValueByKey('ETAG') or type == self.coapOptionType.getValueByKey('NODE_ID') or type == self.coapOptionType.getValueByKey('URI_PATH') or type == self.coapOptionType.getValueByKey('LOCATION_PATH') or type == self.coapOptionType.getValueByKey('URI_QUERY') or type == self.coapOptionType.getValueByKey('LOCATION_QUERY') or type == self.coapOptionType.getValueByKey('URI_HOST') or type == self.coapOptionType.getValueByKey('PROXY_SCHEME') or type == self.coapOptionType.getValueByKey('PROXY_URI'):
            encoded = addString(encoded, value)
        return encoded

    def decode(self, type, encoded):
        self.validateLength(type, encoded.getLength())
        return self.decodeWithType(type,encoded.getValue())

    def decodeWithType(self, type, encoded):
        if type == self.coapOptionType.getValueByKey('URI_PORT') or type == self.coapOptionType.getValueByKey('ACCEPT') or type == self.coapOptionType.getValueByKey('CONTENT_FORMAT'):
            return getShort(encoded)
        if type == self.coapOptionType.getValueByKey('MAX_AGE') or type == self.coapOptionType.getValueByKey('SIZE1') or type == self.coapOptionType.getValueByKey('OBSERVE'):
            return getInt(encoded)

        if type == self.coapOptionType.getValueByKey('IF_MATCH') or type == self.coapOptionType.getValueByKey('ETAG') or type == self.coapOptionType.getValueByKey('NODE_ID') or type == self.coapOptionType.getValueByKey('URI_PATH') or type == self.coapOptionType.getValueByKey('LOCATION_PATH') or type == self.coapOptionType.getValueByKey('URI_QUERY') or type == self.coapOptionType.getValueByKey('LOCATION_QUERY') or type == self.coapOptionType.getValueByKey('URI_HOST') or type == self.coapOptionType.getValueByKey('PROXY_SCHEME') or type == self.coapOptionType.getValueByKey('PROXY_URI'):
            return getString(encoded)

        if type == self.coapOptionType.getValueByKey('IF_NONE_MATCH'):
            return bytearray()

    def validateLength(self, type, length):
        if type == self.coapOptionType.getValueByKey('URI_PORT') or type == self.coapOptionType.getValueByKey('ACCEPT') or type == self.coapOptionType.getValueByKey('CONTENT_FORMAT'):
            if length > 2:
                print('Error.OptionParser.Invalid length 0-2: type = ' + str(type))
        if type == self.coapOptionType.getValueByKey('MAX_AGE') or type == self.coapOptionType.getValueByKey('SIZE1') or type == self.coapOptionType.getValueByKey('OBSERVE'):
            if length > 4:
                print('Error.OptionParser.Invalid length 0-4: type = ' + str(type))
        if type == self.coapOptionType.getValueByKey('IF_MATCH'):
            if length > 8:
                print('Error.OptionParser.Invalid length 0-8: type = ' + str(type))
        if type == self.coapOptionType.getValueByKey('ETAG'):
            if length > 8:
                print('Error.OptionParser.Invalid length 1-8: type = ' + str(type))
        if type == self.coapOptionType.getValueByKey('NODE_ID') or type == self.coapOptionType.getValueByKey('URI_PATH') or type == self.coapOptionType.getValueByKey('LOCATION_PATH') or type == self.coapOptionType.getValueByKey('URI_QUERY') or type == self.coapOptionType.getValueByKey('LOCATION_QUERY'):
            if length > 255:
                print('Error.OptionParser.Invalid length 0-255: type = ' + str(type))
        if type == self.coapOptionType.getValueByKey('URI_HOST') or type == self.coapOptionType.getValueByKey('PROXY_SCHEME'):
            if length == 0 or length > 255:
                print('Error.OptionParser.Invalid length 1-255: type = ' + str(type))
        if type == self.coapOptionType.getValueByKey('PROXY_URI'):
            if length == 0 or length > 1034:
                print('Error.OptionParser.Invalid length 1-1034: type = ' + str(type))
        if type == self.coapOptionType.getValueByKey('IF_NONE_MATCH'):
            if length > 0:
                print('Error.OptionParser.Invalid length 0: type = ' + str(type))

def addShort(data, short):
    dataStruct  = struct.pack('h', short)
    data += dataStruct[::-1]
    return data

def getShort(data):
    tuple = struct.unpack('h', data[::-1])
    return tuple[0]

def addInt(data, int):
    dataStruct  = struct.pack('i', int)
    data += dataStruct[::-1]
    return data

def getInt(data):
    tuple = struct.unpack('i', data[::-1])
    return tuple[0]

def addString(dataIn, text):
    data = dataIn
    for ch in text:
        ch = bytes(ch, encoding='utf_8')
        data += struct.pack('c', ch)
    return data

def getString(data):
    return data.decode('utf_8')
