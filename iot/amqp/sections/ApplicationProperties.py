import iot.amqp.header.api.AMQPWrapper as AMQPWrapper
import iot.amqp.header.api.AMQPUnwrapper as AMQPUnwrapper
import iot.amqp.constructor.DescribedConstructor as DescribedConstructor
import iot.amqp.avps.SectionCode as SectionCode
import iot.amqp.tlv.impl.TLVFixed as TLVFixed
import iot.amqp.tlv.impl.TLVMap as TLVMap
import iot.amqp.avps.AMQPType as AMQPType

class applicationProperties():
    def __init__(self, properties):
        self.properties = properties

    def getValue(self):
        map = TLVMap.tlvMap(None, None)
        wrapper = AMQPWrapper.amqpWrapper() 
        if self.properties is not None and len(self.properties) > 0:
            map = wrapper.wrapMap(self.properties)

        constructor = DescribedConstructor.describedConstructor(map.getCode(), TLVFixed.tlvFixed(AMQPType.amqpType.getValueByKey('SMALL_ULONG'), 0x74))
        map.setConstructor(constructor)
        return map

    def fill(self, map):
        unwrapper = AMQPUnwrapper.amqpUnwrapper()
        if map is not None:
            self.annotations = unwrapper.unwrapMap(map)

    def getCode(self):
        return SectionCode.sectionCode.getValueByKey('APPLICATION_PROPERTIES')

    def toString(self):
        return 'ApplicationProperties [properties=' + str(self.properties) + ']'

    def getProperties(self):
        return self.properties

    def setProperties(self, properties):
        self.properties = properties
