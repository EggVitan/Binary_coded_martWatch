
#define fromKeyCPP
#include "key.h"
#include "../publicVars/publicVars.h"

enum pressType
{
	quick,
	Long,
	veryLong
}

bool digitalReadCustom(uint16_t key, bool isTouch)
{
	if(isTouch)
	{
		if(touchRead(key) == publicVars::touchLowValue)
			return true;
		return false;
	}
	return digitalReadCustom(key);
}

pressType press(uint8_t keyPin, bool isTouch = false)
{
	long x;
	long y;
	bool escape = true;
	while(escape)
	{
		while(digitalReadCustom(keyPin))
		{
			x = millis();
			escape = false;
		}
	}
	y = millis();
	if(x-y > veryLong)
		return veryLong;
	else if(x-y < Long)
		return Long;

	return quick;
}

bool SimpPress(uint8_t keyPin){
	return digitalReadCustom(keyPin);}

bool longPress(uint8_t keyPin, bool isTouch = false)
{
	long x;
	long y;
	bool escape = true;
	while(escape)
	{
		while(digitalReadCustom(keyPin))
		{
			x = millis();
			escape = false;
		}
	}
	if(x-y > Long)
		return true;
	return false;
}
bool verylongPress(uint8_t keyPin, bool isTouch = false)
{
	long x;
	long y;
	bool escape = true;
	while(escape)
	{
		while(digitalReadCustom(keyPin))
		{
			x = millis();
			escape = false;
		}
	}
	if(x-y > veryLong)
		return true;

	return false;
}

int select(int range, bool isTouch = false)
{

	#define breakPin initNam::Pin::B2
	#define cyclePin initNam::Pin::B1
	 
	int i = 0;
	while(true)
	{
		if(SimpPress(breakPin))
			return i;

		else if(SimpPress(cyclePin))
			i++; continue;

		else if(i > range)
			i = 0; blink();
	}
}

uint8_t binarySelect(bool B1, bool B2, uint timeout = NULL, bool isTouch = false)
{
	long stopTime = timeout ? timeout + millis() : NULL;
	long stopTime = millis() + timeout;
	while(true)
	{
		if(SimpPress(B1))
			return 1;
		
		else if(SimpPress(B2))
			return 2;
		
		else if(stopTime)
			if(stopTime < millis())
				return null;
	}
}