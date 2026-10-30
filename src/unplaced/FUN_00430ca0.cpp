#include "decls.h"
extern int DAT_05ad9ad0[16];

// FUNCTION: SADX 0x00430ca0
void FUN_00430ca0(void)
{
	DAT_05ad9ad0[0] = 0;
	DAT_05ad9ad0[1] = 0;
	DAT_05ad9ad0[2] = 0;
	DAT_05ad9ad0[3] = 0;
	DAT_05ad9ad0[4] = 0;
	DAT_05ad9ad0[5] = 0;
	DAT_05ad9ad0[6] = 0;
	DAT_05ad9ad0[7] = 0;
	DAT_05ad9ad0[8] = 0;
	DAT_05ad9ad0[9] = 0;
	DAT_05ad9ad0[10] = 0;
	DAT_05ad9ad0[11] = 0;
	DAT_05ad9ad0[12] = 0;
	DAT_05ad9ad0[13] = 0;
	DAT_05ad9ad0[14] = 0;
	DAT_05ad9ad0[15] = 0;
}

// STUB: SADX 0x00430d00
void FUN_00430d00(void)
{
}

// FUNCTION: SADX 0x00430d20
void FUN_00430d20(int param_1)
{
	int *var1;
	int var2;
	var1 = &DAT_05ad9ad0[0];
	do
	{
		if (*var1 == param_1)
		{
			return;
		}
		var1++;
	} while (var1 != &DAT_05ad9ad0[0x10]);
	var2 = 0;
	do
	{
		if (DAT_05ad9ad0[var2] == 0)
		{
			DAT_05ad9ad0[var2] = param_1;
			return;
		}
		var2++;
	} while (var2 != 0x10);
}
