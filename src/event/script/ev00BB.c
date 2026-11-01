#include "decls.h"
void FUN_007d21b0(...);

// STUB: SADX 0x0074b740
void destDelObjTask(struct task *p_task)
{
}

// FUNCTION: SADX 0x0074b7a0
void execDelObjTask(struct task *p_task)
{
	struct taskwk *local_8 = p_task->twp;
	switch (local_8->mode)
	{
	case 0:
		local_8->mode = 1;
		break;
	case 1:
		local_8->counter.l = local_8->counter.l + 1;
		if (local_8->counter.l > local_8->wtimer)
		{
			local_8->mode = 2;
		}
		{
			struct anywk *local_c = (struct anywk *)local_8->timer.ptr;
			local_c->work.f[8] = local_c->work.f[8] + local_8->scl.x;
			local_c->work.f[9] = local_c->work.f[9] + local_8->scl.y;
			local_c->work.f[10] = local_c->work.f[10] + local_8->scl.z;
		}
		break;
	case 2:
		FreeTask(p_task);
		break;
	}
}

// FUNCTION: SADX 0x0074b7f0
void initDelObjTask(struct task *p_task)
{
	p_task->exec = execDelObjTask;
	p_task->disp = (void (__cdecl *)(struct task *))FUN_007d21b0;
	p_task->dest = destDelObjTask;
}
