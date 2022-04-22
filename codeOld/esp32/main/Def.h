	namespace def
	{
		//0 1 0 0 A2 A1 A0 RW
		//NOT SURE IF ADDRESS IS CORRECT
		#define ledHAdress 0b01001110
		#define ledMAddress 0b0100 0000

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

		#define chargeState 2
		#define isCharging 12

		#define B1 4
		#define B2 0
		#define T1 26
		#define T2 27
		#define T3 14
		

		//is button od active low or active high
		#define onState 1
		#define offState 0
		
		#define storage_SS_Pin 5

		#define SSID 
		#define password 
		#define passwordCommunicationPort 25565 
		//port 23 is Telnet, an unecrypted text communication protocol. 
		//I will encrypt the password myself

		#define ntpServer "pool.ntp.org"

		#define localEncryptionKey "QnjvPHIGW4Zi4CNB"//key, 16 bytes/128 bits/16char
		#define AESLength 128
		#define maxSdStringReturnSize 128 //256/8*4

		#define inputTimeoutTime 5000
		#define passwordTimeoutTime 15000
		#define awakeTime 5000

		#define SD_SSPin 18

		#define errorReportStartBlink 3

		enum Pin
		{
			Hl1 = Hl1,
			Hl2 = Hl2,
			Hl3 = Hl3,
			Hl4 = Hl4,

			Hr1 = Hr1,
			Hr2 = Hr2,
			Hr3 = Hr3,
			Hr4 = Hr4,

			Ml1 = Ml1,
			Ml2 = Ml2,
			Ml3 = Ml3,
			Ml4 = Ml4,

			Mr1 = Mr1,
			Mr2 = Mr2,
			Mr3 = Mr3,
			Mr4	= Mr4,

			B1 = B1,
			B2 = B2,

			//Others
			bluetooth = 40,
			wifi = 41
		}
		enum wake
		{
			B1,
			B2,
			bluetooth,
			wifi
		}
	}
	namespace pin = def;