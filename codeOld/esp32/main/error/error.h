#pragma once

enum errorEn
{
	noError,
	RTCNotFound,
	couldntOptainDateTime,
	couldntConnectToWifi,
	couldntChangeStorageData,
	SD_errorInit,
	SD_volumeError,
	ErrorNotConclusive
};

class error : errorAdvanced
{
	errorEn simpError
};

class errorAdvanced
{
	void* funcTionLocation;
	void* dataLocation;
	dataTypeEn dataType;
	uint8_t isCritical = 0;
	/*0-5, 
	0 = dosent mather, 
	3 = function dosent work,
	5 = watch barely or donot work
	*/
};

#ifndef fromCPPfileIFDEF
	String enumToString(errorEn error);
	void SaveERROR(errorEn error);
	String reportErrorStr();
	void reportErrorLed();
	void reportErrorLed(errorEn error);
	void cleanErrorData();
	void removeErrorData(errorEn error);
	void errorUI();
#endif