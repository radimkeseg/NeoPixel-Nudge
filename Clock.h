/**The MIT License (MIT)
Copyright (c) 2017 by Radim Keseg
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

#pragma once

#include "ITimer.h"
#include "TimeClient.h"



class Clock : virtual public ITimer
{
    private:
      uint32_t color_hand_hour = 0xff0000;
      uint32_t color_hand_mins = 0x00aa00; 
      uint32_t color_hand_secs = 0x110011;
      uint32_t color_segm_hour = 0x111100; //hour segment
      uint32_t color_dots_hour = 0x000011; //full hour dots
      uint32_t color_dots_qrtr = 0x001133; //quarter dots

      TimeClient timeClient;
  
      const long time_update_interval = 12*60*60*1000; //update every 12 hrs
      long last_time_update = time_update_interval;

      int pixel_offset = 0; //useful move the start point, in case the connectors are on bottom and number of pixels is 60 then the offest needs to be 30      

      void setPixel(int position, uint32_t color, boolean mix_color);
    
    public:
      Clock(Adafruit_NeoPixel *strip) : ITimer(strip){}
      Clock(Adafruit_NeoPixel *strip, int pixel_offset) : ITimer(strip){ this->pixel_offset = pixel_offset; }
    
      virtual void Show(boolean clear_background, boolean mix_colors);
      virtual void Show(){ Show(false, false); }
      
      virtual void Reset();
      virtual void Clear();

      virtual void SetUp(uint32_t color_hand_hour, uint32_t color_hand_mins, uint32_t color_hand_secs){ SetUp(color_hand_hour, color_hand_mins, color_hand_secs, 0, 0, 0); }        
      virtual void SetUp(uint32_t color_hand_hour, uint32_t color_hand_mins, uint32_t color_hand_secs, uint32_t color_segm_hour, uint32_t color_dots_hour, uint32_t color_dots_qrtr);        
      virtual void SetTimeOffset(int time_offset);

      int getHourInt(){ return timeClient.getHoursInt();}
      int getMinsInt(){ return timeClient.getMinutesInt(); }
      int getSecsInt(){ return timeClient.getSecondsInt(); }   

      String getFormattedTime(){ return timeClient.getFormattedTime(); }
};
