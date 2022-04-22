#pragma once

#include "../../esp32-Encrypt-master/src/Cipher.h"
#include "../../IS37SML01G1/IS37SML01G1.h"

extern IS37SML01G1 storage;
extern Cipher cipher;

bool password();
bool saveData(const String& inputData);
bool changeData(const String& inputData);
String possibilityRequest(const String& inputData);
uint16_t addDevice(const String& inputData);
bool deleteKey(uint16_t deviceID);
String InputStrManage(const String& inputData);
enum passWordPoss;
void bloutoothPasword();
void wifiPassword();
