#include "decls.h"
static void execShadowTask(struct task *p_task);
static void dispShadowTask(struct task *p_task);
extern struct task *DAT_060cba88[16];

// FUNCTION: SADX 0x0077e8b0
void shadowOff(signed char num)
{
	if (DAT_060cba88[num] != 0)
	{
		DestroyTask(DAT_060cba88[num]);
		DAT_060cba88[num] = 0;
	}
}

#pragma optimize("", off)
// STUB: SADX 0x0077e8e0
static void dispShadowTask(struct task *p_task)
{
}
#pragma optimize("", on)

#pragma optimize("", off)
// STUB: SADX 0x0077e9a0
static void execShadowTask(struct task *p_task)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x0077ea20
void initShadowTask(struct task *p_task)
{
	struct taskwk *var1 = p_task->twp;

	var1->value.ptr = MAlloc(0x10);
	p_task->exec = execShadowTask;
	p_task->disp = dispShadowTask;
	p_task->dest = FUN_007d6940;
}

// STUB: SADX 0x0077ea50
void shadowOn(signed char num, float pos_x, float pos_y, float pos_z, int bigInt, int smallInt, float scaleMax)
{
}
