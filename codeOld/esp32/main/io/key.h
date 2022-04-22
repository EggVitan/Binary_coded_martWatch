#pragma once

#ifndef longPress_in_milliseconds
	#define longPress_in_milliseconds 50
#endif

#ifndef VerylongPress_in_milliseconds
	#define VerylongPress_in_milliseconds 100
#endif

#ifndef fromKeyCPP
enum pressType
{
	quick,
	Long,
	veryLong
}
pressType press(uint8_t keyPin, bool isTouch = false);
bool SimpPress(uint8_t keyPin, bool isTouch = false);
bool longPress(uint8_t keyPin, bool isTouch = false);
int select(int range);
uint8_t binarySelect(bool B1, bool B2, uint timeout = NULL);

#endif