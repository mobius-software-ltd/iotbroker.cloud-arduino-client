#include <Ethernet.h>
#include <EthernetUdp.h>

#include <StandardCplusplus.h>
#include <map>
#include <vector>
#include <WString.h>

#include <ArduinoJson.h>
#include <IoTbrokerClient.h>
/*
#include <SD.h>
#include <SPI.h>

File printFile;
//String buffer;
boolean SDfound;
//CS pin on Ethernet Shield
const int cs = 4;
*/
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

ConfigReader configReader;
Account account;

void setup() {
  
  // start the Ethernet
  Ethernet.begin(mac, ip);

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

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
  Serial.println("Udp.begin OK");
  
  /*
  // Reading file from SD card
  if (!SD.begin(cs)) {
    Serial.print("The SD card cannot be found");
    while(1);
  }
  Serial.println("SD card finding OK");
 
  printFile = SD.open("/conf.txt", FILE_READ);
  if (!printFile) {
    Serial.print("The text file cannot be opened conf.txt");
    while(1);
  }
  Serial.println("File open OK");
  
  while (printFile.available()) {
    String buffer;
    buffer = printFile.readStringUntil('\n');
    Serial.println(buffer); //Printing for debugging purpose         
    //do some action here
  }
  Serial.println("File reading OK");
  printFile.close();
  */
  account = configReader.read_config();
  Serial.println("read_config() OK ");
}

//Rectangle rect;

void loop() {}

/*
void loop() {
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
    //rect.set_values(count, count+1);
    
    count++;
    char count_string[32];
    //sprintf(count_string, "%d", rect.area());
    sprintf(count_string, "%d", 10);
    strcat(ReplyBuffer, count_string);
    Udp.write(ReplyBuffer);
    Udp.endPacket();
  }
  delay(10);
}*/
