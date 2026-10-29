#include "decls.h"
extern struct childtaskset cts_dmg_body_a;
extern struct childtaskset cts_dmg_body_b;
extern struct childtaskset cts_dmg_body_c;
void FUN_00422560(int param_1);

// FUNCTION: SADX 0x00823570
void dispTank(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	FUN_00422560(3);
	SetObjectTexture();
	njPushMatrix(NULL);
	njTranslateV(NULL, &var1->pos);
	if (*(int *)((char *)var1 + 0x1c) != 0)
	{
		njRotateZ(NULL, (unsigned short)*(short *)((char *)var1 + 0x1c));
	}
	if (*(int *)((char *)var1 + 0x14) != 0)
	{
		njRotateX(NULL, (unsigned short)*(short *)((char *)var1 + 0x14));
	}
	if (*(int *)((char *)var1 + 0x18) != 0)
	{
		njRotateY(NULL, (unsigned short)*(short *)((char *)var1 + 0x18));
	}
	njScaleV(NULL, &var1->scl);
	___dsDrawModel((struct NJS_MODEL *)*(int **)((char *)*(int **)((char *)var1 + 8) + 4));
	njPopMatrix(1);
	npSetZCompare();
}

// FUNCTION: SADX 0x00823740
void exitTank(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (FUN_004c39c0(tp))
	{
		return;
	}
	if (var1->counter.ptr != 0)
	{
		WithdrawCollisionEntry(tp, (struct obj *)var1->counter.ptr);
		ReleaseMobileLandObject((struct obj *)var1->counter.ptr);
	}
}

// FUNCTION: SADX 0x008239e0
void __fastcall FUN_008239e0(struct task *param_1)
{
	if ((param_1->twp->btimer & 1) != 0)
	{
		CreateChildrenTask(&cts_dmg_body_a, param_1);
		return;
	}
	if ((param_1->twp->btimer & 2) != 0)
	{
		CreateChildrenTask(&cts_dmg_body_b, param_1);
		return;
	}
	CreateChildrenTask(&cts_dmg_body_c, param_1);
}
