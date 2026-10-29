#include "decls.h"

// STUB: SADX 0x0046e5a0
long GetTotalNumberEmblem(struct SAVE_DATA *psd)
{
	return (long)0;
}

// STUB: SADX 0x0046e5c0
long __fastcall FUN_0046e5c0(long param_1)
{
	return (long)0;
}

// STUB: SADX 0x0046e5e0
void __fastcall FUN_0046e5e0(int param_1)
{
}

// STUB: SADX 0x0046e600
void FUN_0046e600(void *param_1, short param_2)
{
}

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
