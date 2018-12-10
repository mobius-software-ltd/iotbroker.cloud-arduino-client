class errorCode():
    def __init__(self):
        self.dict = {'INTERNAL_ERROR':'amqp:internal-error','NOT_FOUND':'amqp:not-found','UNAUTHORIZED_ACCESS':'amqp:unauthorized-access','DECODE_ERROR':'amqp:decode-error','RESOURCE_LIMIT_EXCEEDED':'amqp:resource-limit-exceeded','NOT_ALLOWED':'amqp:not-allowed','INVALID_FIELD':'amqp:invalid-field','NOT_IMPLEMENTED':'amqp:not-implemented','RESOURCE_LOCKED':'amqp:resource-locked','PRECONDITION_FAILED':'amqp:precondition-failed','RESOURCE_DELETED':'amqp:resource-deleted','ILLEGAL_STATE':'amqp:illegal-state','FRAME_SIZE_TOO_SMALL':'amqp:frame-size-too-small','CONNECTION_FORCED':'amqp:connection-forced','FRAMING_ERROR':'amqp:framing-error','REDIRECTED':'amqp:redirected','WINDOW_VIOLATION':'amqp:window-violation','ERRANT_LINK':'amqp:errant-link','HANDLE_IN_USE':'amqp:handle-in-use','UNATTACHED_HANDLE':'amqp:unattached-handle','DETACH_FORCED':'amqp:detach-forced','TRANSFER_LIMIT_EXCEEDED':'amqp:transfer-limit-exceeded','MESSAGE_SIZE_EXCEEDED':'amqp:message-size-exceeded','REDIRECT':'amqp:redirect','STOLEN':'amqp:stolen'}

    def getValueByKey(self, key):
        return self.dict.get(key)

    def getKeyByValue(self, valueSearch):
        for key, value in self.dict.items():
            if value == valueSearch:
                return key










