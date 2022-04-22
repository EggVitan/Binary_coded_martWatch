#include "../../Def.h"
#include "../error/error.h"
#include "../../io/key.h"
#include "../../io/led.h"

#define connectWate 2000 //ms

// SSID MIGHT NOT BE DEFINED!
char SSID[] = Pin::SSID; 
// password MIGHT NOT BE DEFINED!
char password[] = Pin::password; 

//return true if connected
//make so you can try to connect to multiple wifi network
bool wifiConnect()
{
	WiFi.begin(SSID, password);
	int timeStart = millis();
	while(Wifi.status != WL_CONNECTED && millis() < timeStart+connectWate)
	{	}
	if(Wifi.status == WL_CONNECTED)
		return true;
	else
		return false;
}

void website()
{

}	

void hotspot()
{

}

void jammer()
{
	
}

void wifi()
{

	/*	void (*func[])(const uint8_t&, const uint8_t&, const Datetime datetime)
			= { home, calendar, temperature, wifi, bluetooth}; //functptr
		
		(*func[select(ButtonPin)])(LEDPin, buttonPin, datetime);
	*/
	switch(select(ButtonPin))
	{
		case 0: return;
		case 1: website();
		case 2: hotspot();
		case 3: jammer();
	}
}

#include "time.h"
//not sure if it works
uint32_t getTime()
{
	using namespace error;
	#define gmtOffset 3600

	static bool dayLightSaving = true;
	
	if(!wifiConnect())
		errorReport(couldntConnectToWifi); return NULL;

	//from timeLIB?
	configTime(gmtOffset, (int)gmtOffset*3600, pin::ntpServer);

	uint32_t returnValue;
	if(!getLocalTime(&returnValue))
		errorReport(couldntOptainDateTime);

	return returnValue;
}

