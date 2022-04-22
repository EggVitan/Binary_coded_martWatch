#include <avr/sleep.h>
#include <avr/interrupt.h>

#include "../tinywiremcp23008-master/TinyWireM.h"
#include "../tinywiremcp23008-master/TinyWire_MCP23008.h"
TinyWire_MCP23008 ioH;
TinyWire_MCP23008 ioM;

namespace pinOrg
{
	#define Hl1 0
	#define Hl2 1
	#define Hl3 2
	#define Hl4 3

	#define Hr1 7
	#define Hr2 6
	#define Hr3 5
	#define Hr4 4

	#define Ml1 4
	#define Ml2 5
	#define Ml3 6
	#define Ml4 7

	#define Mr1 3
	#define Mr2 2
	#define Mr3 1
	#define Mr4	0

	#define ledHAdress 0b0100 1110
	#define ledMAddress 0b0100 0000
}

static uint8_t ledHl[3]{pinOrg::Hl1, pinOrg::Hl2,
	pinOrg::Hl3, pinOrg::Hl4};

static uint8_t ledHr[]{pinOrg::Hr1, pinOrg::Hr2,
	pinOrg::Hr3, pinOrg::Hr4};

static uint8_t ledMl[]{pinOrg::Ml1, pinOrg::Ml2,
	pinOrg::Ml3, pinOrg::Ml4};

static uint8_t ledMr[]{pinOrg::Mr1, pinOrg::Mr2,
	pinOrg::Mr3, pinOrg::Mr4};

#include "../RTClib-master/RTClib.h"
RTC_DS3231 rtc;

#define espComPin A2
#define espInterruptWakePeriod 1000
#define rtcSquarWave 1

uint16_t ledTime;
void timeAd()
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

void showTime()
{
	uint16_t andFilter = 0b0000 0000 0000 0001;
	for(uint16_t i = 0; i < 4; i++)
	{
		andFilter << 1;
		ledH.digitalWrite(ledMr[i], (ledTime & andFilter))
	}
	for(uint16_t i = 0; i < 4; i++)
	{
		andFilter << 1;
		ledH.digitalWrite(ledMl[i], (ledTime & andFilter))
	}
	for(uint16_t i = 0; i < 4; i++)
	{
		andFilter << 1;
		ledH.digitalWrite(ledHr[i], (ledTime & andFilter))
	}
	for(uint16_t i = 0; i < 4; i++)
	{
		andFilter << 1;
		ledH.digitalWrite(ledHl[i], (ledTime & andFilter))
	}
}

uint16_t convertToLedTime(int time[1])
{
	returnValue = 0;
	bool rand = false;

	//extract a digit from the two numbers.
	start:
	do
	{
		returnValue += time[rand] % 10;
		time[rand]/= 10;
		returnValue << 1; //bitshift the nubmers into ledTime var
	}while(time[rand] <=10)
	if(rand == false){rand = true; goto start;}
	return returnValue;
}

void updateTime()
{
	DateTime rtcTime = rtc.now();
	ledTime = convertToLedTime({DateTime.hour(), DateTime.minute()});
}

void sleep()
{
    GIMSK |= _BV(PCIE);					// Enable Pin Change Interrupts
    PCMSK |= _BV(rtcSquarWave);			// Set interrupt pin
    ADCSRA &= ~_BV(ADEN);				// ADC off
    wdt_disable();						//watchdog off
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);// replaces above statement
    sleep_enable();						// Sets the Sleep Enable bit in the MCUCR Register (SE BIT)
    sei();								// Enable interrupts
    sleep_cpu();						// sleep
    cli();								// Disable interrupts
    PCMSK &= ~_BV(PCINT3);				// Turn off PB3 as interrupt pin
    sleep_disable();					// Clear SE bit
    ADCSRA |= _BV(ADEN);				// ADC on
    sei();								// Enable interrupts
}

static uint16_t counter = 0;
//at wakeup
ISR(PCINT0_vect)
{
	counter++;
	//wakeup every second, every minute will something change
	if(counter < 60):
		sleep();

	timeAd();
	ioH.begin(pinOrg::ledHAdress);
	ioM.begin(pinOrg::ledMAddress);
	for(int i = 0; i <= 8; i++)
	{//set all output
		ioH.pinMode(i, OUTPUT);
		ioM.pinMode(i, OUTPUT);
	}
	showTime();
	sleep();
}

void setup()
{
	delay(1 000); //10 sek
	updateTime();
	rtc.writeSqwPinMode(DS3231_SquareWave1Hz);
	sleep();
}
