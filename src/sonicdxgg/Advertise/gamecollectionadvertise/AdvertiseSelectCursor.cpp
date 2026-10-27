#include "decls.h"
extern int DAT_00a57ba4;
void FUN_00907d40(void);
int FUN_007f2180();
int FUN_007f2190();

// FUNCTION: SADX 0x00906d90
void __fastcall FUN_00906d90(void *param_1)
{
	*(int *)param_1 = (int)&DAT_00a57ba4;
	FUN_00907d40();
}

// FUNCTION: SADX 0x00906db0
int FUN_00906db0()
{
	int var1;
	int var2;
	int var3;
	int var4;

	var1 = FUN_007f2180();
	if (var1 <= 0x64)
	{
		var3 = var1 / 20;
	}
	else
	{
		var3 = (var1 - 100) / 10 + 5;
	}
	var2 = FUN_007f2190();
	var4 = var2 / 20;
	var3 = var3 + var4;
	if (var1 == 0x82 && var2 == 0x3c)
	{
		var3 = var3 + 1;
	}
	if (var3 > 0xc)
	{
		return 0xc;
	}
	return var3;
}
