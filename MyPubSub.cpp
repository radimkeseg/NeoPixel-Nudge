/**The MIT License (MIT)

Copyright (c) 2021 by Radim Keseg

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "MyPubSub.h"

#define ESP01_BUILTINLED  1

void MyPubSub::callback(char* topic, byte* payload, unsigned int length) {
  if(fHandleSubCallback!=NULL){
    fHandleSubCallback(topic, payload, length);
  }else{  
    //if message recieved just blink - hardcoded for ESP01
    bool blink = digitalRead(ESP01_BUILTINLED);
    for(int i=0; i<4; i++){
      digitalWrite(ESP01_BUILTINLED, blink=!blink);
      delay(200);
    }
  }
}

void MyPubSub::setCredentials(const char* clientID, const char* user, const char* password){
  this->clientID = clientID;
  this->user = user;
  this->password = password;
}


void MyPubSub::reconnect(){
  // Loop until we're reconnected
  int attempt = 1;
  bool reconnected = false;
  
  if (!psclient->connected()) {
    // Attempt to connect
    while(attempt<=3 && !reconnected){
      if (psclient->connect(clientID, user, password)) { //hardcoded needs to be fixed
        reconnected = true;
        subscribe();
      }
      attempt++;
    }
  }
  psclient->loop();
}

bool MyPubSub::setup(){
  if(mqtt_server != NULL ){
    psclient->setServer(mqtt_server, 1883);
    psclient->setCallback( [this](char* topic, byte* payload, unsigned int length) { callback(topic, payload, length); } );
    
    //connect to server and subscribe
    reconnect();
    return true;
  }
   
  return false;
}

bool MyPubSub::isConnected(){
  return psclient->connected();
} 

bool MyPubSub::subscribe(){
  return psclient->subscribe(inTopic);
}

void MyPubSub::handleClient(){
  psclient->loop();  
}

bool MyPubSub::publish(const char* payload, boolean retained) {
    return psclient->publish(outTopic, (const uint8_t*) payload, strlen(payload), retained);
}

void MyPubSub::setHandleSubCallback(fncHandleSubCallback fHandleSubCallback){
  this->fHandleSubCallback = fHandleSubCallback;
}
