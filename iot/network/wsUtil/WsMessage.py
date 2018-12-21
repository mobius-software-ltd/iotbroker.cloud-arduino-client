import json

class wsMessage():
    def __init__(self, fin, opcode, mask, payload):
        self.fin = fin
        self.opcode = opcode
        self.mask = mask
        self.payload = payload

    def getLength(self):
        payload = json.dumps(self.payload)
        if len(payload) > 0:
            return len(payload)
        else:
            return None

    def setFin(self, fin):
        self.fin = fin

    def getFin(self):
        return self.fin

    def setOpcode(self, opcode):
        self.opcode = opcode

    def getOpcode(self):
        return self.opcode

    def setMask(self, mask):
        self.mask = mask

    def getMask(self):
        return self.mask

    def setPayload(self, payload):
        self.payload = payload

    def getPayload(self):
        return self.payload
