#include "../Def.h"
#include <Adafruit_MCP23008>

//Adafruit_MCP23008 ledH;
//Adafruit_MCP23008 ledM;

using namespace Def;
uint8_t ledHl[]{Hl1, Hl2, Hl3, Hl4};
uint8_t ledHr[]{Hr1, Hr2, Hr3, Hr4};
uint8_t ledMl[]{Ml1, Ml2, Ml3, Ml4};
uint8_t ledMr[]{Mr1, Mr2, Mr3, Mr4};
Adafruit_MCP23008 ledH;
Adafruit_MCP23008 ledM;

void ledSetup()
{
	ledH.begin(ledHAdress);
	ledM.begin(ledMAddress);
	for(int i = 0; i <= 8; i++)
	{
		led[0].pinMode(i, OUTPUT);
		led[1].pinMode(i, OUTPUT);
	}

}
/*Will print data like
Hl1, Hr1, Ml1, Ml1,
Hl2, Hr2, Ml2, Ml2,
Hl3, Hr3, Ml3, Ml3,
Hl4, Hr4, Ml4, Ml41*/
void showHorizontal(const uint16_t data)
{
			//0123 4567 89ab cdef
	uint16_t andFilter = 0b0000 0000 0000 1000;
	for(uint16_t i = 0; i < 4; i++)
	{
		andFilter << 4;
		ledH.digitalWrite(ledHl[i], (data & andFilter))
	}
	andFilter = 0b0000 0000 0000 0100;
	for(uint16_t i = 0; i < 4; i++)
	{
		andFilter << 4;
		ledH.digitalWrite(ledHr[i], (data & andFilter))
	}
	andFilter = 0b0000 0000 0000 0010,
	for(uint16_t i = 0; i < 4; i++)
	{
		andFilter << 4;
		ledH.digitalWrite(ledMl[i], (data & andFilter))
	}
	andFilter = 0b0000 0000 0000 0001;
	for(uint16_t i = 0; i < 4; i++)
	{
		andFilter << 4;
		ledH.digitalWrite(ledMr[i], (data & andFilter))
	}
}

void showVertical(const uint16_t data)
{

	uint16_t andFilter = 0b0000 0000 0000 0001;
	for(uint16_t i = 0; i < 4; i++)
	{
		andFilter << 1;
		ledH.digitalWrite(ledMr[i], (data & andFilter))
	}
	for(uint16_t i = 0; i < 4; i++)
	{
		andFilter << 1;
		ledH.digitalWrite(ledMl[i], (data & andFilter))
	}
	for(uint16_t i = 0; i < 4; i++)
	{
		andFilter << 1;
		ledH.digitalWrite(ledHr[i], (data & andFilter))
	}
	for(uint16_t i = 0; i < 4; i++)
	{
		andFilter << 1;
		ledH.digitalWrite(ledHl[i], (data & andFilter))
	}
}

#define fromledCPP
#include led.h
void blink()
{
	showHorizontal(0xFFFF);
	delay(blinkTime);
	showHorizontal(NULL);
	delay(blinkTime)
}

void blink(uint16_t delay, uint16_t times)
{
	for(int i = 0; i < times; i++)
	{
		showHorizontal(0xFFFF);
		delay(delay);
		showHorizontal(NULL)
		delay(delay);
	}

}