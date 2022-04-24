#include <Wire.h>
#define SLAVE_ADDR 0x69 //Nice number
void timeAdd();

void setup() {
  // Initaliz I2C communication as slave
  Wire.begin(SLAVE_ADDR);
  Wire.onReceive(receiveEvent);

}

void loop() {
  // put your main code here, to run repeatedly:
  
}

void receiveEvent(){
  // Reads data from master
  while (Wire.available() > 0) {
    uint16_t data = Wire.read();
  }
  // Turn on the appropriate LEDs
}

// Stuff, idk
uint16_t ledTime;
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
