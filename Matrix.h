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

#pragma once

#include "ITimer.h"
#include "TimeClient.h"



class Matrix : virtual public ITimer
{
    private:
      TimeClient timeClient;
  
      const long time_update_interval = 12*60*60*1000; //update every 12 hrs
      long last_time_update = time_update_interval;

      int pixels_in_row = 0; //due to the matrix display there is need to know how many pixels exist in a row      
    
    public:
      Matrix(Adafruit_NeoPixel *strip) : ITimer(strip){}
      Matrix(Adafruit_NeoPixel *strip, int pixels_in_row) : ITimer(strip){ this->pixels_in_row = pixels_in_row; }
    
      virtual void Show(boolean clear_background, boolean mix_colors);
      virtual void Show(){ Show(false, false); }

      virtual void SetTimeOffset(int time_offset);

      int getHourInt(){ return timeClient.getHoursInt();}
      int getMinsInt(){ return timeClient.getMinutesInt(); }
      int getSecsInt(){ return timeClient.getSecondsInt(); }      

    public:  
      void setPixel(int position, uint32_t color, boolean mix_color);
      void setPixel(int position, uint32_t color){ setPixel(position, color, false);}
      void setPixel(int x, int y, uint32_t color, boolean mix_color);
      void setPixel(int x, int y, uint32_t color){ setPixel(x, y, color, false);}

      uint16_t numPixels(void) const {if(strip==NULL) return 0; return strip->numPixels(); }
      uint16_t numPixelsInRow(void) const {return pixels_in_row; }
      uint16_t numRows(void) const {return numPixels() / numPixelsInRow(); }
      

};
