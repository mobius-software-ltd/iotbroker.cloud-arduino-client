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
        stateCode = StateCode.stateCode()
        code = stateCode.getKeyByValue(byteCode)
        if code == 'ACCEPTED':
            outcome = AMQPAccepted.amqpAccepted()
        elif code == 'MODIFIED':
            outcome = AMQPModified.amqpModified(None ,None ,None)
        elif code == 'REJECTED':
            outcome = AMQPRejected.amqpRejected(None)
        elif code == 'RELEASED':
            outcome = AMQPReleased.amqpReleased()
        else:
            print('Received header with unrecognized outcome code')
        return outcome

    def getState(list):
        state = None
        byteCode = list.getConstructor().getDescriptorCode()
        stateCode = StateCode.stateCode()
        code = stateCode.getKeyByValue(byteCode)
        if code == 'ACCEPTED':
            state = AMQPAccepted.amqpAccepted()
        elif code == 'MODIFIED':
            state = AMQPModified.amqpModified(None ,None ,None)
        elif code == 'RECEIVED':
            state = AMQPReceived.amqpReceived(None,None)
        elif code == 'REJECTED':
            state = AMQPRejected.amqpRejected(None)
        elif code == 'RELEASED':
            state = AMQPReleased.amqpReleased()
        else:
            print('Received header with unrecognized state code')
        return state
