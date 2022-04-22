#include "../Def.h"
#include <SPI.h>
#include <SD.h>
#define fromStorageCPPfileIFDEF
#include "storage.h"
#include "../esp32-Encrypt-master/src/Cipher.h"
#include <arduino>

#define SearchFile1 "SF"
#define peaceLength (def::AESLength/8 + 2)

namespace sd
{
	Sd2Card card;
	SdFile root;
	const int cs = def::SD_SSPin;
};
Cipher cipher(def::localEncryptionKey);

uint16_t fileName(const char* path)
{
	while(true)
	{
		uint16_t returnValue = random(1, sizeof(uint16_t));
		if(!sd::card.exists(path + (char[3])returnValue))
			return returnValue;
	}
}

void addTOSearchFile(char data[peaceLength])
{
	root.seek();
	while(true)
	{
		for(int i = 0; i < peaceLength; i++)
		{
			
		}
	}
}

bool write(folderEn folder, const char* data, char dataName[(def::AESLength/8)])
{

	uint32_t fileName = fileName((char)folder + '/');
	SdFile root = sd::card.open((char[]) ( (char)folder + '/' + (char[3]) FileName),  FILE_WRITE);
	
	cipher.encrypt(data, def::localEncryptionKey);
	root.write(data);
	root.close();
	root = sd::card.open((char[]) ( (char)folder + '/' + SearchFile), FILE_WRITE);
	cipher.encrypt(dataName, def::localEncryptionKey);
	addTOSearchFile(dataName + (char[3])fileName);

}

char* Read(folderEn folder, uint16_t folderName)
{

}

char* Read(folderEn folder, char fileName[(def::AESLength/8)])
{

}

File Read(folderEn folder, uint16_t folderName)
{

}

File Read(folderEn folder, char fileName[(def::AESLength/8)])
{

}

//DONT FORGET TO DELETE
char* readCryptated()
{
	char returnValue[def::AESLength/8] = new char[(const)def::AESLength/8];
	int x = root.position();
	for(int i = 0; i < def::AESLength/8; i++)
		returnValue[i] = root.read();
	root.seek(root.position);
}

//return 0 if first is highest, 1 if second is highest, 2 if the same
uint16_t compareIntegerLengthOfString(const char* first, const char* second)
{
	for(int i = 0; i < def::AESLength/8; i++)
	{
		if((int)first == (int)second)
			continue;
		if((int)first > (int)second)
			return 0
		else
			return 1
	}
}

uint16_t findFile(folderEn folder, char fileName[(def::AESLength/8)])
{	
	fileName = cipher.encrypt(fileName, def::localEncryptionKey);

	SdFile root = sd::card.open((char[])((char)folder + "/" + SearchFile), FILE_READ);
	uint32_t documentLength = 0;
	for(int i = 0; i < 4; i++)
	{
		documentLength = (uint32_t)root.read();
		documentLength << 8;
	}
	//goto middle of document
	root.seek(def::AESLength/8*documentLength/2);
	char* compare = readCryptated();
	uint32_t latestHigh = 0;
	uint32_t latestLow = 0;
	uint32_t temp = 0;
	
	while(true)
	{
		switch(compareIntegerLengthOfString(fileName, compare) != 2)
		{
			case 0:	delete compare; 
				latestHigh = latestLow; latestLow = temp; 
				root.seek(temp = root.position() + ( (latestHigh - latestLow) / 2 * peaceLength ) ); break;
			case 1:	delete compare; 
				latestLow = latestHigh; latestHigh = temp;
				root.seek(root.position() - (latestHigh - latestLow)/2 * peaceLength); break;
			case 2:	delete compare; goto afterWhile;
			delete compare;
		}
	}
	afterWhile:
	root.seek(root.position() + def::AESLength/8);
	char returnValue = root.read() << 8 + root.read();
	root.close();
	return returnValue
}

//return true if successful
bool setup()
{
	using namespace sd, error;
	if (!sd::card.init(SPI_HALF_SPEED, sd::cs)
	{
		SaveERROR({errorEn = SD_errorInit, 
			functionLocation = &sd::card.init(), isCritical = 3}); 
		return false;
	}
	
	if (!volume.init(card)) 
	{
		SaveERROR({errorEn = SD_volumeError, 
			functionLocation = &volume.init(), isCritical = 3}); 
		return false;
	}
	return true;
}