#include "decls.h"
void FUN_00607cc0(int param_1);
extern void FUN_00607cc0(int param_1);
extern int FUN_00607f80();
extern int FUN_00607f90(enum AvaCharEnum param_1);
extern unsigned char DAT_05cd14eb;
extern unsigned char DAT_05cd14ed;
extern unsigned char DAT_05cd14ea;
void FUN_00607c50(struct task *, struct ModeSelPrmType *);
extern struct task *DAT_05edd9c4;

// FUNCTION: SADX 0x00607be0
struct task *SetAdvaCharSelTask(struct ModeSelPrmType *prmp)
{
	void *local_cg;
	struct task *local_8g;

	local_8g = CreateElementalTask(0, 3, char_sel_exec);
	DAT_05edd9c4 = local_8g;
	if (DAT_05edd9c4 != 0)
	{
		local_cg = CAlloc(1, 0x38);
		local_8g->awp = (struct anywk *)local_cg;
		FUN_00607c50(local_8g, prmp);
		local_8g->exec = char_sel_exec;
		local_8g->disp = char_sel_disp;
	}
	return local_8g;
}

// FUNCTION: SADX 0x00607c50
void FUN_00607c50(struct task *param_1, struct ModeSelPrmType *param_2)
{
	struct anywk *local_8;

	local_8 = param_1->awp;
	*(int *)((char *)local_8 + 4) = *(int *)((char *)param_2 + 0);
	*(int *)((char *)local_8 + 8) = *(int *)((char *)param_2 + 4);
	*(float *)((char *)local_8 + 0xc) = 6000.0f;
	*(int *)((char *)local_8 + 0) = 0;
	*(int *)((char *)local_8 + 0x20) = (int)DAT_05cd14eb;
	*(char *)((char *)local_8 + 0x24) = 0;
	*(char *)((char *)local_8 + 0x34) = 0;
	FUN_00607cc0((int)local_8);
}

// FUNCTION: SADX 0x00607cc0
void FUN_00607cc0(int param_1)
{
	*(int *)(param_1 + 0x18) = 0;
	*(float *)(param_1 + 0x28) = 0.0f;
	*(int *)(param_1 + 0x1c) = 0;
}

// STUB: SADX 0x00607ed0
void FUN_00607ed0(struct ModeSelPrmType *prmp)
{
}

// FUNCTION: SADX 0x00607f80
int FUN_00607f80()
{
	return DAT_05cd14ea;
}

// STUB: SADX 0x00607f90
int FUN_00607f90(enum AvaCharEnum chnum)
{
	return (int)0;
}

// FUNCTION: SADX 0x00608000
void FUN_00608000(struct AlrReal *param_1)
{
	FreeAdvaCharMdlTask();
}

// FUNCTION: SADX 0x00608010
void FUN_00608010(struct charsel_char *param_1)
{
	*(unsigned int *)((char *)param_1 + 0x20) = DAT_05cd14ed;
	DAT_05cd14eb = *(unsigned char *)((char *)param_1 + 0x20);
	DAT_05cd14ed = *(unsigned char *)((char *)param_1 + 0x20);
}

// FUNCTION: SADX 0x00608850
void char_sel_disp(struct task *tp)
{
	struct CharSelWk *local_8;

	local_8 = (struct CharSelWk *)tp->awp;
	if (!local_8->BaseCol)
	{
		return;
	}
	ghDefaultBlendingMode();
	ghSetPvrTexBaseColor(local_8->BaseCol);
	DrawSkyBg(local_8->BaseZ + -4.0);
	DrawCharSelBg(local_8);
	FUN_00608f80((struct ModeSelPrmType *)local_8);
	DrawCharSelCursors(local_8);
	DrawCharSelFixedFile(local_8);
}

#pragma optimize("", off)
// STUB: SADX 0x00608f80
void FUN_00608f80(struct ModeSelPrmType *prmp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00609560
void FreeAdvaCharSelTask()
{
	if (DAT_05edd9c4)
	{
		DestroyTask(DAT_05edd9c4);
	}
}

// FUNCTION: SADX 0x00609580
void ChgCharSelNextAdvaMode(enum AdvaModeEnum next)
{
	DAT_05edd9c4->awp->work.ul[2] = (unsigned long)next;
}
