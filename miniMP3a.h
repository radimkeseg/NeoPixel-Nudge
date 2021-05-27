#pragma once

#include "IminiMP3.h"

//https://www.theamplituhedron.com/articles/How-to-use-the-Serial-MP3-Player-UART-with-Speaker-by-OPEN-SMART-with-Arduino/

// Select storage device to TF card
static int8_t select_SD_card[] = {0x7e, 0x03, 0X35, 0x01, 0xef}; // 7E 03 35 01 EF
// Play with index: /01/001xxx.mp3
static int8_t play_song[] = {0x7e, 0x04, 0x31, 0x1E, 0x01, 0xef}; // 7E 04 31 1E 01 EF
// Play the song.
static int8_t play[] = {0x7e, 0x02, 0x01, 0xef}; // 7E 02 01 EF
// Pause the song.
static int8_t pause[] = {0x7e, 0x02, 0x02, 0xef}; // 7E 02 02 EF

class miniMP3a: public IminiMP3
{
  protected:
    void sendCommand(int8_t command[], int len);

  public:
    miniMP3a(int RX, int TX): IminiMP3(RX,TX){}
    miniMP3a(): miniMP3a(ARDUINO_RX, ARDUINO_TX){} 

    void begin();
    void play(int8_t volume, int8_t song); 
    void play(int8_t song);  
};
