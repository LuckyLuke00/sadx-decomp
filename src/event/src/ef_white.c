#include "decls.h"
extern struct task *DAT_060cc4ac;
void initEfWhiteTask(struct task *p_task);

// FUNCTION: SADX 0x007d5360
void FUN_007d5360()
{
	if (DAT_060cc4ac)
	{
		FreeTask(DAT_060cc4ac);
		DAT_060cc4ac = 0;
	}
}

// STUB: SADX 0x007d5380
void dispEfWhiteTask(struct task *p_task)
{
}

// STUB: SADX 0x007d53f0
void execEfWhiteTask(struct task *p_task)
{
}

// FUNCTION: SADX 0x007d54a0
void initEfWhiteTask(struct task *p_task)
{
	struct taskwk *var1 = p_task->twp;
	void *var2 = MAlloc(0x10);
	var1->mode = 0;
	*(int *)((char *)var2 + 0xc) = 0xffffff;
	var1->value.ptr = var2;
	p_task->exec = execEfWhiteTask;
	p_task->disp = dispEfWhiteTask;
	p_task->dest = DesertAChildTask;
}

// STUB: SADX 0x007d54e0
void efWhiteOn(int in_int, int out_int)
{
}

// STUB: SADX 0x007d5580
void efWhiteOn2(int in_int, int white_int, int out_int)
{
}
