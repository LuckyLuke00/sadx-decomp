#include "decls.h"
void FUN_0061e5b0(struct task *param_1);
extern int DAT_05b42a80;
void charmdl_exec(struct task *tp);
extern struct task *DAT_05edf6e0;
extern float DAT_05edf6c4;
void FUN_0061def0(struct task *param_1);
void FUN_0061e200(struct task *param_1);
void FUN_0061e570(struct task *param_1);

// FUNCTION: SADX 0x0061de70
struct task *FUN_0061de70(void)
{
	struct task *local_8g;
	struct anywk *local_cg;

	local_8g = CreateElementalTask(0, 3, FUN_0061e200);
	DAT_05edf6e0 = local_8g;
	if (DAT_05edf6e0 != 0)
	{
		local_cg = (struct anywk *)CAlloc(1, 0x38);
		local_8g->awp = local_cg;
		FUN_0061def0(local_8g);
		local_8g->exec = FUN_0061e200;
		local_8g->disp = charmdl_disp;
		local_8g->dest = FUN_0061e570;
		DAT_05edf6c4 = 0.0;
	}
	return local_8g;
}

// STUB: SADX 0x0061e0d0
void FUN_0061e0d0(int param_1)
{
}

// STUB: SADX 0x0061e160
void SetCharMdlsLocOut(struct CharMdlWk *wkp)
{
}

// STUB: SADX 0x0061e200
void FUN_0061e200(struct task *tp)
{
}

// STUB: SADX 0x0061e250
void charmdl_exec(struct task *tp)
{
}

// FUNCTION: SADX 0x0061e2d0
void charmdl_disp(struct task *tp)
{
	struct anywk *local_8;

	local_8 = tp->awp;
	___njSetPerspective(0x31c7);
	DAT_05b42a80 = 0x31c7;
	if ((signed char)local_8->work.sb[0x2c] >= 2)
	{
		DispCharMdls((struct CharMdlWk *)local_8);
	}
}

// FUNCTION: SADX 0x0061e570
void FUN_0061e570(struct task *param_1)
{
	struct task *local_8;
	local_8 = (struct task *)param_1->awp;
	if (local_8->ocp != (struct OBJ_CONDITION *)0x0)
	{
		DestroyTask((struct task *)local_8->ocp);
	}
	FUN_0061e5b0(local_8);
}

// STUB: SADX 0x0061e5b0
void FUN_0061e5b0(struct task *task)
{
}

// FUNCTION: SADX 0x0061e690
void FreeAdvaCharMdlTask()
{
	if (DAT_05edf6e0 != 0)
	{
		DestroyTask(DAT_05edf6e0);
	}
	DAT_05edf6e0 = 0;
}

// FUNCTION: SADX 0x0061e6c0
void SetCharMdlSelFlg(unsigned char flg)
{
	((unsigned char *)DAT_05edf6e0->awp)[0x34] = flg;
}
