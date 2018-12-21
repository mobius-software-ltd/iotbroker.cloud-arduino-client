import iot.amqp.avps.AMQPType as AMQPType
import iot.amqp.avps.DistributionMode as DistributionMode
import iot.amqp.avps.TerminusDurability as TerminusDurability
import iot.amqp.avps.TerminusExpiryPolicy as TerminusExpiryPolicy
import iot.amqp.constructor.DescribedConstructor as DescribedConstructor
import iot.amqp.header.api.AMQPUnwrapper as AMQPUnwrapper
import iot.amqp.header.api.AMQPWrapper as AMQPWrapper
import iot.amqp.header.api.HeaderFactoryOutcome as HeaderFactoryOutcome
import iot.amqp.wrappers.AMQPSymbol as AMQPSymbol
import iot.amqp.tlv.impl.TLVList as TLVList
import iot.amqp.tlv.impl.TLVFixed as TLVFixed

class amqpSource():
    def __init__(self,address,durable,expiryPeriod,timeout,dynamic,dynamicNodeProperties,distributionMode,filter,defaultOutcome,outcomes,capabilities):
        self.address = address
        self.durable = durable
        self.expiryPeriod = expiryPeriod
        self.timeout = timeout
        self.dynamic = dynamic
        self.dynamicNodeProperties = dynamicNodeProperties
        self.distributionMode = distributionMode
        self.filter = filter
        self.defaultOutcome = defaultOutcome
        self.outcomes = outcomes
        self.capabilities = capabilities
        self.index = 0
        self.amqpType = AMQPType.amqpType()

    def toArgumentsList(self):
        list = TLVList.tlvList(None,None)
        wrapper = AMQPWrapper.amqpWrapper()
        if self.address is not None:
            list.addElement(0, wrapper.wrap(self.address))
        if self.durable is not None:
            list.addElement(1, wrapper.wrap(self.durable))
        if self.expiryPeriod is not None:
            list.addElement(2, wrapper.wrap(AMQPSymbol.amqpSymbol(self.expiryPeriod.value)))
        if self.timeout is not None:
            list.addElement(3, wrapper.wrap(self.timeout))
        if self.dynamic is not None:
            list.addElement(4, wrapper.wrap(self.dynamic))
        if self.dynamicNodeProperties is not None and isinstance(self.dynamicNodeProperties,dict):
            if self.dynamic is not None:
                if self.dynamic:
                    list.addElement(5, wrapper.wrapMap(self.dynamicNodeProperties))
                else:
                    print("Source's dynamic-node-properties can't be specified when dynamic flag is false")
            else:
                print("Source's dynamic-node-properties can't be specified when dynamic flag is not set")

        if self.distributionMode is not None:
            list.addElement(6, wrapper.wrap(AMQPSymbol.amqpSymbol(self.distributionMode.value)))
        if self.filter is not None and isinstance(self.filter, dict):
            list.addElement(7, wrapper.wrapMap(self.filter))
        if self.defaultOutcome is not None:
            list.addElement(8, self.defaultOutcome.toArgumentsList())
        if self.outcomes is not None and len(self.outcomes) > 0:
            list.addElement(9, wrapper.wrapArray(self.outcomes))
        if self.capabilities is not None and len(self.capabilities) > 0:
            list.addElement(10, wrapper.wrapArray(self.capabilities))

        constructor = DescribedConstructor.describedConstructor(list.getCode(),TLVFixed.tlvFixed(self.amqpType.getValueByKey('SMALL_ULONG'), 0x28))
        list.setConstructor(constructor)
        return list

    def fromArgumentsList(self, list):
        unwrapper = AMQPUnwrapper.amqpUnwrapper()
        if isinstance(list, TLVList):
            if len(list.getList()) > 0 :
                element = list.getList()[0]
                if element is not None and not element.isNull():
                    self.address = unwrapper.unwrapString(element)
            if len(list.getList()) > 1 :
                element = list.getList()[1]
                if element is not None and not element.isNull():
                    self.durable = TerminusDurability.terminusDurability(unwrapper.unwrapUInt(element))
            if len(list.getList()) > 2 :
                element = list.getList()[2]
                if element is not None and not element.isNull():
                    self.expiryPeriod = TerminusExpiryPolicy.terminusExpiryPolicy(unwrapper.unwrapSymbol(element))
            if len(list.getList()) > 3 :
                element = list.getList()[3]
                if element is not None and not element.isNull():
                    self.timeout = unwrapper.unwrapUInt(element)
            if len(list.getList()) > 4 :
                element = list.getList()[4]
                if element is not None and not element.isNull():
                    self.dynamic = unwrapper.unwrapBool(element)
            if len(list.getList()) > 5 :
                element = list.getList()[5]
                if element is not None and not element.isNull():
                    if self.dynamic is not None:
                        if self.dynamic:
                            self.dynamicNodeProperties = unwrapper.unwrapMap(element)
                        else:
                            print("Received malformed Source: dynamic-node-properties can't be specified when dynamic flag is false")
                    else:
                        print("Received malformed Source: dynamic-node-properties can't be specified when dynamic flag is not set")

            if len(list.getList()) > 6 :
                element = list.getList()[6]
                if element is not None and not element.isNull():
                    self.distributionMode = DistributionMode.distributionMode(unwrapper.unwrapSymbol(element))
            if len(list.getList()) > 7:
                element = list.getList()[7]
                if element is not None and not element.isNull():
                    self.filter = unwrapper.unwrapMap(element)

            if len(list.getList()) > 8:
                element = list.getList()[8]
                if element is not None and not element.isNull():
                    code = element.getCode()
                    if code not in (self.amqpType.getValueByKey('LIST_0'),self.amqpType.getValueByKey('LIST_8'),self.amqpType.getValueByKey('LIST_32')):
                        print('Expected type OUTCOME - received: ' + element.getCode())


                self.defaultOutcome = HeaderFactoryOutcome.headerFactoryOutcome.getOutcome(element)
                self.defaultOutcome.fromArgumentsList(element)

            if len(list.getList()) > 9:
                element = list.getList()[9]
                if element is not None and not element.isNull():
                    self.outcomes = unwrapper.unwrapArray(element)
            if len(list.getList()) > 10:
                element = list.getList()[10]
                if element is not None and not element.isNull():
                    self.capabilities = unwrapper.unwrapArray(element)

    def toString(self):
        return 'AMQPSource [address=' + str(self.address) + ', durable=' + str(self.durable) + ', expiryPeriod=' + str(self.expiryPeriod) + ', timeout=' + str(self.timeout) + ', dynamic=' + str(self.dynamic) + ', dynamicNodeProperties=' + str(self.dynamicNodeProperties) + ', distributionMode=' + str(self.distributionMode) + ', filter=' + str(self.filter) + ', defaultOutcome=' + str(self.defaultOutcome) + ', outcomes=' + str(self.outcomes) + ', capabilities=' + str(self.capabilities) + ']'

    def getAddress(self):
        return self.address

    def setAddress(self, address):
        self.address = address

    def getDurable(self):
        return self.durable

    def setDurable(self, durable):
        self.durable = durable

    def getExpiryPeriod(self):
        return self.expiryPeriod

    def setExpiryPeriod(self, expiryPeriod):
        self.expiryPeriod = expiryPeriod

    def getTimeout(self):
        return self.timeout

    def setTimeout(self, timeout):
        self.timeout = timeout

    def getDynamic(self):
        return self.dynamic

    def setDynamic(self, dynamic):
        self.dynamic = dynamic

    def getDynamicNodeProperties(self):
        return self.dynamicNodeProperties

    def setDynamicNodeProperties(self, dynamicNodeProperties):
        self.dynamicNodeProperties = dynamicNodeProperties

    def getDistributionMode(self):
        return self.distributionMode

    def setDistributionMode(self, distributionMode):
        self.distributionMode = distributionMode

    def getFilter(self):
        return self.filter

    def setFilter(self, filter):
        self.filter = filter

    def getDefaultOutcome(self):
        return self.defaultOutcome

    def setDefaultOutcome(self, defaultOutcome):
        self.defaultOutcome = defaultOutcome

    def getOutcomes(self):
        return self.outcomes

    def setOutcomes(self, outcomes):
        self.outcomes = outcomes

    def getCapabilities(self):
        return self.capabilities

    def setCapabilities(self, capabilities):
        self.capabilities = capabilities
