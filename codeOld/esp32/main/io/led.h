#pragma once

#ifndef blinkTime
	#define blinkTime 50 //MS
#endif

#ifndef fromledCPP
void ledSetup();
void showHorizontal(const uint16_t data);
void showVertical(const uint16_t data);
void blink();
void blink(uint16_t delay, uint16_t times);
#endif