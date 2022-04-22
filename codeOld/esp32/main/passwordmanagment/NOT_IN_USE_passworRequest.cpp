//String passwordRequest(const uint8_t& LEDPin, const int8_t& ButtonPin, const String& inputData);
//String possibilityRequest(const uint8_t& LEDPin, const int8_t& ButtonPin, const String& inputData);
//String noteRequest(const uint8_t& LEDPin, const int8_t& ButtonPin, const String& inputData);
//String AdressRequest(const uint8_t& LEDPin, const int8_t& ButtonPin, const String& inputData);
//String PaymentCardRequest(const uint8_t& LEDPin, const int8_t& ButtonPin, const String& inputData);
//String GiftCardRequest(const uint8_t& LEDPin, const int8_t& ButtonPin, const String& inputData);
//String BankAccountRequest(const uint8_t& LEDPin, const int8_t& ButtonPin, const String& inputData);





#include "IS37SML01G1/IS37SML01G1.h"
#include "Def.h"
#include "../esp32-Encrypt-master/src/Cipher.h"
IS37SML01G1 storage(def::storage_SS_Pin);
Cipher cipher(def::localEncryptionKey);

#define ACK (char)6
#define NAK (char)21
#define EOT (char)4

/*
	//return String array part where the wanted data starts. Return 0xffff if not found
	uint16_t findData(const String&, DataPart part)
	{
		switch (part)
		{
			case typeIdf: return NULL; break;
			case DeviceID: return 2; break;
			case nameID: return 3; break;

		}
	}
*/

bool password(uint8_t& ButtonPin, const uint8_t& LEDPi)
{
	uint16_t crypted = random(0, 0xffff);
	show(ButtonPin, crypted);

	uint16_t x[3];
	x[0] = crypted & 0xf000;
	x[1] = crypted & 0x0f00;
	x[2] = crypted & 0x00f0;
	x[3] = crypted & 0x000f;
	
	x[0] >> 12;
	x[1] >> 8; 
	x[2] >> 4;
	
	~x[0]
	x[1] = x[1]^x[2];
	x[3] = x[3]&x[0];

	uint8_t filter = 0x0001;
	for(int i = 0; i < 4; i++)
	{
		int input;
		for(int j = 0; j < 4; j++)
		{
			while(true)
			{
				if(digitalRead(buttonPin[0]))
					//		0b0123456789abcdef
					input = 0b0000000000000001; break;
				if(digitalRead(buttonPin[1]))
					input = 0b0000000000000010; break;
				if(digitalRead(buttonPin[2]))
					input = 0b0000000000000100; break;
				if(digitalRead(buttonPin[3]))
					input = 0b0000000000001000; break;
			}
		}
		if(input != x[i])
			{
				show(LEDPin, 
					0b1001 
					  0000 
					  0110 
					  1001);
				delay(150);
			return false;	
			}
	}
	show(LEDPin, 
		0b1001 
		  0000 
		  1001 
		  0110
		);
	delay(150);
	return true;
}


String neverMindeVoid(const uint8_t& LEDPin, const int8_t& ButtonPin)
	return NAK;

String passwordRequest(const uint8_t& LEDPin, const int8_t& ButtonPin, const String& inputData)
{
	#define typeID 0
	#define DeviceID 1
	#define nameID 2
	if(!password(buttonPin, ledPin))
		return NAK;


	String data = cipher.decrypt(storage.ReadContent(&inputData[nameID], 0b0000 0000), Def::localEncryptionKey);
	uint32_t encryptionKey[4] = storage.ReadEncryptionKey(inputData[DeviceID]);
	return cipher.encrypt(data, &encryptionKey[0]);
}

String possibilityRequest(const uint8_t& LEDPin, const int8_t& ButtonPin, const String& inputData)
{
	#define typeID 0
	#define DeviceID 1
	#define typeID 2
	#define nameID 3
	if(!password(buttonPin, ledPin))
		return NAK;
	uint32_t encryptionKey[4] = storage.ReadEncryptionKey(inputData[DeviceID]);
	String data = storage.ReadContent(String[nameID], inputData[typeID]);
	return cipher.encrypt(data, &encryptionKey[0]);

}

String noteRequest(const uint8_t& LEDPin, const int8_t& ButtonPin, const String& inputData)
{
	#define typeID 0
	#define DeviceID 1
	#define nameID 2
	if(!password(buttonPin, ledPin))
		return NAK;


	String data = cipher.decrypt(storage.ReadContent(&inputData[nameID], 0b0000 0001), Def::localEncryptionKey);
	uint32_t encryptionKey[4] = storage.ReadEncryptionKey(inputData[DeviceID]);
	return cipher.encrypt(data, &encryptionKey[0]);

}

//DO NOT WORK
String allDataCompareAlgorithm(uint8_t type, const String& inputData, uint8_t IDData, uint8_t IDType)
{
	uint32_t encryptionKey[4] = storage.ReadEncryptionKey(inputData[DeviceID]);
	String allData = storage.ReadContent(NULL, type, inputData[IDType]);
	String returnData = "";
	for(int i = 0; i < 0xffffffff; i++)
	{
		if(AllData == NULL)
		{
			returnData = cipher.decrypt(returnData, Def::localEncryptionKey);
			for(int j = 0; j < sizeof(returnData)+3; j++)
			{
				if(returnData[j] == inputData[IDData + j])
					continue;
				else if(inputData[IDData + j] == NULL ||inputData[IDData + j] == EOT)
				{
					return cipher.encrypt(returnData, &encryptionKey[0]);
				}
				
				returnData = "";
				break;
			}
		}
		returnData += allData[i];
	}



	return NULL;
}

String name(const uint8_t& LEDPin, const int8_t& ButtonPin, const String& inputData)
{
	if(!password(buttonPin, ledPin))
	return NAK;

	if(inputData[3] == NULL)
	{
		String data = cipher.decrypt(storage.ReadContent(&inputData[IDData], inputData[0]), Def::localEncryptionKey);
		uint32_t encryptionKey[4] = storage.ReadEncryptionKey(inputData[DeviceID]);
		return cipher.encrypt(data, &encryptionKey[0]);
	}
	uint32_t encryptionKey[4] = storage.ReadEncryptionKey(inputData[DeviceID]);
	String allData = storage.ReadContent(NULL, type, inputData[IDType]);
	String returnData = "";
	for(int i = 0; i < 0xffffffff; i++)
	{
		if(AllData == NULL)
		{
			returnData = cipher.decrypt(returnData, Def::localEncryptionKey);
			for(int j = 0; j < sizeof(returnData)+3; j++)
			{
				if(returnData[j] == inputData[IDData + j])
					continue;
				else if(inputData[IDData + j] == NULL ||inputData[IDData + j] == EOT)
				{
					return cipher.encrypt(returnData, &encryptionKey[0]);
				}
				
				returnData = "";
				break;
			}
		}
		returnData += allData[i];
	}



	return NULL;
}


String adressRequest(const uint8_t& LEDPin, const int8_t& ButtonPin, const String& inputData)
{
	#define typeID 0
	#define DeviceID 1
	#define IDType 3
	#define IDData 4
	enum IDTypeEn
	{
		Name,		//0
		MiddleName,	//1
		LastName, 	//2
		Phone, 		//3
		MobilePhone,//4
		WorkPhone,	//5
		BirthDay,	//6
		EmailAdress,//7
		Adress,		//8
		PostalCode,	//9
		Company,	//10

	}
	if(!password(buttonPin, ledPin))
		return NAK;

	if((IDTypeEN)inputData[IDType] == Name)
	{
		String data = cipher.decrypt(storage.ReadContent(&inputData[IDData], 0b0000 0010), Def::localEncryptionKey);
		uint32_t encryptionKey[4] = storage.ReadEncryptionKey(inputData[DeviceID]);
		return cipher.encrypt(data, &encryptionKey[0]);
	}
	return allDataCompareAlgorithm(0b0000 0010, inputData, IDData, IDType);

}

String PaymentCardRequest(const uint8_t& LEDPin, const int8_t& ButtonPin, const String& inputData)
{
	#define typeID 0
	#define DeviceID 1
	#define IDType 3
	#define IDData 4
	enum IDTypeEn
	{
		Name, 			//1
		ExpirationDate,	//2
		SecurityCode,	//3
		CardNumber		//4 
	}
	if(!password(buttonPin, ledPin))
		return NAK;

	if((IDTypeEn)inputData[IDType] == Name)
	{
		String data = cipher.decrypt(storage.ReadContent(&inputData[IDData], 0b0000 0011), Def::localEncryptionKey);
		uint32_t encryptionKey[4] = storage.ReadEncryptionKey(inputData[DeviceID]);
		return cipher.encrypt(data, &encryptionKey[0]);
	}
	return allDataCompareAlgorithm(0b0000 0011, inputData, IDData, IDType);
}

String GiftCardRequest(const uint8_t& LEDPin, const int8_t& ButtonPin, const String& inputData)
{
	#define typeID 0
	#define DeviceID 1
	#define IDType 3
	#define IDData 4
	if(!password(buttonPin, ledPin))
		return NAK;
	return allDataCompareAlgorithm(0b0000 0100, inputData, IDData, IDType);
}

String BankAccountRequest(const uint8_t& LEDPin, const int8_t& ButtonPin, const String& inputData)
{
	#define typeID 0
	#define DeviceID 1
	#define nameID 2
	if(!password(buttonPin, ledPin))
		return NAK;
}