/*
In init.h initNam::Pin have M13 and M14 as TXD0
I don't know if they are defined. if not. tha could be a problem.

*/

#include <arduino>
#include "includes.h"
#include "../ulptool-master/srd/include/ulptool/ulptool"

//PUBLIC


//Pin enum
void sleep()
{
	using namespace Def;
	//wakeup if any pin/button is "onstate"
	esp_sleep_enable_ext0_wakeup(B1, onState);
	esp_sleep_enable_ext1_wakeup(B2, onState);

	ULP::start_ulp_program();
	esp_deep_sleep_start();
}

//IRAM_ATTR is used with interrupt
void IRAM_ATTR charging()
{
	led::blink(50, 5);

}

void B1();
void B1();
void setup()
{
	{
		using namespace def;
		pinMode(B1, INPUT);
		pinMode(B2, INPUT);
	}

	esp_sleep_wakeup_cause_t wakeupCause = esp_sleep_get_wakeup_cause();
	if(wakeupCause != esp_sleep_wakeup_cause_t)
	{
		led::ledSetup();
		clock::clockSetup();
		ULP::init_ulp_program();
	}

	//				PIN 			 FUNC	mode (when high)
	attachInterrupt(Def::isCharging, charging, HIGH);

	static const void (*func[])()
			= { B1, B2, bluetooth, wifi}; //functptr

	uint16_t sleepTime = millis() + def::awakeTime;
	while(true)
	{
		switch(wakeupCause)
		{
			case ESP_SLEEP_WAKEUP_EXT0: B1();
			case ESP_SLEEP_WAKEUP_EXT1: B2();
		}
		if(millis() <= sleepTime):
			sleep();
	}
}

void home()
	{return;}

void B1()
	*publicVars::B1SelectPin[ key::select(publicVars::B1SelectPin.size() ) ] ();

void B2()
{
	using namespace key;

	delay(10);
	if(digitalRead(def::b2) && longPress(def::B2))
	{
		using namespace passwordManagment;
		uint8_t select = binarySelect(def::b1, def::b2, def::inputTimeoutTime);
		if(select == 1)
			bloutoothPasword();
		else if(select == 2)
			wifiPasword();

		return;
	}

	uint32_t* timeout = new uint32_t(millis() + def::awakeTime);
	uint8_t pinData;
	while (timeout < millis() && !pinData)
	{
		pinData =
			touchRead(def::T1) << 1 +
			touchRead(def::T2) << 1 +
			touchRead(def::T3);

		publicVar::B2TouchMacro[pinData];
	}

}
