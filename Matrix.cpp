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

#include "Matrix.h"
    
//public:
void Matrix::Show(boolean clear_background, boolean mix_colors){
  uint32_t color = 0;
  int pos = 0;

  if(strip == NULL) return;
  
  long stamp = millis();
  if(stamp - last_time_update > time_update_interval || stamp < last_time_update ){
    last_time_update = stamp;
    timeClient.updateTime();
  }

  if(clear_background) strip->clear();

  /* regular animation
  



   
   */

  strip->show();  
}

void Matrix::SetTimeOffset(int time_offset){
  timeClient.setTimeOffset(time_offset);
  timeClient.updateTime();
}

/**
 * setPixel need to adress proper pixel in Matrix 10x8, howerver the trick is in the wiringm which needs to be solved
 * start═X-X-X-X-X-X-X╗
 *      ╔X-X-X-X-X-X-X╝
 *      ╚X-X-X-X-X-X-X╗
 *      ╔X-X-X-X-X-X-X╝
 *      ╚X-X-X-X-X-X-X
 */
void Matrix::setPixel(int pos, uint32_t color, boolean mix_color){
  pos = pos % strip->numPixels(); //just to address the pixels in circular buffer
  int x = pos % pixels_in_row;
  int y = pos / pixels_in_row;

  setPixel(x, y, color, mix_color);
}

void Matrix::setPixel(int x, int y, uint32_t color, boolean mix_color){
  int pos = 0;
  if(y%2 == 0){ //even row - counting from 0
    pos = y*pixels_in_row + x;
  }else{//odd row
    pos = (y+1)*pixels_in_row - x - 1;
  }
  
  if(mix_color){
    uint32_t bg_color = strip->getPixelColor(pos);
    if( bg_color == 0 ) //if bg color is black dont mix just draw
      strip->setPixelColor(pos, color);
    else
      strip->setPixelColor(pos, mixColors(bg_color, color));
  }else{
    strip->setPixelColor(pos, color);
  }

}


