#include "../../Vector-master/src/vector.h"
#include "../includes.h"

static Vector<void(*)()> B1SelectPin
{
	clock::showCalendar, 
	clock::showTemp, 
	wifi::wifi, 
	bluetooth::bluetooth
};

    void(*point[])()

static void(*B2TouchMacro[5])()
{

};

static uint8_t touchLowValue = 30;