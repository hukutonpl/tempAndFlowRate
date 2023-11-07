# tempAndFlowRate
Monitor CO2 laser temperature and flow rate using ESP32

This is a project for my CO2 laser with 
1. Monitor temperature using DS18B20
2. Water flow using YFS201 
3. ESP32 microcontroller
4. TFT 1.8 inch display

Here is the library used:
#include <TFT_eSPI.h> //by bodmer
#include <SPI.h>
#include <DS18B20.h> 
#include <FlowSensor.h> //by Hafidh Hidayat


##Display Wiring
Display     	ESP32
VCC 	--> 	5V
RESET 	--> 	G14	
GND 	--> 	GND
LED 	--> 	3.3V
SDA 	--> 	G23	
SCK 	--> 	G18	
CS 		--> 	G17
A0 		--> 	G2

You will need to modify User_Setup.h. Modified file included here
Read more here https://www.az-delivery.de/blogs/azdelivery-blog-fur-arduino-und-raspberry-pi/1-8-toll-tft-am-esp-32-dev-kit-c-betreiben

For temperature and flow rate sensor, I used breakout module. One for both DS18B20 and one for YFS201. See sensor2.jpg

##DS18B20 Wiring
DS18B20     	ESP32
VCC 	--> 	5V
GND 	--> 	GND
Data 	--> 	13


##YFS201 Wiring
YFS201     	ESP32
VCC 	--> 	5V
GND 	--> 	GND
Data 	--> 	34


You can modify the temp and flow rate to your wants.

const float MAX_TEMP_IN   = 30.0; //In Celcius
const float MIN_TEMP_IN   = 18.0; //In Celcius

const float MAX_TEMP_OUT  = 30.0; //In Celcius
const float MIN_TEMP_OUT  = 18.0; //In Celcius

const float MIN_FLOW_RATE = 0.5; //In L/min

To change celcius to fahrenheit if fairly easy. Change all 
ds.getTempC(); to ds.getTempF();

You will get nan flow rate reading if delay < 1000 ms. Set it to atleast 1000 ms
delay(1000);
