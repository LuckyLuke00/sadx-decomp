#include "decls.h"

// FUNCTION: SADX 0x0046e620
void __fastcall FUN_0046e620(int param_1)
{
	short sVar1 = *(short *)(param_1 + 0xa);
	short sVar2 = *(short *)(param_1 + 0xc);
	if (sVar1 < sVar2)
	{
		sVar1++;
		*(short *)(param_1 + 0xa) = sVar1;
		return;
	}
	if (sVar1 > sVar2)
	{
		sVar1--;
		*(short *)(param_1 + 0xa) = sVar1;
	}
}
