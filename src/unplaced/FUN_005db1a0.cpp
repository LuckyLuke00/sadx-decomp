#include "decls.h"
extern short DAT_05b9d724;
extern short DAT_05b9d744;

// FUNCTION: SADX 0x005db1a0
long FUN_005db1a0()
{
	long local_cg;
	long local_8g;

	local_8g = GetPlayerNumber();
	switch (local_8g)
	{
	case 0:
		local_cg = 0;
		break;
	case 2:
		local_cg = 1;
		break;
	case 3:
		local_cg = 2;
		break;
	case 5:
		local_cg = 3;
		break;
	case 6:
		local_cg = 4;
		break;
	case 7:
		local_cg = 5;
		break;
	default:
		local_cg = 6;
		break;
	}
	return local_cg;
}

// FUNCTION: SADX 0x005db230
unsigned char FUN_005db230(void)
{
	int local_8g;
	unsigned char local_9;

	local_8g = ((int)DAT_05b9d724 << 8) | (int)DAT_05b9d744;
	local_9 = (unsigned char)(local_8g & 0xff);
	if (local_9 <= 0 || local_9 >= 6)
		local_9 = 0;
	return local_9;
}
