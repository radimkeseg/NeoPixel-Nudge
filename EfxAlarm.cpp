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

#include "EfxAlarm.h"

//public 
void EfxAlarm::Show(boolean clear_background, boolean mix_colors){
  if(strip==NULL) return;
  int ln = strip->numPixels();
    
  if(j>=3) j=0;  
  
  for (uint16_t i=0; i < ln; i+=3) {
    strip->setPixelColor(i+j, color);    //turn every third pixel on
    strip->setPixelColor((i+j+1)%ln, 0);        //turn other pixel off
    strip->setPixelColor((i+j+2)%ln, 0);        //turn other third pixel off
  } 

  j++;
}

void EfxAlarm::SetUp(uint32_t color){
  this->color = color;
}

void EfxAlarm::Reset(){
  j = 0;
}
