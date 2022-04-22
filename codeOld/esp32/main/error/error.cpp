#include <LinkedList.h>
#include "../io/led.h"
#include "../io/key.h"
#include "../Def.h"
#define fromCPPfileIFDEF
#include "error.h"

#define EOT (char)4

enum dataTypeEn
{
	staticT,
	heapT,
	StackT
};

String enumToString(errorEn error)
{
	switch(error)
	{
		case noError: return "noError"; break; 
		case RTCNotFound: return "RTCNotFound"; break; 
		case couldntOptainDateTime: return "couldntOptainDateTime"; break; 
		case couldntConnectToWifi: return "couldntConnectToWifi"; break; 
		case couldntChangeStorageData: return "couldntChangeStorageData"; break; 
	}
}

LinkedList<error> errorData = LinkedList<error>();

//return false if wifi didn't work
void SaveERROR(error errorIn)
{
	errorData.add(errorIn);
}

String reportErrorStr()
{
	String returnValue = "";
	for(int i = 0; i <= errorData.size(); i++)
	{
		returnValue += enumToString(errorData[i]);
		returnValue += NULL;
	}
	return returnValue + EOT;
}

uint16_t enumToBlink(errorEn error)
{
	switch(error)
	{
		case noError: 					return NULL;
		case RTCNotFound: 				return (uint16_t) ( (uint8_t)error << 8 + 0b0100 1000);
		case couldntOptainDateTime: 	return (uint16_t) ( (uint8_t)error << 8 + 0b1000 1000);
		case couldntConnectToWifi: 		return (uint16_t) ( (uint8_t)error << 8 + 0b1000 1000);
		case couldntChangeStorageData: 	return(uint16_t) ( (uint8_t)error << 8 + 0b1000 1000);
	}	
}

void reportErrorLed()
{
	for(int i = 0; i < errorData.size(); i++)
	{
		blink(50, def::errorReportStartBlink);//ms, times
		showVertical(enumToBlink(errorData[i]));
		bool x = false;
		while(true)
		{
			if(longPress(Def::B1))
				break;
		}

	}

}

void reportErrorLed(errorEn error)
{
	blink(50, 3);//ms, times
	showVertical(enumToBlink(errorData[i]));
}

void cleanErrorData()
{
	errorData.clear();
}

void removeErrorData(errorEn error)
{
	for(int i = 0; i < errorData.size(); i++)
	{
		if(errorData[i] == error)
		{
			errorData.remove(i);
			return;
		}
	}
}

void B1()//led
{
	for(int i = 0; i <= errorData.length(); i++)
	{
		long waitBreak = millis() + def::inputTimeoutTime;
		enumToBlink(errorData[i]);
		while(waitBreak > millis())
		{
			if(key::SimpPress(def::B2))
				break
			if(key::SimpPress(def::B1))
				waitBreak = millis() + def::inputTimeoutTime;
		}
		
	}

}
void B2() //online
{

}

void errorUI()
{
	switch(key::binarySelect(def::B1, def::B2, def::inputTimeoutTime))
	{
		case 0: B1(); break;
		case 1: B2(); break;
		case 3: return; 
	}

}