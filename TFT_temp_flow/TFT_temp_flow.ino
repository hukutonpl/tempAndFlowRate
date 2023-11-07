//by hukuton pl

#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>
#include <DS18B20.h>
#include <FlowSensor.h>

TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h
DS18B20 ds(13);
FlowSensor FlowMeter(YFS201, 34);

int16_t background1 = TFT_BLACK;
int16_t background2 = TFT_BLACK;
int16_t background3 = TFT_BLACK;

float tempIn, tempOut;
float flowRate;

const float MAX_TEMP_IN   = 30.0; //In Celcius
const float MIN_TEMP_IN   = 18.0; //In Celcius

const float MAX_TEMP_OUT  = 30.0; //In Celcius
const float MIN_TEMP_OUT   = 18.0; //In Celcius

const float MIN_FLOW_RATE = 0.5; //In L/min

int16_t xCenter;
int16_t yPos = 0;

void IRAM_ATTR count()
{
  FlowMeter.count();
}

void tempInBackgroundColor(float tempIn) {
  if (tempIn < MIN_TEMP_IN) {
    background1 = (background1 == TFT_BLACK) ? TFT_BLUE : TFT_BLACK;
  } else if (tempIn > MAX_TEMP_IN) {
    background1 = (background1 == TFT_BLACK) ? TFT_RED : TFT_BLACK;
  } else {
    background1 = TFT_BLACK;
  }
}

void tempOutBackgroundColor(float tempOut) {
  if (tempOut < MIN_TEMP_OUT) {
    background2 = (background2 == TFT_BLACK) ? TFT_BLUE : TFT_BLACK;
  } else if (tempOut > MAX_TEMP_OUT) {
    background2 = (background2 == TFT_BLACK) ? TFT_RED : TFT_BLACK;
  } else {
    background2 = TFT_BLACK;
  }
}

void flowBackgroundColor(float waterFlow){
  if (waterFlow < MIN_FLOW_RATE) {
    background3 = (background3 == TFT_BLACK) ? TFT_RED : TFT_BLACK;
  } else {
    background3 = TFT_BLACK;
  }
}

void setup(void) {
  Serial.begin(9600);
  FlowMeter.begin(count);

  Serial.print("Devices: "); //temp sensor
  Serial.println(ds.getNumberOfDevices());
  Serial.println();

  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  xCenter = tft.width()/2 - 1;
}

void loop() {
  String buffer1;
  String buffer2;
  String buffer3;

  while (ds.selectNext()) {

    uint8_t address[8];
    ds.getAddress(address);

    Serial.print("Address:");
    for (uint8_t i = 0; i < 8; i++) {
      Serial.print(" ");
      Serial.print(address[i]);
    }
    Serial.println();

    if(address[7] == 167) { //address ends with 167 is set for In sensor
      Serial.print("Temperature In: ");
      tempIn = ds.getTempC();
      Serial.print(tempIn);
      Serial.print(" C");
    } else if (address[7] == 11) { //address ends with 11 is set for Out sensor
      Serial.print("Temperature Out: ");
      tempOut = ds.getTempC();
      Serial.print(tempOut);
      Serial.print(" C");
    }
    Serial.println();
  }

  // if(tempIn > 30.0 || tempOut > 30.0 || flowRate < 0.5){
  //   background = (background == TFT_BLACK) ? TFT_RED : TFT_BLACK;
  // } else {
  //   background = TFT_BLACK;
  // }


  FlowMeter.read();
	Serial.print("Flow rate (L/minute) : ");
  flowRate = FlowMeter.getFlowRate_m();
	Serial.println(flowRate);
  Serial.println();

  tft.setTextPadding(-100);
  tft.setTextDatum(TC_DATUM);
  tft.setTextColor(TFT_YELLOW);
  tft.setTextSize(1);
  tft.drawString("Water Temps & Flow", xCenter, 1, 2);

  tft.drawLine(0, 1, tft.width()-1, 1, TFT_YELLOW);
  tft.drawLine(0, 17, tft.width()-1, 16, TFT_YELLOW);

  buffer1 += String(tempIn, 2);
  buffer1 += F(" `C");
  buffer2 += String(tempOut, 2);
  buffer2 += F(" `C");
  buffer3 += String(flowRate, 1);
  buffer3 += F(" L/m");

  // Temperature 1
  tempInBackgroundColor(tempIn);
  tft.setTextColor(TFT_WHITE, background1);  
  tft.setTextSize(2);
  tft.drawString(buffer1, xCenter, 31, 2);
  tft.setTextSize(1);
  tft.drawString("Temp In:", xCenter, 19, 2);



  // Temperature 2
  tempOutBackgroundColor(tempOut);
  tft.setTextColor(TFT_WHITE, background2);  
  tft.setTextSize(2);
  tft.drawString(buffer2, xCenter, 74, 2);
  tft.setTextSize(1);
  tft.drawString("Temp Out:", xCenter, 61, 2);



   // Water Flow
  flowBackgroundColor(flowRate);
  tft.setTextColor(TFT_WHITE, background3);  
  tft.setTextSize(2);
  tft.drawString(buffer3, xCenter, 119, 2);
  tft.setTextSize(1);
  tft.drawString("Water Flow:", xCenter, 105, 2);

  delay(1000);
}



