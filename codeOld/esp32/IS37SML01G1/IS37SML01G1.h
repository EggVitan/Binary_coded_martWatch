#ifndef IS37SML01G1_LIB_DEF
#define IS37SML01G1_LIB_DEF
#include <SPI.h>

class IS37SML01G1
{
public:

	#define encryptionStart 0x0000 0000
	#define encryptionEnd 0x0000 0780
	#define ContendStart 0x0000 0780
	#define ContendEnd 0x3B6D 0340
	#define PointerStart 0x3B43 1909
	#define PointerEnd 0x3B9A CA00

	const int SS;
	IS37SML01G1(int SSpin)
	{SS=SSpin;}
	bool IS37SML01G1::WriteAt(uint32_t Address, const char* Data);
	String IS37SML01G1::ReadAt(uint32_t Address, const char* Data);

	bool IS37SML01G1::WritePointer(const uint32_t pointTo, const char* name);
	//return null if multable answers
	uint32_t IS37SML01G1::ReadPointer(const char* name);
	
	//return device identifier
	uint16_t IS37SML01G1::WriteEncryptionKey(const char* key);

	//DONT FORGET TO DELETE HEAP ALLOCATED STRING
	char* IS37SML01G1::ReadEncryptionKey(uint8_t KeyNum); 
	bool deleteEncryptionKey(uint8_t deviceID);


	bool IS37SML01G1::WriteContent(const char* data);
	String IS37SML01G1::ReadContent(uint32_t pointer);
	//return null if non found, return NAK if multable found 
	//followed by all possibilities separated by null
	//type == 0xFF ? dont care : only that type. se faq.txt for what the diffrent values are
	String IS37SML01G1::ReadContent(const char* finder, uint8_t type);
	String IS37SML01G1::ReadContent(const char* finder, uint8_t type, char startData);

	//write new content and pointer 
	bool IS37SML01G1::WriteNew(const char* data);
	bool IS37SML01G1::ChangeData(const char* data, uint32_t pointer);

private:
#define maxSpeed 104 000 000 //104 mhz
SPI.beginTransaction(SPISettings(maxSpeed, MSBFIRST, SPI_MODE0));

};



#endif