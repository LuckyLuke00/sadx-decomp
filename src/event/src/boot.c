#include "decls.h"
void FUN_007d6940(struct task *param_1);
extern struct task *DAT_060cc95c;

// STUB: SADX 0x007d8d50
void sandStorm(int frame, int alpha)
{
}

// FUNCTION: SADX 0x007d8d80
void deleteBoot()
{
	if (DAT_060cc95c)
	{
		FreeTask(DAT_060cc95c);
		DAT_060cc95c = 0;
	}
}

// STUB: SADX 0x007d8da0
void FUN_007d8da0(void)
{
}

// STUB: SADX 0x007d8fa0
void dispBootTask(struct task *p_task)
{
}

// STUB: SADX 0x007d9010
void execBootTask(struct task *p_task)
{
}

// FUNCTION: SADX 0x007d90f0
void initBootTask(struct task *p_task)
{
	p_task->exec = execBootTask;
	p_task->disp = dispBootTask;
	p_task->dest = FUN_007d6940;
}

// STUB: SADX 0x007d9110
void createBoot(int wait_frame, int sstorm_frame, int poweron_frame, int adjust_frame)
{
}
