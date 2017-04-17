//  __  __   __      _       _             _                                        _                /\/|       
// |  \/  | /_/     | |     | |           | |                                      (_)              |/\/        
// | \  / | ___   __| |_   _| | ___     __| | ___    ___ ___  _ __ ___  _   _ _ __  _  ___ __ _  ___ __ _  ___  
// | |\/| |/ _ \ / _` | | | | |/ _ \   / _` |/ _ \  / __/ _ \| '_ ` _ \| | | | '_ \| |/ __/ _` |/ __/ _` |/ _ \ 
// | |  | | (_) | (_| | |_| | | (_) | | (_| |  __/ | (_| (_) | | | | | | |_| | | | | | (_| (_| | (_| (_| | (_) |
// |_|  |_|\___/ \__,_|\__,_|_|\___/   \__,_|\___|  \___\___/|_| |_| |_|\__,_|_| |_|_|\___\__,_|\___\__,_|\___/ 
//                                                                                               )_)            
//                                                                                                              

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>


#define FIREBASE_HOST F("checkbaby-338a9.firebaseio.com")
#define FIREBASE_AUTH "nqB1HAmkwZ6nvMKUMmxpYXFtILcPSrKGyvp3ePH8"

const char* ssid = "NET_2G7A5441";
const char* password = "B37A5441";
//const char* ssid = "ICOMP_1A";
//const char* password = "1comp@14#";


WiFiServer server(80);
WiFiClient client;


 String dateTime;

// Cria a intancia do sevidor 
// especifica a porta para ouvir requisição 

int boundRate= 115200; //Frequencia de 

void setup() {
  Serial.begin(boundRate);
  delay(10);
  setupFirebase();
  // prepare GPIO2
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  
  conectWifi();
  
}

void loop() {
  wifiClientSockets();
}

