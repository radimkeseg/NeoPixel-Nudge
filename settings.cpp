/**The MIT License (MIT)

Copyright (c) 2021 Radim Keseg

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

#include "settings.h"

extern settings_t settins;

void CustomSettings::init() {
  //http://esp8266.github.io/Arduino/versions/2.0.0/doc/filesystem.html
  if(SPIFFS.begin()){
    //SPIFFS.format(); //uncomment if formating needed
    delay(100);
  }
}

void CustomSettings::write(){
    //write location to SPIFF
    File f = SPIFFS.open(CUSTOM_SETTINGS, "w");
    if (f){
      f.write((uint8_t*) &settings, sizeof(settings_t));
    }
    f.flush();
    f.close();
}

void CustomSettings::read(){
    //read setting from SPIFF
    File f = SPIFFS.open(CUSTOM_SETTINGS, "r");
    if(f){
       f.read((uint8_t*) &settings, sizeof(settings_t));
    }
    f.close();
}

void CustomSettings::print(){    
/*
    Serial.print("UTC TimeOffset: "); Serial.println(settings.UTC_OFFSET);
    Serial.print("DST: "); Serial.println(settings.DST);
    Serial.print("brightness: "); Serial.println(settings.brightness);
    Serial.print("brightness night: "); Serial.println(settings.brightness_night);
    Serial.print("color hours: "); Serial.println(settings.color_hours);
    Serial.print("color quarters: "); Serial.println(settings.color_quarters);
    Serial.print("animate: "); Serial.println(settings.animate);
    Serial.print("alarm: "); Serial.println(settings.ALARM_SWITCH);
    Serial.print("color alarm: "); Serial.println(settings.color_alarm);
    Serial.print("@ "); Serial.print(settings.alarmHour); Serial.print(":"); Serial.println(settings.alarmMins);

    Serial.println("MQTT");
    Serial.print(" broker: "); Serial.println(settings.MQTT_BROKER);
    Serial.print(" user: "); Serial.println(settings.MQTT_USER);
    Serial.print(" password: "); Serial.println("***********");
    Serial.print(" device ID: "); Serial.println(settings.MQTT_DEVICE_ID);
    Serial.print(" out topic: "); Serial.println(settings.MQTT_OUT_TOPIC);
    Serial.print(" in topic: "); Serial.println(settings.MQTT_IN_TOPIC);    
*/	
}
