static Vector<void(*)()> B1SelectPin = 
	{ 
		home, 
		clock::showCalendar, 
		clock::showTemp, 
		wifi::wifi, 
		bluetooth::bluetooth,
		error::errorUI
	};

// organised with t1 as most significant bit and t3 as least, 
//the counting binary (all low do not exist)
void(*B2TouchMacro()[7]) = 
	{ 
	};

static uint8_t touchLowValue = 30;