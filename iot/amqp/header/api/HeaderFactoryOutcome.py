import iot.amqp.avps.StateCode as StateCode
import iot.amqp.tlv.impl.AMQPAccepted as AMQPAccepted
import iot.amqp.tlv.impl.AMQPModified as AMQPModified
import iot.amqp.tlv.impl.AMQPReceived as AMQPReceived
import iot.amqp.tlv.impl.AMQPRejected as AMQPRejected
import iot.amqp.tlv.impl.AMQPReleased as AMQPReleased

class headerFactoryOutcome():

    def getOutcome(list):
        outcome = None
        byteCode = list.getConstructor().getDescriptorCode()
        code = StateCode.stateCode(byteCode)
        if code == StateCode.stateCode.getValueByKey('ACCEPTED'):
            outcome = AMQPAccepted.amqpAccepted()
        elif code == StateCode.stateCode.getValueByKey('MODIFIED'):
            outcome = AMQPModified.amqpModified(None ,None ,None)
        elif code == StateCode.stateCode.getValueByKey('REJECTED'):
            outcome = AMQPRejected.amqpRejected(None)
        elif code == StateCode.stateCode.getValueByKey('RELEASED'):
            outcome = AMQPReleased.amqpReleased()
        else:
            print('Received header with unrecognized outcome code')
        return outcome

    def getState(list):
        state = None
        byteCode = list.getConstructor().getDescriptorCode()
        code = StateCode.stateCode(byteCode)
        if code == StateCode.stateCode.getValueByKey('ACCEPTED'):
            state = AMQPAccepted.amqpAccepted()
        elif code == StateCode.stateCode.getValueByKey('MODIFIED'):
            state = AMQPModified.amqpModified(None ,None ,None)
        elif code == StateCode.stateCode.getValueByKey('RECEIVED'):
            state = AMQPReceived.amqpReceived(None,None)
        elif code == StateCode.stateCode.getValueByKey('REJECTED'):
            state = AMQPRejected.amqpRejected(None)
        elif code == StateCode.stateCode.getValueByKey('RELEASED'):
            state = AMQPReleased.amqpReleased()
        else:
            print('Received header with unrecognized state code')
        return state
