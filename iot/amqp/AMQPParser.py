import iot.amqp.avps.HeaderCode as HeaderCode
import iot.amqp.header.api.HeaderFactory as HeaderFactory
import iot.amqp.header.impl.AMQPPing as AMQPPing
import iot.amqp.header.impl.AMQPProtoHeader as AMQPProtoHeader
import iot.amqp.numeric.NumericUtil as NumericUtil

class amqpParser():
    def __init__(self):
        self.index = 0
    
    def next(self, data, index):
        length = NumericUtil.util.getInt(data[self.index:self.index + 4])
        self.index = index + 4
        if length == 1095586128:
            protocolId = NumericUtil.util.getByte(data, self.index)
            self.index += 1
            versionMajor = NumericUtil.util.getByte(data, self.index)
            self.index += 1
            versionMinor = NumericUtil.util.getByte(data, self.index)
            self.index += 1
            versionRevision = NumericUtil.util.getByte(data, self.index)
            self.index += 1
            if (protocolId == 0 or protocolId == 3) and versionMajor == 1 and versionMinor == 0 and versionRevision == 0:
                self.index = 0
                return data[index: 8]

        self.index = 0
        return data[index:length]
    
    def encode(self, header):
        buf = None

        if header.toStringShort() == 'AMQPProtoHeader':
            buf = bytearray()
            buf = NumericUtil.util.addString(buf,'AMQP')
            buf = NumericUtil.util.addByte(buf,header.getProtocolId())
            buf = NumericUtil.util.addByte(buf, header.getVersionMajor())
            buf = NumericUtil.util.addByte(buf, header.getVersionMinor())
            buf = NumericUtil.util.addByte(buf, header.getVersionRevision())
            return buf

        if header.toString() == 'AMQPPing':
            buf = bytearray()
            buf = NumericUtil.util.addInt(buf,8)
            buf = NumericUtil.util.addByte(buf,header.getDoff())
            buf = NumericUtil.util.addByte(buf, header.getType())
            buf = NumericUtil.util.addShort(buf, header.getChannel())
            return buf

        length = 8
        arguments = header.toArgumentsList()
        length += arguments.getLength()

        sections = None
        headerCode = HeaderCode.headerCode()
        if header.getCode() == headerCode.getValueByKey('TRANSFER'):
            sections = header.getSections()
            if sections is not None:
                for section in sections.values():
                    length += section.getValue().getLength()

        buf = bytearray()
        buf = NumericUtil.util.addInt(buf,length)
        buf = NumericUtil.util.addByte(buf,header.getDoff())
        buf = NumericUtil.util.addByte(buf, header.getType())
        buf = NumericUtil.util.addShort(buf, header.getChannel())

        if arguments.toString() == 'TLVList':
            buf += arguments.getBytes()

        if sections is not None:
            for section in sections.values():
                value = section.getValue()
                buf += value.getBytes()

        self.index = 0
        return buf
    
    def decode(self, data):
        length = NumericUtil.util.getInt(data[self.index:self.index+4])
        self.index += 4
        doff = NumericUtil.util.getByte(data,self.index) & 0xff
        self.index += 1
        type = NumericUtil.util.getByte(data,self.index) & 0xff
        self.index += 1
        channel = NumericUtil.util.getShort(data[self.index:self.index+2]) & 0xffff
        self.index += 2

        if length == 8 and doff == 2 and (type == 0 or type == 1) and channel == 0:
            if self.index >= len(data):
                self.index = 0
                return AMQPPing.amqpPing()
            else:
                print("Received malformed ping-header with invalid length")

        if length == 1095586128 and (doff == 3 or doff == 0) and type == 1 and channel == 0:
            if self.index >= len(data):
                self.index = 0
                return AMQPProtoHeader.amqpProtoHeader(doff)
            else:
                print("Received malformed protocol-header with invalid length")
        header = None
        
        headerFactory = HeaderFactory.headerFactory(self.index)
        if type == 0:
            header = headerFactory.getAMQP(data)
        elif type == 1:
            header = headerFactory.getSASL(data)
        else:
            print("Received malformed header with invalid type: " + type)

        self.index = headerFactory.getIndex()
        
        header.setDoff(doff)
        header.setType(type)
        header.setChannel(channel)
        headerCode = HeaderCode.headerCode()
        if header.getCode() == headerCode.getValueByKey('TRANSFER'):
            header.setSections({})
            while self.index < len(data):
                headerFactory.setIndex(self.index)
                section = headerFactory.getSection(data)
                header.sections[section.getCode()] = section
                self.index = headerFactory.getIndex()
        
        self.index = 0
        return header
