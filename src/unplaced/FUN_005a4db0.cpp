#include "decls.h"
void FUN_005a4e10(void *param_1);
extern void *DAT_05eda1d8;

// FUNCTION: SADX 0x005a4db0
void FUN_005a4db0(void *param_1)
{
	void *local_8;
	local_8 = DAT_05eda1d8;
	FUN_005a4e10(param_1);
	if (local_8 != DAT_05eda1d8)
	{
		FUN_005a4c90((int)param_1);
		FUN_005a4e00();
	}
	else
	{
		FUN_005a4c90((int)param_1);
	}
}
