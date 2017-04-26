//
// Copyright 2015 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// FirebaseRoom_ESP8266 is a sample that demo using multiple sensors
// and actuactor with the FirebaseArduino library.

void setupFirebase(){
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); //Instanciar só uma vez
}
  
void sendFirebaseDatabase(JsonObject& noSensor) {
    String data="";
    data.concat("/noSensor/Data");
    String ano = noSensor["ano"];
    data.concat(ano);data.concat("-");
    String mes = noSensor["mes"]; 
    data.concat(mes);data.concat("-");
    String dia= noSensor["dia"];
    data.concat(dia);
    
  String path = Firebase.push(data, noSensor);
  bool isFailed = Firebase.failed();
  if(isFailed) {
    Serial.println(F("Erro ao adicionar no Sensor"));
    Serial.println(Firebase.error());
   }
  
}

