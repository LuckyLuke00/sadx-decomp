#include "decls.h"

// FUNCTION: SADX 0x00874520
void FUN_00874520(struct task *param_1, struct obj *param_2)
{
	struct taskwk *local_4 = param_1->twp;
	struct obj *local_8 = GetMobileLandObject();
	*local_8 = *param_2;
	local_4->flag &= 0xfeff;
	local_4->counter.ptr = local_8;
	RegisterCollisionEntry(0x80000003, param_1, local_8);
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
