//Tobias was here
#include <Wire.h>
#include "ds3231.h" // https://github.com/rodan/ds3231

#define BUFF_MAX 128

uint8_t time[8];
char recv[BUFF_MAX];
unsigned long prev, interval = 5000; //interval = milisecondt to wait between each return
void binary_led_show(uint16_t); // We have less than 16 leds, 
//0b1100 1101 1111 0111

void setup()
{
    Wire.begin();
    DS3231_init(DS3231_CONTROL_INTCN);
    memset(recv, 0, BUFF_MAX);
    // We dont have serial aparently :(
}

void loop()
{
    char buff[BUFF_MAX];
    uint16_t now = millis();
    struct ts t;

    // show time once in a while
    if (now - prev > interval) {
        DS3231_get(&t);
  
        // there is a compile time option in the library to include unixtime support
        snprintf(buff, BUFF_MAX, "%d", t.unixtime); // limits size
        //Serial.println(buff);
        
        prev = now;
    }
}
