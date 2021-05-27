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

//for now works well in case of 60 pixel strip only
//in other cases comment the line below
//#define SHOWCLOCK
#define PLAYSONG

#include "MyWifi.h"
MyWifi myWifi; 

#include "MyPubSub.h"
MyPubSub *myPubSub;

#include "ITimer.h"
#include "Interval.h"
#include "Clock.h"

#include "EfXRainbow.h"
#include "EfXHour.h"
#include "EfXQuarter.h"
#include "EfXAlarm.h"
#include "EfXAction.h"

#ifdef PLAYSONG
//#include "miniMP3.h"
#include "miniMP3a.h"
//miniMP3 mp3; //blue miniMP3player1.0
miniMP3a mp3; //red miniMP3playerA 
#endif

#include "Pubee.h"
Pubee pubee;

bool isInSetupMode = false;

//esp01 -> generic8266 flash:1M+128k SPIFF
#define SETUP_PIN 0      //GPIO0
#define TX 1             //LED_BUILTIN
#define RX 3
#define LED_STRIP 2
/*//node mcu test and debug
#define SETUP_PIN D7      //GPIO0
#define TX LED_BUILTIN
#define RX D7
*/
#define AP_NAME "NeoPixel-Bell-Nudger"

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, LED_STRIP, NEO_GRB + NEO_KHZ800);

#ifdef SHOWCLOCK
Clock clock(&strip, 30);
#else
Clock clock(&strip, 0);
#endif

EfxRainbow efx_rainbow(&strip);
EfxHour efx_hour(&strip);
EfxQuarter efx_quarter(&strip);
EfxAlarm efx_alarm(&strip);
EfxAction efx_action(&strip);

static void publish(pubeeStates status){
  if(myWifi.getCustomSettings().settings.MQTT){
    if(pubee.setStatus(status)){
       myPubSub->reconnect();
       myPubSub->publish(("{ \"state\":\""+pubee.getStatus()+"\" }").c_str()); 
    }
  }
}

/* webserver handlers */
bool action = false;
Interval ActionInterval;

static bool forceUpdateData = false;

static String stFncHandleAction(){ 
  char color[8];
  int sec = 0;
  
  if(myWifi.getServer().arg("color")!=NULL){
    strncpy(color, myWifi.getServer().arg("color").c_str(), 8);
    efx_action.SetUp( ITimer::hex2rgb( color ) );
  }
  
  if(myWifi.getServer().arg("sec")==NULL ){
    action = false;
    ActionInterval.set(sec=0);
  }else{
    action = true;
    sec = atoi(myWifi.getServer().arg("sec").c_str());
    ActionInterval.set( sec * 1000 );
  }
  
  return "OK";
}

#include <ArduinoJson.h>
static String stHandleSubCallback(char* topic, byte* payload, unsigned int length){
  StaticJsonDocument<1024> doc;  //should be set dynamic, maybe later 255 should be enough
  DeserializationError error = deserializeJson(doc, (char*)payload);

  if (error) {
    return "JSON ERROR";
  }

  const char* color = doc["color"];
  efx_action.SetUp( ITimer::hex2rgb((char*)color) );


#ifdef PLAYSONG
  int song = doc["song"];
  int volume = doc["volume"];
  if(song>0){
    digitalWrite(SETUP_PIN, HIGH); 
    delay(20);
    mp3.play(volume, song);
  }
#endif

  
  action = true;
  int sec = doc["sec"];
  ActionInterval.set( sec * 1000 );

  return "OK";
}

/**/

void setup() {
  //Serial.begin(115200);

  strip.begin();
  strip.clear();
  strip.show();

  myWifi.setup(AP_NAME,60); //1 min to configure the WIFI 
  myWifi.setActionHandler( stFncHandleAction );
  myWifi.getCustomSettings().print();

  if(myWifi.getCustomSettings().settings.MQTT){
    myPubSub = new MyPubSub(myWifi.getWifiClient(), myWifi.getCustomSettings().settings.MQTT_BROKER, myWifi.getCustomSettings().settings.MQTT_IN_TOPIC, myWifi.getCustomSettings().settings.MQTT_OUT_TOPIC );
    myPubSub->setCredentials(myWifi.getCustomSettings().settings.MQTT_DEVICE_ID, myWifi.getCustomSettings().settings.MQTT_USER, myWifi.getCustomSettings().settings.MQTT_PASSWORD);
    myPubSub->setHandleSubCallback( stHandleSubCallback );
    myPubSub->setup();
  }

  updateData();

#ifdef PLAYSONG
  mp3.begin();
  pinMode(SETUP_PIN, OUTPUT);
  digitalWrite(SETUP_PIN, LOW); 
#endif  

  delay(100);  
}

long lastDrew = 0;
long lastUpdate = 0;

long stamp = 0;

void loop() {
  pubeeStates ps = IDLE;
  bool fast=false;  
  
  // Handle web server
  myWifi.handleClient();
  if(myWifi.getCustomSettings().settings.MQTT) myPubSub->handleClient();

  clock.Clear(); 
  
  if(clock.getHourInt()>=22 || clock.getHourInt()<6) strip.setBrightness(myWifi.getCustomSettings().settings.brightness_night);
  else strip.setBrightness(myWifi.getCustomSettings().settings.brightness);

  //animate
  if( myWifi.getCustomSettings().settings.animate ) { 
    efx_rainbow.Show(); 
    delay(10); 
    fast=true; 
    ps=ANIMATION;
  } 
  yield();

  
  // effect by the full hour
  if( clock.getMinsInt() == 0 && clock.getSecsInt()<20){
    if(myWifi.getCustomSettings().settings.animate)
      efx_hour.Show(); 
    else
      efx_rainbow.Show();    
    delay(10); 
    fast=true;
    ps = FULLHOUR;
  // effect by the guarters
  }else{
    efx_hour.Reset();
    if( clock.getMinsInt() == 15 && clock.getSecsInt()<3 || clock.getMinsInt() == 30 && clock.getSecsInt()<6 || clock.getMinsInt() == 45 && clock.getSecsInt()<9){
      efx_quarter.Show();
      delay(10); 
      fast=true;
      ps = QUARTER;
    }else{
      efx_quarter.Reset();
    }
  }  
  yield();

  //effect by alarm
  if(myWifi.getCustomSettings().settings.ALARM_SWITCH)
  if(clock.getHourInt() == myWifi.getCustomSettings().settings.alarmHour && clock.getMinsInt() == myWifi.getCustomSettings().settings.alarmMins){
    efx_alarm.Show(); 
    delay(50); 
    fast=true;
    ps = ALARM;
  }else{
    efx_alarm.Reset();
  }
  yield();


  if(action){
    if(ActionInterval.expired()){
#ifdef PLAYSONG    
      digitalWrite(SETUP_PIN, LOW);         
#endif
      action = false;
    }else{
      efx_action.Show(); 
      delay(50); 
      fast=true;
      ps = ACTION;
    }
  }else{
    efx_action.Reset();
  }
  yield();

#ifdef SHOWCLOCK
  // show clock
  clock.Show(false, true); 
#endif
    
  strip.show(); //render all

  if(stamp - lastUpdate > UPDATE_INTERVAL_SECS * 1000 || stamp < lastUpdate || forceUpdateData){
    updateData();
    lastUpdate = stamp;  
  }

  if(fast)
    publish(ps);
  else
   publish(IDLE);
  delay(fast?50:500);
}

void updateData(){
  efx_hour.SetUp(ITimer::hex2rgb( myWifi.getCustomSettings().settings.color_hours) );
  efx_quarter.SetUp(ITimer::hex2rgb( myWifi.getCustomSettings().settings.color_quarters) );
  efx_alarm.SetUp(ITimer::hex2rgb( myWifi.getCustomSettings().settings.color_alarm) );
  
  clock.SetTimeOffset(myWifi.getCustomSettings().settings.UTC_OFFSET+myWifi.getCustomSettings().settings.DST);  
  if(forceUpdateData) forceUpdateData=false;
}
