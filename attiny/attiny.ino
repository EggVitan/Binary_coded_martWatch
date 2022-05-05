#include <Wire.h>
#include "LowPower.h" // https://www.arduino.cc/en/Reference/ArduinoLowPower
#define SLAVE_ADDR 0x69 //Nice number
#define interruptPin x
void timeAdd();
void turnemon(uint16_t);
void beforeWeAdd();
uint16_t ledTime;
uint16_t customDisplay;

// The leds
const int LED_PINS[] = {D1,D2,D3,D4,D5,D6,D7,D8,D9} //placeholder numbers for now
//wait maybe

void setup() {
  // Initaliz I2C communication as slave
  Wire.begin(SLAVE_ADDR);
  Wire.onReceive(receiveEvent);
}

void loop() {
  // A mimir
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
}

// Recive stuff over I2C
void receiveEvent(){
  // invokes only once
  static bool invoked;
  if (invoked != 1) {
    while (Wire.available() > 0) {
      uint8_t firstByte = Wire.read();
      uint8_t secondByte = Wire.read();
      ledTime = (firstByte << 8) + secondByte;
      invoked = 1;
    }
  } else {
    while (Wire.available() > 0) {
      uint8_t firstByte = Wire.read();
      uint8_t secondByte = Wire.read();
      customDisplay = (firstByte << 8) + secondByte;
    }
  // Cant have it looking for interrupts before ledTime gets defined.
  attachInterrupt(interruptPin, beforeWeAdd, RISING); 
  // Turn on the appropriate LEDs
  turnemon(ledTime);
}

void turnemon(uint16_t leds) {
  int16_t andFilter = 0x0001; //0b 0000 0000 0000 0001
  for(int i = 0; i < 16; i++) {
    digitalWrite(LED_PINS[i], ledTime & andFilter);
    andFilter << 1;
  }
}

// Gets envoced every second, but only invokes timeAdd once per minute.
void beforeWeAdd() {
  static int8_t count;
  count++;
  if (count >= 60 ) {
    timeAdd();
    count = 0;

    //If not running game
    turnemon(ledTime);
  }
}

// Stuff, idk
void timeAdd()
{
  namespace numbers
  {
    #define bitFilter 0xFFF0
    #define MrAd 0x0001 // 0b0000 0000 0000 0001
    #define MlAd 0x0010 // 0b0000 0000 0001 0000
    #define HrAd 0x0100
    #define HlAd 0x1000
  }
  ledTime += numbers::MrAd; //ledTime++

  //Gives me Mr time isolated
  uint16_t temp = ledTime & 0x000F;
  if(temp >= 10)
  {
    ledTime += numbers::mlAd;

    uint16_t EndFilter = 0xFFF0;

    temp = ledTime & 0x00F0;
    temp >> 4;
    if(temp >= 6)
    {
      ledTime += numbers::HrAd;
      endFilter = 0xFF00;
      temp = ledTime & 0x0F00;
      temp >> 8;
      if(temp >= 10)
      {
        ledTime += numbers::HlAd;
        endFilter = 0xF000;
        temp = ledTime & 0xF000;
        temp >> 12;

        if(temp >= 3)
        {
          endFilter = 0b0000000000000000;
        }
      }
    }
    ledTime = ledTime & endFilter;
  }
}
