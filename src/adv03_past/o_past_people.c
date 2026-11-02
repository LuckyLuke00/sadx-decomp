#include "decls.h"
extern unsigned char DAT_05bafce4;

// STUB: SADX 0x006be240
long pastp_control_walk(struct task *task_p)
{
	return (long)0;
}

// STUB: SADX 0x006be6e0
void pastp_walk_end(struct task *task_p)
{
}

// STUB: SADX 0x006becf0
void pastp_exec_eveidle(struct task *task_p)
{
}

// FUNCTION: SADX 0x006bee20
void ObjectPASTPeopleWait(struct task *task_p)
{
	struct taskwk *var1 = task_p->twp;
	if (var1->scl.z < (float)*DAT_05b3e0d8)
	{
		if (pastp_new(task_p, (enum pastpmotion_type)0) != 0)
		{
			struct anywk *var2 = task_p->awp;
			CCL_Init(task_p, (struct CCL_INFO *)(*(int *)((char *)var2 + 0x14) + 0x2c), 1, 4);
			*(void (__cdecl **)(struct task *))((char *)var2 + 0x28) = (void (__cdecl *)(struct task *))pastp_control_wait;
			task_p->dest = mrp_end;
			return;
		}
	}
	if (DAT_05ccde90 != 0)
	{
		pastp_debug_draw(task_p);
	}
}

// FUNCTION: SADX 0x006bf090
void pastp_walk_man_eveidle(struct task *task_p)
{
	if (EV_CheckCansel() == 0)
	{
		pastp_walk_man_1st(task_p);
		task_p->exec = pastp_walk_man;
	}
	else if (DAT_05bafce4 != 0)
	{
		LoopTaskC(task_p);
	}
}

// FUNCTION: SADX 0x006bf0c0
void pastp_walk_man(struct task *task_p)
{
	if (EV_CheckCansel())
	{
		task_p->exec = pastp_walk_man_eveidle;
		return;
	}
	LoopTaskC(task_p);
}
