/*
	See faq for A LOT of information about following code
*/


#include "../esp32-Encrypt-master/src/Cipher.h"
#include "Def.h"
#include "error.h"
#include "../io/led.h"
#include "../wierless/wifi/wifi.h"

#define ACK (char)6
#define ACK (char)6
#define NAK (char)21
#define EOT (char)4
#define FS (char)28

IS37SML01G1 storage(def::storage_SS_Pin);
Cipher cipher(def::localEncryptionKey);

bool password()
{
	uint16_t crypted = random(0, 0xffff);
	showHorizontal(crypted);

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
				showHorizontal( 
					0b1001 
					  0000 
					  0110 
					  1001);
				delay(150);
			return false;	
			}
	}
	showHorizontal( 
		0b1001 
		  0000 
		  1001 
		  0110
		);
	delay(150);
	return true;
}
String RequestStorageReader(const String& inputData)
{

	if(inputData[3] == NULL)
	{
		String data = cipher.decrypt(storage.ReadContent(&inputData[IDData], inputData[0]), Def::localEncryptionKey);
		const char* encryptionKey = storage.ReadEncryptionKey(inputData[DeviceID]);
		String data = cipher.encrypt(data, encryptionKey);
		delete encryptionKey;
		return data;
	}
	const char* encryptionKey = storage.ReadEncryptionKey(inputData[DeviceID]);
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
					String data = cipher.encrypt(returnData, encryptionKey);
					delete  encryptionKey; 
					return data;
				}
				
				returnData = "";
				break;
			}
		}
		returnData += allData[i];
	}



	return NULL;
}
//return true if succesfull
bool saveData(const String& inputData)
{
	char storageInput[inputData->length()+1];
	inputData->toCharArray(storageInput, sizeof(storageInput));
	storageInput[sizeof(storageInput)] = NULL;
	return storage.WriteNew(&storageInput);
}

//seturn true if succesfull
bool changeData(const String& inputData)
{
	uint32_t pointer;
	//pointer = to the pointer. If it is NULL 
	if((pointer = storage.ReadPointer(inputData[3])) == NULL)
		return false;

	for(int i = 0; i < inputData.length(); i++)
	{
		if(inputData[i] == FS)
		{
			const char* OrStorageData = &inputData[i + 1];
			const char* encryptionKey = storage.ReadEncryptionKey(inputData[0]);
			String EncStorageData = returnData = cipher.decrypt(OrStorageData, encryptionKey);
			delete encryptionKey;
			EncStorageData = cipher.encrypt(EncStorageData, def::localEncryptionKey);
			return storage.ChangeData(EncStorageData, pointer);
		}
	}
}

String possibilityRequest(const String& inputData)
{
	#define DeviceID 0
	#define typeID 1
	#define typeFinderData 2
	#define FollowUpData 3
	#define nameID 4

	const char* encryptionKey = storage.ReadEncryptionKey(inputData[DeviceID]);
	String data = cipher.decrypt(storage.ReadContent(&inputData[IDData], inputData[typeID]), Def::localEncryptionKey);
	data = cipher.encrypt(data, encryptionKey);
	delete encryptionKey;
	return data;
}

uint16_t addDevice(const String& inputData)
{
	const char key[16];
	for(int i = 0; i < 16; i++)
	{
		key[i] = random(sizeof(char));
	}
	key[16] = NULL; // to allow char*
	uint16_t deviceID = storage.WriteEncryptionKey(&key);

	for(int i = 0; i <= sizeof(key); i+=2)
	{
		showHorizontal(((key[i] << 8) + key[i+1]));
		while(digitalRead(def::B1) == def::offState)
		{
			if(digitalRead(def::B2) == def::onState)
			{
				i -= 4;// previuse state
				break;
			}
		}
	}
	String returnValue = deviceID + cipher.encrypt("Hello World!", &key);
	return returnValue;
}

bool deleteKey(uint16_t deviceID)
	return storage.DeleteEncryptionKey(deviceID);

String InputStrManage(const String& inputData)
{
	if(!password(ButtonPin))
		return NAK;

	Switch(inputData[1])
	{
		case 0x00:	
		case 0x01:	
		case 0x02:	
		case 0x03:	
		case 0x04:	
		case 0x05:	
		case 0x06:	
		case 0x07:	return RequestStorageReader(inputStr); break; break;
		
		case 0x08:	saveData(inputStr) ? return ACK : return NAK; break;
		
		case 0x09:	changeData(inputStr) ? return ACK : return NAK; break;
		
		case 0x0A:	return possibilityRequest(inputStr); break;

		case 0x0B:	return AddDevice(ButtonPin, inputStr); break;
		case 0x0C:	deleteKey(inputData[2]) ? return AddDevice(ButtonPin, input) : return NAK; break;
		case 0x0D:	deleteKey(inputData[0]) ? return ACK : return NAK; break;
	}

}

enum passWordPoss
{
	neverMinde,
	possibility,
	note,
	adress,
	PaymentCard,
	Adress,
	PaymentCard,
	GiftCard,
	BankAccount
}

void bloutoothPasword()
{

}

WiFiServer server(def::passwordCommunicationPort);
WiFiClient client;


void wifiPassword()
{
	if(!bool wifiConnect())
		errorReport(couldntConnectToWifi); return;

	server.begin();
	
	long waitTime = def::passwordTimeoutTime + millis();
	
	while(waitTime < millis())
	{
		client = server.available();
		if(client)
			break;
	}

	String inputStr = "";
	client.print((char)6);
	waitTime = def::passwordTimeoutTime + millis();
	while(waitTime < millis())
	{
		if(client.available() != 0)
		{
			char x = client.read();
			if(x == (char)3)
				break;
			else
				inputStr += x;
		}	

	}
	client.write(InputStrManage(inputStr));
}