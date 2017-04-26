

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
  
  StaticJsonBuffer<300> jsonBufferNoSensor;
  JsonObject& noSensor = jsonBufferNoSensor.createObject();
  
  
  int resp= treatmentRequest(noSensor);
    if(resp ==-1){return;} //Tratamento de request invalida

  // Set GPIO2 according to the request
  digitalWrite(LED_BUILTIN, resp);
  
  client.flush();

  treatmentResponse(resp,noSensor); //Trata a reposta
}
 
int treatmentRequest(JsonObject& noSensor){

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

    noSensor["batimento"]= getValue().toInt();
    noSensor["tipoAlerta1"]= getValue().toInt();
    noSensor["mensagem1"]= getValue();

 
    noSensor["temperatura"] = getValue().toFloat(); //Float
    noSensor["tipoAlerta2"]= getValue().toInt();
    noSensor["mensagem2"]= getValue();

    dateTime=getValue();
    
    Serial.println("Begin to format");
    Serial.println(dateTime);
   
    noSensor["ano"]= getDate('-').toInt();
    noSensor["mes"]= getDate('-');
    noSensor["dia"]= getDate('-');
    noSensor["hora"]= getDate(':').toInt();
    noSensor["minuto"]= getDate(':').toInt();
    noSensor["segundo"]= getDate(':').toInt();;    

    Serial.println("End to format");
    
    
 
 
    noSensor["umidade"]= getValue().toInt();
    noSensor["tipoAlerta3"]= getValue().toInt();
    noSensor["mensagem3"]= getValue();
   
   // Check erro na request
   int bpm = noSensor["batimento"];
   int temp =noSensor["temperatura"];
   int umi =noSensor["umidade"];
   
 if(bpm==0 & temp==0 & umi==0){
     Serial.println(F("Batimento"));
     Serial.println(bpm);
     Serial.println(F("Temperatura"));
     Serial.println(temp);
     Serial.println(F("Umidade"));
     Serial.println(umi);
     
     Serial.println(F("invalid request"));
       client.stop();
       resp=-1;
    }
     return resp;
}


  String getDate(char separador)
{
  int indexdate = dateTime.indexOf(separador);
  String date = dateTime.substring(0, indexdate);
   
  if (dateTime.startsWith(date + separador)) { //Verifica se estar no fim
    dateTime.replace(date + separador, "");
  } else {
    dateTime.replace(date + separador  + "/", "");
 
    }

  Serial.println("getDate>> ");
  Serial.println(date ); //Mostra date e valor
  Serial.println("dateTime: " + dateTime);
  Serial.println("getDate<<\n\n");

  return date;
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

void treatmentResponse(int resp, JsonObject& noSensor){
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

  sendFirebaseDatabase(noSensor);
}
  
