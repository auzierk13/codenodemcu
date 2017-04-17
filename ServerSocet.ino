/*
 *  This sketch demonstrates how to set up a simple HTTP-like server.
 *  The server will set a GPIO pin depending on the request
 *    http://server_ip/gpio/0 will set the GPIO2 low,
 *    http://server_ip/gpio/1 will set the GPIO2 high
 *  server_ip is the IP address of the ESP8266 module, will be 
 *  printed to Serial when the module is connected.
 */


String req; //Request http

 
void conectWifi(){

// Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password); // Conecta na rede WiFi 
  
  while (WiFi.status() != WL_CONNECTED) {//Verifica conexão
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Inicia o servidor 
  server.begin();
  Serial.println("Server started");

  // Mostra o endereço IP 
  Serial.println(WiFi.localIP());	
}


void wifiClientSockets(){
// Check if a client has connected
  client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("New client");
  while(!client.available()){
    delay(1);
  }
    
  int resp= treatmentRequest();
    if(resp ==-1){return;} //Tratamento de request invalida

  // Set GPIO2 according to the request
  digitalWrite(LED_BUILTIN, resp);
  
  client.flush();

  treatmentResponse(resp); //Trata a reposta
}
 
int treatmentRequest(){

   // Read the first line of the request
    req = client.readStringUntil('\r');
    Serial.println(req);
    client.flush();
    
    // Match the request
    int resp=0;
//    if (req.indexOf("/gpio/0") != -1)
//      resp = 0;
//    else if (req.indexOf("/gpio/1") != -1)
//      resp = 1;
//    else {
//      Serial.println("invalid request");
//       client.stop();
//       resp=-1;
//    }

    Serial.println("Inicio do Tratamento "+ req); //imprimindo a string1

  ////////Removendo cabeçario da requisição
   if(!req.startsWith("GET /")){
    Serial.println("A req  nao inicia com  \"GET \"\n");
     Serial.println("invalid request");
       client.stop();
       resp=-1;
  }else{
    req.replace("GET /", "");
    Serial.println("Req sem Heard: "+ req); //imprimindo a string1
  }
  ////////Removendo Final da requisição
  if(!req.endsWith(" HTTP/1.1")){
    Serial.println("A req  nao termina com \" HTTP/1.1\"\n");
     Serial.println("invalid request");
       client.stop();
       resp=-1;
  }else{
    req.replace(" HTTP/1.1", "");
    Serial.println("Req sem Http1.1: "+ req); //imprimindo a string1
  }
  //////////////////////////////////////

  /////Captura de variaveis
  Serial.println("\n\n"); 
  Serial.println("Captacao de variavel "+ req); //imprimindo a string1   

    noSensor.bpm= getValue().toInt();
    noSensor.mensagem= getValue();
    noSensor.statusAlerta= getValue();
    noSensor.temperatuera = getValue().toFloat(); //Float
    Serial.print("temperatuera "); //Mostra chave e valor
    Serial.println(noSensor.temperatuera); //Mostra chave e valor
    noSensor.tipoalerta= getValue().toInt();
    noSensor.umidadade= getValue().toInt();

   
     return resp;
}
String getValue()
{
  int indexchave= req.indexOf('&');
  String chave = req.substring(0,indexchave); 
  String valor = req.substring(indexchave+1,req.indexOf('/')); 
  if(!req.endsWith(chave+"&"+valor)){//Verifica se estar no fim
   req.replace(chave+"&"+valor+"/",""); //Remove dados para economizar clocks
   }else{
    req.replace(chave+"&"+valor,""); 
    }
   
   Serial.println("GetValue>> ");
   Serial.println(chave+": "+ valor);
   Serial.println("Req: "+ req);
   Serial.println("GetValue<<\n\n");
   
  return valor;
}

void treatmentResponse(int resp){
  // Prepare the response
  String httpRes = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO is now ";
  httpRes += (resp)?"high":"low";
  httpRes += "</html>\n";

  // Send the response to the client
  client.print(httpRes);
  delay(1);
  Serial.println("Client disonnected");
  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed  

  sendFirebaseDatabase();
}
  
