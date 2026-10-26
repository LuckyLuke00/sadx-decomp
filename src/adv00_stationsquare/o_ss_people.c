#include "decls.h"
extern int *DAT_05b3e0d8;
extern short DAT_05ccde90;
extern "C" int rand(void);
extern unsigned char DAT_05bafce4;

// STUB: SADX 0x006848e0
long ssp_talk(struct task *task_p)
{
	return (long)0;
}

// STUB: SADX 0x00685230
void ssp_exec_eveidle(struct task *task_p)
{
}

// FUNCTION: SADX 0x00685360
void ObjectSSPeopleWait(struct task *task_p)
{
	struct taskwk *var1 = task_p->twp;
	if (var1->scl.z < (float)*DAT_05b3e0d8)
	{
		int var2 = rand();
		float var3 = (float)var2 * 3.0517578125e-05;
		int var4 = (int)(var3 * 3.0 + 0.0);
		if (ssp_new(task_p, (enum sspmotion_type)var4) != 0)
		{
			struct anywk *var5 = task_p->awp;
			CCL_Init(task_p, (struct CCL_INFO *)(*(int *)((char *)var5 + 0x14) + 0x44), 1, 4);
			*(void (__cdecl **)(struct task *))((char *)var5 + 0x28) = (void (__cdecl *)(struct task *))ssp_control_wait;
			task_p->dest = mrp_end;
			return;
		}
	}
	if (DAT_05ccde90 != 0)
	{
		ssp_debug_draw(task_p);
	}
}

// FUNCTION: SADX 0x00685610
void ssp_walk_man_eveidle(struct task *task_p)
{
	if (EV_CheckCansel() == 0)
	{
		FreeTaskC(task_p);
		ssp_walk_man_1st(task_p);
		task_p->exec = ssp_walk_man;
	}
	else if (DAT_05bafce4 != 0)
	{
		LoopTaskC(task_p);
	}
}

// FUNCTION: SADX 0x00685650
void ssp_walk_man(struct task *task_p)
{
	if (EV_CheckCansel())
	{
		task_p->exec = ssp_walk_man_eveidle;
		return;
	}
	LoopTaskC(task_p);
}
