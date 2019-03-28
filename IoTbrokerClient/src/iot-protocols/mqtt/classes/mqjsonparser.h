#ifndef MQJSONPARSER_H
#define MQJSONPARSER_H

#include "iot-protocols/classes/message.h"
#include <iterator>

class MQJsonParser
{

public:

    static unsigned char[] json(Message *message);
    static Message *message(unsigned char *json[]);

};

#endif // MQJSONPARSER_H
