#include "../includes.h"
#include "../../RTClib-master/RTClib.h"
using namespace led;
using namespace error;

extern uint16_t ledTime;
extern RTC_DS3231 rtc;

namespace numbers
{
	#define 4bitFilter 0b0000000000001111
	#define MrAd 1
	#define MlAd 16
	#define HrAd 256
	#define MlAd 268435456
}

void showCalendar()
{
	Datetime datetime = rtc.now();
	uint16_t data = 0x0000;
	data += Datetime.month(); //0x000M
	data << 5 //0x000M << 5 = 0d0000 000M MMM0 0000
	data += Datetime.day(); // 0d0000 000M MMMD DDDD
	data << 3; // 0d0000 MMMM DDDD D000
	data += dayOfTheWeek(); //0D0000 MMMM DDDD DWWWW

	led::showVertical(data);
}

void showTemp()
{
	double temp = rtc.getTemperature();
	char tempStr[3];
	sprintf(tempStr,"%f",temp);//convert to string
	uint16_t showValue = 0;
	for(int i = 0; i < 3; i++)
	{
		showValue += tempStr[i]-48;//-48 to convert to int
		showValue << 4;
	} 
	showValue += tempStr[3]-48;//-48 to convert to int
	showVertical(showValue);
}


void convert(int time[1])
{
	ledTime = 0;
	bool rand = false;
	
	//extract a digit from the two numbers. 
	start:
	do
	{
		ledTime += time[rand] % 10;
		time[rand]/= 10;
		ledTime << 1; //bitshift the nubmers into ledTime var	
	}while(time[rand] <=10)
	if(rand == false){rand = true; goto start;}
}

//extract data from ledTime, hl = 3, hr= 2, ml = 1, mr = 0
uint16_t extract(int wich)
{				 		 //0123456789abcdef
	uint16_t andFilter = 0b0000000000001111;
	x << (wich*4);
	uint16_t returnValue = ledTime & andFilter;
	returnValue >> (wich*4);
	return returnValue;
}

//Ad 1 to the time
void timeAd()
{
	ledTime++; 

	uint16_t temp = ledTime & 0b0000000000001111;
	if(temp >= 10)
	{
		ledTime += numbers::mlAd;

		uint16_t EndFilter = 0b1111111111110000;
		
		temp = ledTime & 0b0000000011110000;
		temp >> 4;
		if(temp >= 6)
		{
			ledTime += numbers::HrAd;
			endFilter = 0b1111111100000000;
			temp = ledTime & 0b0000111100000000;
			temp >> 8;
			if(temp >= 10)
			{
				ledTime += numbers::HlAd;
				endFilter = 0b1111000000000000;
				temp = ledTime & 0b1111000000000000;
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

void setLed()
	led::showvertical(ledTime);

clockCl()
{
	if(! rtc.begin())
		error::errorReport(RTCNotFound);
	
	//I use internal crystal oscillator
	rtc.disable32K();
	
	//Set time
	rtc.adjust(Datetime(wifi::getTime() ) );
	{	
		Datetime temp = rtc.now();
		convert({temp.hour, temp.minute});
	}
}

