#ifndef COAPOPTIONPARSER_H
#define COAPOPTIONPARSER_H

#include "iot-protocols/coap/classes/coapenums.h"
#include "iot-protocols/coap/classes/coapoption.h"

class CoapOptionParser
{
private:
    static unsigned char * encodeMethod(CoAPOptionDefinitions option, JsonVariant object);
    static JsonVariant decodeMethod(CoAPOptionDefinitions option, unsigned char * bytes);

public:

    static CoapOption encode(CoAPOptionDefinitions option, JsonVariant object);
    static JsonVariant decode(CoapOption option);

};

#endif // COAPOPTIONPARSER_H
