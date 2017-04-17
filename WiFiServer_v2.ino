/*
 *  This sketch demonstrates how to set up a simple HTTP-like server.
 *  The server will set a GPIO pin depending on the request
 *    http://server_ip/gpio/0 will set the GPIO2 low,
 *    http://server_ip/gpio/1 will set the GPIO2 high
 *  server_ip is the IP address of the ESP8266 module, will be 
 *  printed to Serial when the module is connected.
 */

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "checkbaby-338a9.firebaseio.com"
#define FIREBASE_AUTH "nqB1HAmkwZ6nvMKUMmxpYXFtILcPSrKGyvp3ePH8"

const char* ssid = "netvirtua87";
const char* password = "2097527020";
WiFiServer server(80);
WiFiClient client;


struct no
{
   int bpm;
   String mensagem;
   bool statusAlerta;
   float temperatuera;
   int tipoalerta;
   int umidadade;
};

typedef struct no Record;
Record noSensor;

// Cria a intancia do sevidor 
// especifica a porta para ouvir requisição 

int boundRate= 115200; //Frequencia de 

void setup() {
  Serial.begin(boundRate);
  delay(10);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); //Instanciar só uma vez
  // prepare GPIO2
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  
  conectWifi();
  
}

void loop() {
  wifiClientSockets();
}

