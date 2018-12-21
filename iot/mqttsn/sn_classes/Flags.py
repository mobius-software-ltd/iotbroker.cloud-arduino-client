import iot.classes.QosType as QosType
import iot.mqttsn.sn_classes.Flag as Flag
import iot.mqttsn.sn_classes.TopicType as TopicType
import iot.mqttsn.sn_classes.SNmessageType as SNmessageType

class Flags():
    def __init__(self, dup, qos, retain, will, cleanSession, topicType):

        self.dup = dup
        if qos is not None:
            self.qos = qos
        else:
            self.qos = None
        self.retain = retain
        self.will = will
        self.cleanSession = cleanSession
        self.topicType = topicType
        self.qosType = QosType.qosType()
        self.flag = Flag.flag()
        self.snMessageType = SNmessageType.snMessageType()
        self.topicTypeEnum = TopicType.topicType()

    def isDup(self):
        return self.dup

    def setDup(self, dup):
        self.dup = dup

    def getQoS(self):
        return self.qos

    def setQoS(self, qos):
        self.qos = qos

    def isRetain(self):
        return self.retain

    def setRetain(self, retain):
        self.retain = retain

    def isWill(self):
        return self.will

    def setWill(self, will):
        self.will = will

    def isClean(self):
        return self.cleanSession

    def setClean(self, clean):
        self.cleanSession = clean

    def getTopicType(self):
        return self.topicType

    def setTopicType(self, topicType):
        self.topicType = topicType

    def encode(self):
        flagsByte = 0
        if self.dup:
            flagsByte += 128 #Flag.DUPLICATE
        if self.qos is not None:
            flagsByte += self.qos.getValue() << 5
        if self.retain:
            flagsByte += 16 #Flag.RETAIN
        if self.isWill():
            flagsByte += 8 #Flag.WILL
        if self.isClean():
            flagsByte += 4 #Flag.CLEAN_SESSION
        if self.topicType is not None:
            flagsByte += self.topicType.value[0]
        return flagsByte

    def decode(self,flagsByte, type):
        flags = []
        bitmask = []
        flags.append(128) #Flag.DUPLICATE
        flags.append(96) #Flag.QOS_LEVEL_ONE
        flags.append(64) #Flag.QOS_2
        flags.append(32) #Flag.QOS_1
        flags.append(16) #Flag.RETAIN
        flags.append(8) #Flag.WILL
        flags.append(4) #Flag.CLEAN_SESSION
        flags.append(3) #Flag.RESERVED_TOPIC
        flags.append(2) #Flag.SHORT_TOPIC
        flags.append(1) #Flag.ID_TOPIC

        for flag in flags:
            if ((flagsByte & flag) == flag):
                bitmask.append(flag)
        return self.validateAndCreate(bitmask,type)

    def validateAndCreate(self, bitmask, type):
        dup = False
        retain = False
        will = False
        clean = False
        if 3 in bitmask: #RESERVED_TOPIC
            print('Error. Reserved flag set to true in SNFlags')
        if 128 in bitmask: #DUPLICATE
            dup = True
        if 16 in bitmask: #RETAIN
            retain = True
        if 8 in bitmask: #WILL
            will = True
        if 4 in bitmask: #CLEAN_SESSION
            clean = True

        qos = self.qosType.getValueByKey('AT_MOST_ONCE')
        if self.flag.getValueByKey('QOS_LEVEL_ONE') in bitmask:
            qos = QosType.LEVEL_ONE.value[0]
        if  self.flag.getValueByKey('QOS_2') in bitmask:
            qos = QosType.EXACTLY_ONCE.value[0]
        if self.flag.getValueByKey('QOS_1') in bitmask:
            qos = QosType.AT_LEAST_ONCE.value[0]

        topicType = self.topicType.getValueByKey('NAMED')
        if self.flag.getValueByKey('SHORT_TOPIC') in bitmask:
            topicType = self.topicType.getValueByKey('SHORT')
        if self.flag.getValueByKey('ID_TOPIC') in bitmask:
            topicType = self.topicType.getValueByKey('ID')

        if type == self.snMessageType.getValueByKey('SN_CONNECT'):
            if dup:
                print('Error. SNFlags. Invalid encoding: dup flag = ' + str(type))
            if qos != self.qosType.getValueByKey('AT_MOST_ONCE'):
                print('Error. SNFlags. Invalid encoding: qos flag = ' + str(type))
            if retain:
                print('Error. SNFlags. Invalid encoding: retain flag = ' + str(type))
            if topicType != TopicType.NAMED:
               print('Error. SNFlags. Invalid encoding: topicType flag = ' + str(type))

        if type ==  self.snMessageType.getValueByKey('SN_WILL_TOPIC'):
            if dup:
                print('Error. SNFlags. Invalid encoding: dup flag = ' + str(type))
            if qos is None:
                print('Error. SNFlags. Invalid encoding: qos flag = ' + str(type))
            if will:
                print('Error. SNFlags. Invalid encoding: will flag = ' + str(type))
            if clean:
                print('Error. SNFlags. Invalid encoding: clean flag = ' + str(type))
            if topicType != self.topicTypeEnum.getValueByKey('NAMED'):
                print('Error. SNFlags. Invalid encoding: topicType flag = ' + str(type))

        if type == self.snMessageType.getValueByKey('SN_PUBLISH'):
            if qos is None:
                print('Error. SNFlags. Invalid encoding: qos flag = ' + str(type))
            if dup & (qos == self.qosType.getValueByKey('AT_MOST_ONCE') or qos == self.qosType.getValueByKey('LEVEL_ONE')):
                print('Error. SNFlags. Invalid encoding: dup flag = ' + str(type))
            if will:
                print('Error. SNFlags. Invalid encoding: will flag = ' + str(type))
            if clean:
                print('Error. SNFlags. Invalid encoding: clean flag = ' + str(type))
            if topicType != self.topicTypeEnum.getValueByKey('NAMED') and topicType != self.topicTypeEnum.getValueByKey('SHORT') and topicType != self.topicTypeEnum.getValueByKey('ID'):
                print('Error. SNFlags. Invalid encoding: topicType flag = ' + str(type))

        if type == self.snMessageType.getValueByKey('SN_SUBSCRIBE'):
            if qos is None:
               print('Error. SNFlags. Invalid encoding: qos flag = ' + str(type))
            if qos == self.qosType.getValueByKey('LEVEL_ONE'):
                print('Error. SNFlags. Invalid encoding: qos flag = ' + str(type))
            if retain:
                print('Error. SNFlags. Invalid encoding: retain flag = ' + str(type))
            if will:
                print('Error. SNFlags. Invalid encoding: will flag = ' + str(type))
            if clean:
                print('Error. SNFlags. Invalid encoding: clean flag = ' + str(type))
            if topicType != self.topicTypeEnum.getValueByKey('NAMED') and topicType != self.topicTypeEnum.getValueByKey('SHORT') and topicType != self.topicTypeEnum.getValueByKey('ID'):
                print('Error. SNFlags. Invalid encoding: topicType flag = ' + str(type))

        if type == self.snMessageType.getValueByKey('SN_SUBACK'):
            if dup:
                print('Error. SNFlags. Invalid encoding: dup flag = ' + str(type))
            if qos is None:
                print('Error. SNFlags. Invalid encoding: qos flag = ' + str(type))
            if retain:
                print('Error. SNFlags. Invalid encoding: retain flag = ' + str(type))
            if will:
                print('Error. SNFlags. Invalid encoding: will flag = ' + str(type))
            if clean:
                print('Error. SNFlags. Invalid encoding: clean flag = ' + str(type))
            if topicType != self.topicTypeEnum.getValueByKey('NAMED'):
                print('Error. SNFlags. Invalid encoding: topicType flag = ' + str(type))

        if type == self.snMessageType.getValueByKey('SN_UNSUBSCRIBE'):
            if dup:
                print('Error. SNFlags. Invalid encoding: dup flag = ' + str(type))
            if qos != self.qosType.getValueByKey('AT_MOST_ONCE'):
                print('Error. SNFlags. Invalid encoding: qos flag = ' + str(type))
            if retain:
                print('Error. SNFlags. Invalid encoding: retain flag = ' + str(type))
            if will:
                print('Error. SNFlags. Invalid encoding: will flag = ' + str(type))
            if clean:
                print('Error. SNFlags. Invalid encoding: clean flag = ' + str(type))
            if topicType != self.topicTypeEnum.getValueByKey('NAMED') and topicType != self.topicTypeEnum.getValueByKey('SHORT') and topicType != self.topicTypeEnum.getValueByKey('ID'):
                print('Error. SNFlags. Invalid encoding: topicType flag = ' + str(type))

        if type == self.snMessageType.getValueByKey('SN_WILL_TOPIC_UPD'):
            if dup:
                print('Error. SNFlags. Invalid encoding: dup flag = ' + str(type))
            if qos is None:
                print('Error. SNFlags. Invalid encoding: qos flag = ' + str(type))
            if will:
                print('Error. SNFlags. Invalid encoding: will flag = ' + str(type))
            if clean:
                print('Error. SNFlags. Invalid encoding: clean flag = ' + str(type))
            if topicType != self.topicTypeEnum.getValueByKey('NAMED'):
                print('Error. SNFlags. Invalid encoding: topicType flag = ' + str(type))

            self.dup = dup
            self.retain = retain
            self.qos = qos
            self.will = will
            self.clean = clean
            self.topicType = topicType
            return self
