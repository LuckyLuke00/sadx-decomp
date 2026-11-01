#include "decls.h"
extern long DAT_060cd250[4];

// FUNCTION: SADX 0x007e4b90
void CartDataSetSubTotalTime(signed char lap, long time)
{
	DAT_060cd250[lap] = time;
}

// FUNCTION: SADX 0x007e4bb0
void CartDataSetLapTime(signed char lap, long time)
{
	DAT_060cd250[lap + 3] = time;
}

// FUNCTION: SADX 0x007e4c10
int FUN_007e4c10(struct BEST3_CART *param_1)
{
	char local_18[16];
	int var1;
	int var2;
	int var3;
	int var4;

	MirenSaveDataLoadCartData((struct BEST3_CART *)local_18);
	var1 = *(char *)local_18;
	if (var1 < 0)
	{
		var1 = 0;
	}
	else if (var1 >= 0x64)
	{
		var1 = 0x63;
	}
	var2 = *(char *)(local_18 + 1);
	if (var2 < 0)
	{
		var2 = 0;
	}
	else if (var2 >= 0x3c)
	{
		var2 = 0x3b;
	}
	var3 = *(char *)(local_18 + 2);
	if (var3 < 0)
	{
		var3 = 0;
	}
	else if (var3 >= 0x64)
	{
		var3 = 0x63;
	}
	var4 = var1 * 16 - var1;
	return (var2 + var4 * 4) * 100 + var3;
}
