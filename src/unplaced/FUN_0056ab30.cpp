#include "decls.h"

// FUNCTION: SADX 0x0056ab30
void FUN_0056ab30()
{
	ADX_Close();
	ADXTaskInit();
	dsInitInt(2, 1);
	EV_PcNpcEnd();
}

// FUNCTION: SADX 0x0056ab50
int FUN_0056ab50(int *param_1)
{
	if (*(int *)(param_1 + 1) != 0)
	{
		return FUN_005a5190(*(int *)(param_1 + 1));
	}
	else
	{
		return 4;
	}
}
