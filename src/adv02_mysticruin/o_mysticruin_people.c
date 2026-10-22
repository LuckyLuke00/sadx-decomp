#include "decls.h"
extern short DAT_05b9d744;
extern unsigned char DAT_05bafce4;

// FUNCTION: SADX 0x006af220
void mrp_walk_man_end(struct task *task_p)
{
	Free(task_p->awp->work.ptr[0]);
}

// STUB: SADX 0x006af850
long mrp_damage(struct task *task_p)
{
	return (long)0;
}

// FUNCTION: SADX 0x006afbb0
void mrp_end(struct task *task_p)
{
	Free(*(void **)((char *)task_p->awp + 0x24));
	InputHookDelete(task_p);
}

// FUNCTION: SADX 0x006afbd0
void mrp_walk_end(struct task *task_p)
{
	Free(*(void **)((char *)task_p->awp + 0x2c));
	Free(*(void **)((char *)task_p->awp + 0x24));
	InputHookDelete(task_p);
}

// STUB: SADX 0x006b01c0
void mrp_exec_eveidle(struct task *task_p)
{
}

// STUB: SADX 0x006b0410
void mrp_walk_man_1st(struct task *task_p)
{
}

// FUNCTION: SADX 0x006b0480
void mrp_walk_man_eveidle(struct task *task_p)
{
	if (EV_CheckCansel() == 0)
	{
		FreeTaskC(task_p);
		mrp_walk_man_1st(task_p);
		task_p->exec = mrp_walk_man;
	}
	else
	{
		if (DAT_05bafce4 != 0)
		{
			LoopTaskC(task_p);
		}
	}
}

// FUNCTION: SADX 0x006b04c0
void mrp_walk_man(struct task *task_p)
{
	if (EV_CheckCansel())
	{
		task_p->exec = mrp_walk_man_eveidle;
		return;
	}
	LoopTaskC(task_p);
}

// FUNCTION: SADX 0x006b05c0
void mrp_actman(struct task *task_p)
{
	struct anywk *var1;
	int var2;

	var1 = task_p->awp;
	if (var1->work.ul[0] == 0)
	{
		var2 = (DAT_05b9d744 & 0xff);
		MRPcInit();
		var1->work.ptr[1] = mrp_walk_act_init(var2);
		var1->work.ul[2] = var2;
		var1->work.ul[0] = 1;
	}
	else
	{
		if (var1->work.ul[2] != (DAT_05b9d744 & 0xff))
		{
			MRPcEnd();
			if (var1->work.ptr[1] != NULL)
			{
				DestroyTask((struct task *)var1->work.ptr[1]);
				var1->work.ptr[1] = NULL;
			}
			var1->work.ul[0] = 0;
		}
	}
}
