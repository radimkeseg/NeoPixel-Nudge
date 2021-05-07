#include "miniMP3.h"


void miniMP3::begin(){
    mySerial->begin(9600); 
    sendCommand(CMD_SEL_DEV, DEV_TF); //select the TF card 
}


void miniMP3::play(int8_t volume, int8_t song){
    if( volume>30 ) volume = 30;
    if(song>255) song=255;   
    sendCommand(CMD_PLAY_WITHVOLUME, ((int16_t)volume)*256 + song);
}


void miniMP3::sendCommand(int8_t command, int16_t dat){
   Send_buf[0] = 0x7e; //starting byte
   Send_buf[1] = 0xff; //version
   Send_buf[2] = 0x06; //the number of bytes of the command without starting byte and ending byte
   Send_buf[3] = command; //
   Send_buf[4] = 0x00;//0x00 = no feedback, 0x01 = feedback
   Send_buf[5] = (int8_t)(dat >> 8);//datah
   Send_buf[6] = (int8_t)(dat); //datal
   Send_buf[7] = 0xef; //ending byte
   for(uint8_t i=0; i<8; i++)//
   {
     mySerial->write(Send_buf[i]) ;//send bit to serial mp3
   }
}
