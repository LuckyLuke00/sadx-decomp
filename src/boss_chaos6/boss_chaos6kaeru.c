#include "decls.h"

// FUNCTION: SADX 0x006fa6d0
void FUN_006fa6d0(int param_1)
{
	int iVar1;

	iVar1 = *(int *)(param_1 + 0x20);
	*(short *)(iVar1 + 0x10) = *(short *)(iVar1 + 0x10) - 1;
	if (*(short *)(iVar1 + 0x10) <= 0)
	{
		*(int *)(iVar1 + 0x18) = *(int *)(iVar1 + 0x18) + 0xb6;
		*(short *)(iVar1 + 0x10) = 3;
	}
}

// STUB: SADX 0x006faab0
void setCatchingC6Kaeru(struct task *tp)
{
}
