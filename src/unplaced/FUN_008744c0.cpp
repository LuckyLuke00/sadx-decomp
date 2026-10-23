#include "decls.h"

// STUB: SADX 0x00874520
void FUN_00874520(struct task *param_1, struct obj *param_2)
{
}

// STUB: SADX 0x008745c0
void FUN_008745c0(void)
{
}

// FUNCTION: SADX 0x00874640
void __fastcall FUN_00874640(int *param_1)
{
	int iVar2;
	iVar2 = *param_1;
	while (iVar2 != 0)
	{
		*(int *)(iVar2 + 0x20) &= 0xfffffffe;
		param_1 = (int *)((char *)param_1 + 4);
		iVar2 = *param_1;
	}
}
