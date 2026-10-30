#include "decls.h"
#include "../advertise.h"

// GLOBAL: SADX 0x05ad9668
SOCControllerAll* DAT_05ad9668;

// STUB: SADX 0x00424970
SOCInput::SOCInput()
{
}

// FUNCTION: SADX 0x00424a70
int __fastcall FUN_00424a70(void *param_1)
{
	return *(int *)((char *)param_1 + 0x48);
}

// FUNCTION: SADX 0x00424a80
char __fastcall FUN_00424a80(void *param_1)
{
	return (*(int *)((char *)param_1 + 0x48) == 5) + 5;
}

// FUNCTION: SADX 0x00424b40
SOCController* SOCInput::FUN_00424b40()
{
	if (local_0 >= 0 && local_0 < 8 && local_4[local_0] != 0)
	{
		return local_4[local_0];
	}
	if (DAT_05ad9668 == 0)
	{
		DAT_05ad9668 = new SOCControllerAll;
	}
	return DAT_05ad9668;
}

// STUB: SADX 0x00424b90
void __fastcall FUN_00424b90(void *param_1, int param_2)
{
}
