#include "../Def.h"
#include <SD.h>

enum folderEn
{
	password = '0',
	SecureNote = '1',
	Address = '2',
	PaymentCard = '3',
	GiftCard = '4',
	BankAccount = '5',
	encryptionKeys = '6'
};

#ifndef fromStorageCPPfileIFDEF

	//return true if successful
	bool setup();
	bool write(folderEn folder, const char* data, char fileName[(def::AESLength/8)]);
	//return NULL if folder not found, 
		//0x01 if multiple folder found(char finder) 
		//0x02 if file to long (return char*)
	//return decrypted
	char* Read(folderEn folder, uint16_t folderName);
	char* Read(folderEn folder, char fileName[(def::AESLength/8)]);
	File Read(folderEn folder, uint16_t folderName);
	File Read(folderEn folder, char fileName[(def::AESLength/8)]);
	
	//return NULL if none found
	uint16_t findFile(folderEn folder, char fileName[(def::AESLength/8)]);
//	bool writePassword(folderEn folder, const char* data);
//	bool writeSecureNote(folderEn folder, const char* data);
//	bool writeAddress(folderEn folder, const char* data);
//	bool writePaymentCard(folderEn folder, const char* data);
//	bool writeBankAccount(folderEn folder, const char* data);
//	bool writeEncryptionKey(folderEn folder, const char* key, const char* IDname);

	//HEAP ALLOCATED DONT FORGET TO DELETE
	//Return null if to long string
//	char* ReadPassword(folderEn folder, const char* data);
//	char* ReadSecureNote(folderEn folder, const char* data);
//	char* ReadAddress(folderEn folder, const char* data);
//	char* ReadPaymentCard(folderEn folder, const char* data);
//	char* ReadBankAccount(folderEn folder, const char* data);
//	char* ReadEncryptionKey(folderEn folder, const char* key, const char* IDname);

//	File ReadPassword(folderEn folder, const char* data);
//	File ReadSecureNote(folderEn folder, const char* data);
//	File ReadAddress(folderEn folder, const char* data);
//	File ReadPaymentCard(folderEn folder, const char* data);
//	File ReadBankAccount(folderEn folder, const char* data);
//	File ReadEncryptionKey(folderEn folder, const char* key, const char* IDname);

#endif