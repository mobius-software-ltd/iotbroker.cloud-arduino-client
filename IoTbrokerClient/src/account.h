#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include "iot-protocols/classes/topic.h"
#include <WString.h>

enum Protocol {
	MQTT = 0,
	MQTT_SN = 1,
	COAP = 2,
	AMQP = 3,
	WEBSOCKETS = 4
};

class Account {
public:
      int id;
      Protocol protocol;
      String username;
      String password;
      String client_id;
      String server_host;
      int server_port;
      int clean_session;
      int keep_alive;
      String will;
      String will_topic;
      int is_retain;
      QoS qos;
      int is_default;

    	int is_secure;
    	String certificate;
    	String certificate_password;
};

#endif /* ACCOUNT_H_ */
