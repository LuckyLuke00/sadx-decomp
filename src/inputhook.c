#include "decls.h"
void FUN_0055f9e0(struct task *param_1);
static void inputhook_exec(struct task *task_p);
int FUN_0055f9f0(struct task *param_1, struct task **param_2);
extern struct task *DAT_05ccdac8;
extern struct task *DAT_05ccdacc;

// FUNCTION: SADX 0x0055f530
struct task *InputHookInit()
{
	struct task *local_8;
	local_8 = CreateElementalTask(0, 0, inputhook_exec);
	DAT_05ccdac8 = 0;
	DAT_05ccdacc = 0;
	if (local_8 != 0)
	{
		local_8->dest = FUN_0055f9e0;
	}
	return local_8;
}

// FUNCTION: SADX 0x0055f580
long InputHookSet(struct task *hook_task_p, struct NJS_POINT3 *pos_p, long *ang_y_p, long *status_p, long type, float range)
{
	struct task *local_8g;
	struct task *local_cg;

	if (FUN_0055f9f0(hook_task_p, &local_8g) == 0)
	{
		local_cg = local_8g;
		local_8g = (struct task *)MAlloc(0x20);
		if (local_8g == (struct task *)0x0)
		{
			return 0;
		}
		local_8g->next = local_cg;
		if (local_cg != (struct task *)0x0)
		{
			local_cg->last = local_8g;
		}
		else
		{
			DAT_05ccdac8 = local_8g;
		}
		local_8g->last = (struct task *)0x0;
	}
	local_8g->ocp = (struct OBJ_CONDITION *)type;
	local_8g->ctp = (struct task *)pos_p;
	local_8g->exec = (void (*)(struct task *))ang_y_p;
	local_8g->disp = (void (*)(struct task *))status_p;
	*(float *)((char *)local_8g + 0x18) = range;
	local_8g->ptp = hook_task_p;
	return 1;
}

// FUNCTION: SADX 0x0055f630
void InputHookRelease(void)
{
	if (DAT_05ccdacc != 0)
	{
		*(int *)DAT_05ccdacc->disp = 0;
		DAT_05ccdacc = 0;
	}
	PadReadOnP(0xff);
}

// STUB: SADX 0x0055f670
void InputHookDelete(struct task *del_task_p)
{
}

// STUB: SADX 0x0055f6f0
static void inputhook_exec(struct task *task_p)
{
}

// STUB: SADX 0x0055f990
void FUN_0055f990(struct task *param_1)
{
}

// STUB: SADX 0x0055f9e0
void FUN_0055f9e0(struct task *param_1)
{
}

// STUB: SADX 0x0055f9f0
int FUN_0055f9f0(struct task *param_1, struct task **param_2)
{
	return (int)0;
}

// STUB: SADX 0x0055fa50
void inputhook_end(struct task *task_p)
{
}
