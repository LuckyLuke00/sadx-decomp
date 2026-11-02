#include "decls.h"
extern int DAT_060c5abc;
extern struct NJS_POINT3 DAT_060c5aa0[];
extern int DAT_060c5ac0;
extern int DAT_060c5ac4;

// FUNCTION: SADX 0x0070efd0
void E101R_InitAfterImagePartsPos(struct task *pTask)
{
	DAT_060c5ac0 = 0;
	DAT_060c5ac4 = 0;
}

// STUB: SADX 0x0070f020
void E101R_CalcAfterImageNum(struct E101R_WK *pE101RWk, int flag, int *pNum)
{
}

// STUB: SADX 0x0070f400
void E101R_SetAfterImagePos(struct task *pTask)
{
}

// FUNCTION: SADX 0x0070fb50
void E101R_AfterImageMagni(struct E101R_WK *pE101RWk, struct NJS_ACTION *pAction)
{
	struct task *var1 = CreateElementalTask(2, 4, aiMagniExec);
	if (var1 != 0)
	{
		struct anywk *var2 = (struct anywk *)MAlloc(0x10);
		if (var2 != 0)
		{
			int var3 = DAT_060c5abc;
			var1->awp = var2;
			var2->work.f[2] = 1.0f;
			var2->work.f[3] = 0.5f;
			var2->work.ptr[0] = (void *)((char *)DAT_060c5aa0 + var3 * 0x28);
			var2->work.ptr[1] = (void *)pAction;
		}
		else
		{
			DestroyTask(var1);
		}
	}
}
