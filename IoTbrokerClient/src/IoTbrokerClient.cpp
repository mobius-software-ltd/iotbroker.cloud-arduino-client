#include "IoTbrokerClient.h"

File printFile;
String buffer;
boolean SDfound;
//CS pin on Ethernet Shield
const int cs = 4;

void Rectangle::set_values (int x, int y) {
  width = x;
  height = y;
}

Account ConfigReader::read_config() {
  String line;
  Account account;
  if(SD.begin(cs)){
    printFile = SD.open(FILENAME, FILE_READ);
    if(printFile) {
      while(printFile.available()) {
          line = printFile.readStringUntil('\n');
          if(line[0] != COMMENT){
            int pos = line.indexOf(DELIM);
            String keyStr = line.substring(0, pos);
            String value = line.substring(pos, line.length());

            if(keyStr.compareTo("protocol") == 0){
              account.protocol = Protocol(value.toInt());
            } else if(keyStr.compareTo("username") == 0){
              account.username = value;
            } else if(keyStr.compareTo("password") == 0){
              account.password = value;
            } else if(keyStr.compareTo("clientId") == 0){
              account.client_id = value;
            } else if(keyStr.compareTo("host") == 0){
              account.server_host = value;
            } else if(keyStr.compareTo("port") == 0){
              account.server_port = value.toInt();
            } else if(keyStr.compareTo("cleanSession") == 0){
                if(value.compareTo("True") == 0)
                  account.clean_session = 1;
                else
                  account.clean_session = 0;
            } else if(keyStr.compareTo("keepAlive") == 0){
              account.keep_alive = value.toInt();
            } else if(keyStr.compareTo("will") == 0){
              account.will = value;
            } else if(keyStr.compareTo("willTopic") == 0){
              account.will_topic = value;
            } else if(keyStr.compareTo("retain") == 0){
                if(value.compareTo("True") == 0)
                  account.is_retain = 1;
                else
                  account.is_retain = 0;
            } else if(keyStr.compareTo("qos") == 0){
              account.qos = value.toInt();
            } else if(keyStr.compareTo("isSecure") == 0){
                if(value.compareTo("True") == 0)
                  account.is_secure = 1;
                else
                  account.is_secure = 0;
            } else if(keyStr.compareTo("certKeyPath") == 0){
              account.certificate = value;
            } else if(keyStr.compareTo("certPassword") == 0){
              account.certificate_password = value;
            } else if(keyStr.compareTo("topicName") == 0){
              topic_name = value;
            } else if(keyStr.compareTo("messageQos") == 0){
              message_qos = value.toInt();
            } else if(keyStr.compareTo("messageRetain") == 0){
                if(value.compareTo("True") == 0)
                  message_retain = 1;
                else
                  message_retain = 0;
            } else if(keyStr.compareTo("messageDup") == 0){
                if(value.compareTo("True") == 0)
                  message_dup = 1;
                else
                  message_dup = 0;
            } else if(keyStr.compareTo("period") == 0){
              period_message_resend = value.toInt();
            }
          }
      }
      printFile.close();
    } else {
      Serial.println("The text file cannot be opened");
    }
  } else {
    Serial.println("The SD card cannot be found");
  }
  return account;
}
