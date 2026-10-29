#include "decls.h"
extern unsigned char DAT_05cd290c[48];

// FUNCTION: SADX 0x0058b860
void FUN_0058b860(int param_1, int param_2)
{
	if (param_2 != 0)
	{
		DAT_05cd290c[param_1] |= 1;
	}
	else
	{
		DAT_05cd290c[param_1] &= 0xfffffffe;
	}
	DAT_05cd290c[param_1] |= 2;
}
