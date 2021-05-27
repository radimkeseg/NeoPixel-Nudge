#pragma once

#include <SoftwareSerial.h>

#define ARDUINO_RX 3//should connect to TX of the Serial MP3 Player module
#define ARDUINO_TX 1//connect to RX of the module

class IminiMP3
{
  protected:
    SoftwareSerial *mySerial; //mySerial(ARDUINO_RX, ARDUINO_TX);//init the serial protocol, tell to myserial wich pins are TX and RX    

  public:
    IminiMP3(int RX, int TX){
          mySerial = new SoftwareSerial(RX, TX);
    }
    IminiMP3(): IminiMP3(ARDUINO_RX, ARDUINO_TX){} 

    virtual ~IminiMP3(){
      delete mySerial;
    }

    virtual void begin() = 0;
    virtual void play(int8_t volume, int8_t song) = 0;
    virtual void play(int8_t song) = 0;
};
