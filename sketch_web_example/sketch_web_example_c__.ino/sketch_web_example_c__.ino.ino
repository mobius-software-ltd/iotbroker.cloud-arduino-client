#include <Ethernet.h>
#include <EthernetUdp.h>

int main(void)
{
  // Enter a MAC address and IP address for your controller below.
  // The IP address will be dependent on your local network:
  byte mac[] = {
    0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
  };
  IPAddress ip(172, 21, 0, 177);
  
  unsigned int localPort = 8888;      // local port to listen on
  
  // buffers for receiving and sending data
  char packetBuffer[UDP_TX_PACKET_MAX_SIZE];  // buffer to hold incoming packet,
  
  // An EthernetUDP instance to let us send and receive packets over UDP
  EthernetUDP Udp;
  
  int count = 1;

  //SETUP
  // You can use Ethernet.init(pin) to configure the CS pin
  //Ethernet.init(10);  // Most Arduino shields
  //Ethernet.init(5);   // MKR ETH shield
  //Ethernet.init(0);   // Teensy 2.0
  //Ethernet.init(20);  // Teensy++ 2.0
  //Ethernet.init(15);  // ESP8266 with Adafruit Featherwing Ethernet
  //Ethernet.init(33);  // ESP32 with Adafruit Featherwing Ethernet

  // start the Ethernet
  Ethernet.begin(mac, ip);

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("HERE");
  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }

  // start UDP
  Udp.begin(localPort);
  
  // Arduino "Loop"
  while (1)
  {
      // if there's data available, read a packet
      int packetSize = Udp.parsePacket();
      char ReplyBuffer[] = "Packet from DUE received ";        // a string to send back
      if (packetSize) {
        Serial.print("Received packet of size ");
        Serial.println(packetSize);
        Serial.print("From ");
        IPAddress remote = Udp.remoteIP();
        for (int i=0; i < 4; i++) {
          Serial.print(remote[i], DEC);
          if (i < 3) {
            Serial.print(".");
          }
        }
        Serial.print(", port ");
        Serial.println(Udp.remotePort());
    
        // read the packet into packetBufffer
        Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
        Serial.println("Contents:");
        Serial.println(packetBuffer);
    
        // send a reply to the IP address and port that sent us the packet we received
        Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
        char count_string[32];
        sprintf(count_string, "%d", count++);
        strcat(ReplyBuffer, count_string);
        Udp.write(ReplyBuffer);
        Udp.endPacket();
      }
      delay(10);
      }
}
