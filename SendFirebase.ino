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


void sendFirebaseDatabase() {
  String id = Firebase.pushInt("/ColetaSensor", 0);
  Firebase.setInt("/noSensor/" + id + "/batimento", noSensor.bpm);
  Firebase.setString("/noSensor/" + id + "/mensagem", noSensor.mensagem);
  Firebase.setBool("/noSensor/" + id + "/statusAlerta",  noSensor.statusAlerta);
  Firebase.setFloat("/noSensor/" + id + "/temperatuera", noSensor.temperatuera);
//  Firebase.setString("/noSensor/" + id + "/time", "");
////////////////Tratamento com time
  Firebase.setInt("/noSensor/" + id + "/time/date", 4);
  Firebase.setInt("/noSensor/" + id + "/time/day", 6);
  Firebase.setInt("/noSensor/" + id + "/time/hours", 22);
  Firebase.setInt("/noSensor/" + id + "/time/minutes", 16);
  Firebase.setInt("/noSensor/" + id + "/time/month", 4);
  Firebase.setInt("/noSensor/" + id + "/time/seconds",30 );
  Firebase.setFloat("/noSensor/" + id + "/time/time", 1488665789343);
  Firebase.setInt("/noSensor/" + id + "/time/timezoneOffset", 4);
  Firebase.setInt("/noSensor/" + id + "/time/year", 2017);
  
////////////////Fim Tratamento com time
  Firebase.setInt("/noSensor/" + id + "/tipoalerta", noSensor.tipoalerta);
  Firebase.setInt("/noSensor/" + id + "/umidadade",  noSensor.umidadade);
  Firebase.remove("/ColetaSensor");
}


