#include <SD.h>
#include <SPI.h>
#include "account.h"

#define DELIM ":"
#define COMMENT '#'
#define FILENAME "./conf.txt"

String topic_name;
int message_qos = 0;
int message_retain = 0;
int message_dup = 0;

int period_message_resend = 60;

class Rectangle {
    int width, height;
  public:
    void set_values (int,int);
    int area () {return width*height;}
};

class ConfigReader {
  public:
    Account read_config();
  };
