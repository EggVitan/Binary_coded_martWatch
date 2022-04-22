#include "../Def.h"
#include "SD.h"
#include "SPI.h"
#include "../error/error.h"

/*
	#define encryptionStart 0x0000 0000
	#define encryptionEnd 0x0000 0780
	#define ContendStart 0x0000 0780
	#define ContendEnd 0x3B6D 0340
	#define PointerStart 0x3B43 1909
	#define PointerEnd 0x3B9A CA00
*/
namespace sd
{
	Sd2Card card;
	SdVolume volume;
	SdFile root;
	const int cs = def::SD_SSPin;
};

bool WriteAt(uint32_t Address, const char* Data)
{
	
}

String ReadAt(uint32_t Address, const char* Data);

bool WritePointer(const uint32_t pointTo, const char* name);
//return null if multable answers
uint32_t ReadPointer(const char* name);

//return device identifier
uint16_t WriteEncryptionKey(const char* key);

//DONT FORGET TO DELETE HEAP ALLOCATED STRING
char* ReadEncryptionKey(uint8_t KeyNum); 
bool deleteEncryptionKey(uint8_t deviceID);


bool WriteContent(const char* data);
String ReadContent(uint32_t pointer);
//return null if non found, return NAK if multable found 
//followed by all possibilities separated by null
//type == 0xFF ? dont care : only that type. se faq.txt for what the diffrent values are
String ReadContent(const char* finder, uint8_t type);
String ReadContent(const char* finder, uint8_t type, char startData);

//write new content and pointer 
bool WriteNew(const char* data);
bool ChangeData(const char* data, uint32_t pointer);

//return true if successful
bool setup()
{
	if (!sd::card.init(SPI_HALF_SPEED, sd::cs)
		SaveERROR(SD_errorInit); return false;
	
	if (!volume.init(card)) {
		SaveERROR(SD_volumeError); return false;

	return true;
}