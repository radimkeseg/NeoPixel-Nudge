# ESP8266-NeoPixel-Nudge

Neopixel homemade clock (quater announcer) with nudge and alarm feature

* also works as a wall clock see:
 * //#define SHOWCLOCK //to show clock
 * //#define PLAYSONG  //to play sound


## Setup

* Download this project either with a git checkout or press "Download as zip"
* Install the following librarys with your Arduino Library Manager in Sketch > Include Library > Manage Libraries...
 * Adafruit Neopixel
 * WiFiManager (tzapo)
 * PubSub (mqtt)
 * ArduinoJson (JsonParser)

## Example of interaction

MQTT
execute color effect
* payload -> { "color": "00ffff", sec : 5}

execute color effect and play song
* payload -> { "color": "00ffff", sec : 5, song: 1, volume: 30 }

click the SETUP PIN -> ESP01 GPIO0
* payload ->  { click:1, sec: 1 }


## Components
* Esp8266 ESP-01 http://www.ebay.com/itm/1-2-5PCS-ESP8266-ESP-01-Serial-WIFI-Wireless-Transceiver-Wireless-Module-AP-STA-/191995377029?var=&hash=item2cb3d0f585:m:m0s8RCLsHPdb53jvkd0ZbWg
* NeoPixel stripe or 3 times WS2812 5050 elements
