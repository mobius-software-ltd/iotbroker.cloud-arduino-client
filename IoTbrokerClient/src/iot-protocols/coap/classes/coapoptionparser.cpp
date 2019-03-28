#include "coapoptionparser.h"

CoapOption CoapOptionParser::encode(CoAPOptionDefinitions option, JsonVariant object)
{
    unsigned char * value = CoapOptionParser::encodeMethod(option, object);
    return CoapOption(option, sizeof(value), value);
}

JsonVariant CoapOptionParser::decode(CoapOption option)
{
    return CoapOptionParser::decodeMethod((CoAPOptionDefinitions)option.getNumber(), option.getValue());
}

unsigned char * CoapOptionParser::encodeMethod(CoAPOptionDefinitions option, JsonVariant object)
{
    switch (option) {
    case COAP_URI_PORT_OPTION:
    case COAP_CONTENT_FORMAT_OPTION:
    case COAP_ACCEPT_OPTION: {
        int value = std::get<int>(object);
        unsigned char * array = new unsigned char[2];
        array[0] = (unsigned char) 0x00;
        array[1] = (unsigned char) value;
        return array;
    } break;
    case COAP_MAX_AGE_OPTION:
    case COAP_SIZE1_OPTION:
    case COAP_OBSERVE_OPTION: {
        int value = std::get<int>(object);
        return (unsigned char)value;
    } break;
    case COAP_NODE_ID_OPTION:
    case COAP_IF_MATCH_OPTION:
    case COAP_URI_HOST_OPTION:
    case COAP_ETAG_OPTION:
    case COAP_URI_PATH_OPTION:
    case COAP_LOCATION_PATH_OPTION:
    case COAP_URI_QUERY_OPTION:
    case COAP_LOCATION_QUERY_OPTION:
    case COAP_PROXY_SCHEME_OPTION:
    case COAP_PROXY_URI_OPTION: {
        String value = std::get<String>(object);
        return value;
    } break;
    default:
        break;
    }
    return NULL;
}

JsonVariant CoapOptionParser::decodeMethod(CoAPOptionDefinitions option, unsigned char * bytes)
{
    JsonVariant value;
    switch (option) {
    case COAP_URI_PORT_OPTION:
    case COAP_CONTENT_FORMAT_OPTION:
    case COAP_ACCEPT_OPTION: {
        if (sizeof(bytes) >= 2) {
            value.set(get_short(buffer, 0));
        }
    } break;
    case COAP_MAX_AGE_OPTION:
    case COAP_SIZE1_OPTION:
    case COAP_OBSERVE_OPTION: {
        if (sizeof(bytes) >= 4) {
            value.set(get_int(buffer, 0));
        }
    } break;
    case COAP_NODE_ID_OPTION:
    case COAP_IF_MATCH_OPTION:
    case COAP_URI_HOST_OPTION:
    case COAP_ETAG_OPTION:
    case COAP_URI_PATH_OPTION:
    case COAP_LOCATION_PATH_OPTION:
    case COAP_URI_QUERY_OPTION:
    case COAP_LOCATION_QUERY_OPTION:
    case COAP_PROXY_SCHEME_OPTION:
    case COAP_PROXY_URI_OPTION: {
        value.set(bytes);
    } break;
    default:
        break;
    }
    return value;
}
