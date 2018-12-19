import iot.amqp.header.api.AMQPWrapper as AMQPWrapper
import iot.amqp.header.api.AMQPUnwrapper as AMQPUnwrapper
import iot.amqp.constructor.DescribedConstructor as DescribedConstructor
import iot.amqp.avps.SectionCode as SectionCode
import iot.amqp.tlv.impl.TLVFixed as TLVFixed
import iot.amqp.tlv.impl.TLVMap as TLVMap
import iot.amqp.avps.AMQPType as AMQPType

class messageAnnotations():
    def __init__(self, annotations):
        self.annotations = annotations

    def getValue(self):
        map = TLVMap.tlvMap(None, None)
        wrapper = AMQPWrapper.amqpWrapper() 
        if self.annotations is not None and len(self.annotations) > 0:
            map = wrapper.wrapMap(self.annotations)

        constructor = DescribedConstructor.describedConstructor(map.getCode(), TLVFixed.tlvFixed(AMQPType.amqpType.getValueByKey('SMALL_ULONG'), 0x72))
        map.setConstructor(constructor)
        return map

    def fill(self, map):
        unwrapper = AMQPUnwrapper.amqpUnwrapper()
        if map is not None:
            self.annotations = unwrapper.unwrapMap(map)

    def getCode(self):
        return SectionCode.sectionCode.getValueByKey('MESSAGE_ANNOTATIONS')

    def toString(self):
        return 'MessageAnnotations [annotations=' + str(self.annotations) + ']'

    def getAnnotations(self):
        return self.annotations

    def setAnnotations(self, annotations):
        self.annotations = annotations
