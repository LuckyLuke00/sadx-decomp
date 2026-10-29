#include "decls.h"
void FUN_007d6940(struct task *param_1);

// FUNCTION: SADX 0x007d1cf0
void FUN_007d1cf0(int param_1)
{
	if (DAT_060cbfdc[param_1] != 0)
	{
		FreeTask((struct task *)DAT_060cbfdc[param_1]);
		DAT_060cbfdc[param_1] = 0;
	}
}

// STUB: SADX 0x007d1d20
void dispModelTask(struct task *p_task)
{
}

// STUB: SADX 0x007d1df0
void dispModelTaskEC(struct task *p_task)
{
}

// FUNCTION: SADX 0x007d1ff0
void FUN_007d1ff0(struct task *param_1)
{
	param_1->exec = execModelTask;
	param_1->disp = dispModelTask;
	param_1->dest = FUN_007d6940;
}

// FUNCTION: SADX 0x007d2010
void initModelTaskEC(struct task *p_task)
{
	p_task->exec = execModelTaskEC;
	p_task->disp = dispModelTaskEC;
	p_task->dest = FUN_007d6940;
}

// STUB: SADX 0x007d20f0
void FUN_007d20f0(float param_1, float param_2, float param_3, long param_4, long param_5, long param_6, float param_7, float param_8, float param_9, void *param_10, void *param_11, int param_12)
{
}
