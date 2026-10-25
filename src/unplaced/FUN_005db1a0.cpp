#include "decls.h"

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

// STUB: SADX 0x005db230
unsigned char FUN_005db230(void)
{
	return (unsigned char)0;
}
