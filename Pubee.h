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

#define ps_NONE "NONE"
#define ps_IDLE "IDLE"
#define ps_ACTION "ACTION"
#define ps_ALARM "ALARM"
#define ps_FULLHOUR "FULLHOUR"
#define ps_QUARTER "QUARTER"
#define ps_ANIMATION "ANIMATION"
#define ps_RESTART "RESTART"

typedef enum pubeeStates { NONE, IDLE, ACTION, ALARM, FULLHOUR, QUARTER, ANIMATION, RESTART } pubeeStates;

class Pubee
{
    private:
     pubeeStates pubee;

    public:
      Pubee(){pubee = NONE;}
      ~Pubee(){};
      
      bool setStatus(pubeeStates status){
         if(pubee==status) return false;
         else pubee=status; 
         return true;        
      }

      String getStatus(){
        switch(pubee){
          case NONE: return ps_NONE;
          case IDLE: return ps_IDLE;
          case ACTION: return ps_ACTION;
          case ALARM: return ps_ALARM;
          case FULLHOUR: return ps_FULLHOUR;
          case QUARTER: return ps_QUARTER;
          case ANIMATION: return ps_ANIMATION;
          case RESTART: return ps_RESTART;
          default: return ps_NONE;
        }
      }
};
