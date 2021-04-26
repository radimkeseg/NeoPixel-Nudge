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

const char PAGE_INDEX[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8">
	<title>NeoPixel Statue</title>

<script>
 var simplePicker = {
   colorize: function(color, destID){
     if(color.match(/^#[0-9a-f]{3,6}$/)){
     document.getElementById(destID).style.backgroundColor = color;
     document.getElementById(destID).className = "color-box";
   }else{
     document.getElementById(destID).style.backgroundColor = "";
     document.getElementById(destID).className = "color-box color-box-error";
   }
   },
   
   init: function(){
    this.colorize('{val-color-hours}','box-color-hours');
    this.colorize('{val-color-quarters}','box-color-quarters');
    this.colorize('{val-color-alarm}','box-color-alarm');
   }   
  };
  
  window.onload = function(){
    simplePicker.init();
  }
</script>
 
<style>
.color-box{
    width: 32px;
    height: 20px;
    display: inline-block;
    border: 1px solid #000;
    margin-bottom: -7px;
}
.color-box-error{
    border: 1px solid #f00;
}
</style>

<style>
hr {
  border: 0px;
  border-bottom: 1px solid black;
}
.btn-group {
  border: 0px solid black;
  -webkit-border-radius: 0px 10px 10px 10px;
  border-radius: 0px 10px 10px 10px; 
  background-color: #feefc3;
  padding: 5px;
  margin-bottom: 20px;
}
checkbox input:before {
  content: '';
  background: #fff;
  display: block;
  width: 10px;
  height: 10px;
  border: 1px solid black;
  margin-left: 0px;
}

input{
  transition: 0.5s;
}

label{
  display: block;
  width:100px;
  height: 25px;
  display: table-cell;
  vertical-align: bottom;
  white-space: nowrap;
}
label.title{
  width:150px;
  padding-left: 10px;
  padding-right: 10px;
  border-radius: 10px 10px 0px 0px; 
  background-color: #feefc3;
}
 </style>

<style>
.password + .unmask {
  position: realtive;
  right: 10px;
  top: 50%;
  transform: translateY(0%);
  text-indent: -9999px;
  width: 25px;
  height: 25px;
  background: #ccc;
  border-radius: 50%;
  cursor:pointer;
  border: none;
  -webkit-appearance:none;
}

.password + .unmask:before {
  content: "";
  position: absolute;
  top: 5px;
  left: 5px;
  width: 15px;
  height: 15px;
  background: #e3e3e3;
  z-index:1;
  border-radius: 50%;
}

.password[type="text"] + .unmask:after {
  content: "";
  position: absolute;
  top: 7px;
  left: 7px;
  width: 11px;
  height: 11px;
  background: #ccc;
  z-index: 2;
  border-radius: 50%;
}

 </style>
 </head>

<body>
<h1>NeoPixel Nodger</h1>
<p>
Neopixel Nodger with an ESP8266 IoT device
<p/>

<form method='post' action='settings'>
<label>UTC TimeOffset<br><input id='_timeoffset' name='_timeoffset' length=5 pattern='^[0-9-\\.]{1,5}$' required value='{timeoffset}'></label><br>
<label>DST<br><input id='_dst' name='_dst' type='checkbox' {dst}></label><br>
<br/>
<label>Brightness by daylight<br><input id='_brightness' name='_brightness' length=3 pattern='^[0-9]{3,0}$' value='{brightness}'></label><br>
<label>Brightness at night<br><input id='_brightness_night' name='_brightness_night' length=3 pattern='^[0-9]{3,0}$' value='{brightness_night}'>22:00-06:00</label><br>
<br/>
<lable>Clock colors:</label><br/>
<label><input id="input-color-hours" type="text" pattern="#[0-9a-f]{3,6}" name="_input-color-hours" title="e.g. #f00 or #ff0000" value="{val-color-hours}" onkeyup="simplePicker.colorize(this.value,'box-color-hours')" ><div class="color-box" id="box-color-hours"></div> hours</label><br/>
<label><input id="input-color-quarters" type="text" pattern="#[0-9a-f]{3,6}" name="_input-color-quarters" title="e.g. #0a0 or #00aa00" value="{val-color-quarters}" onkeyup="simplePicker.colorize(this.value,'box-color-quarters')"><div class="color-box" id="box-color-quarters"></div> quarters</label><br/>
<label>Animate<br><input id='_animate' name='_animate' type='checkbox' {animate}></label><br>
<br/>
<label>ALARM<br><input id='_alarm' name='_alarm' type='checkbox' {alarm}></label><br>
<label><input id="_input-color-alarm" type="text" pattern="#[0-9a-f]{3,6}" name="_input-color-alarm" title="e.g. #f0f or #ff00ff" value="{val-color-alarm}" onkeyup="simplePicker.colorize(this.value,'box-color-alarm')" ><div class="color-box" id="box-color-alarm"></div> alarm</label><br/>
<label>Time<br><input id='_alarmHour' name='_alarmHour' length=2 pattern='^[0-9]{2,0}$' value='{alarmHour}'>:<input id='_alarmMins' name='_alarmMins' length=2 pattern='^[0-9]{2,0}$' value='{alarmMins}'></label>
<br/>
<br/>
<label class='title'><input id='_mqtt' name='_mqtt' type='checkbox' {mqtt}>Send to Home Assisstant / MQTT broker</label>
<div class='btn-group'>
<table>
<tr><td><label>MQTT broker</label></td><td><input id='_mqtt_broker' name='_mqtt_broker' length=16 pattern='^.{1,255}$' required value='{mqtt_broker}'></td></tr>
<tr><td><label>User</label></td><td><input id='_mqtt_user' name='_mqtt_user' length=16 pattern='^[0-9a-zA-Z_\.]{1,255}$' required value='{mqtt_user}'></td></tr>
<tr><td><label>Password</label></td><td><input type='password' id='_mqtt_password' name='_mqtt_password' class='password' length=16 pattern='^.{1,255}$' required value='{mqtt_password}'><button class="unmask" type="button" title="Mask/Unmask password to check content" onClick="unmask('_mqtt_password')">Unmask</button></td></tr>
<tr><td><label>DeviceID</label></td><td><input id='_mqtt_device_id' name='_mqtt_device_id' length=16 pattern='^[0-9a-z_]{1,255}$' required value='{mqtt_device_id}'></td></tr>
<tr><td><label>Out Topic</label></td><td><input id='_mqtt_otopic' name='_mqtt_otopic' length=32 pattern='^[0-9a-z_/]{1,255}$' required value='{mqtt_otopic}'></td></tr>
<tr><td><label>In Topic</label></td><td><input id='_mqtt_itopic' name='_mqtt_itopic' length=32 pattern='^[0-9a-z_/]{1,255}$' required value='{mqtt_itopic}'></td></tr>
</table>
</div>

<input type='submit' value='Store'></form>

<script>
function unmask(pass_id){
  pass = document.getElementById(pass_id);
  if(pass.getAttribute('type') == 'password')
    pass.setAttribute('type','text');
  else
    pass.setAttribute('type','password');
  return false;
}  


function mqtt_checkbox(){
  var checkBox = document.getElementById('_mqtt');  
  document.getElementById("_mqtt_broker").disabled  = !checkBox.checked;
  document.getElementById("_mqtt_user").disabled  = !checkBox.checked;
  document.getElementById("_mqtt_password").disabled  = !checkBox.checked;
  document.getElementById("_mqtt_device_id").disabled  = !checkBox.checked;
  document.getElementById("_mqtt_otopic").disabled  = !checkBox.checked;
  document.getElementById("_mqtt_itopic").disabled  = !checkBox.checked;
}

function onLoad(){
  mqtt_checkbox();
  refresh();
}

document.getElementById('_mqtt').addEventListener('click',mqtt_checkbox);
setTimeout(onLoad, 500);   

</script>

</body>
</html>
)=====";
