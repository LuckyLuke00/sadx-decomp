#include "decls.h"
void FUN_007d21b0(void *param_1);

// STUB: SADX 0x0074b740
void destDelObjTask(struct task *p_task)
{
}

// STUB: SADX 0x0074b7a0
void execDelObjTask(struct task *p_task)
{
}

// FUNCTION: SADX 0x0074b7f0
void initDelObjTask(struct task *p_task)
{
	p_task->exec = execDelObjTask;
	p_task->disp = (void (__cdecl *)(struct task *))FUN_007d21b0;
	p_task->dest = destDelObjTask;
}
