#include "miniMP3a.h"


void miniMP3a::begin(){
    mySerial->begin(9600); 
    sendCommand(select_SD_card, 5); //select the TF card 
}


void miniMP3a::play(int8_t volume, int8_t song){
  play(song); //ignore volume
}

void miniMP3a::play(int8_t song){
  if(song>255) song=255;   
  play_song[4] = song;
  sendCommand(play_song, 6);
}


void miniMP3a::sendCommand(int8_t command[], int len){
  for(int i=0;i<len;i++){ mySerial->write(command[i]); }
}
