#include "decls.h"
void *FUN_0055e540(void);
static struct task *hintbox_monitor_set(struct task *task_p, enum monitor_mode mode);
extern void Free(void *mp);
static long hintbox_test_range(struct task *task_p, float range);
long FUN_0055f390(struct task *param_1);
void Free(void *mp);
void FUN_0055e510(void *param_1);
long FUN_0055f110(struct task *param_1);

// STUB: SADX 0x0055e2c0
void ObjectHintbox(struct task *task_p)
{
}

// STUB: SADX 0x0055e470
long hintbox_getwork(struct task *task_p)
{
	return (long)0;
}

// FUNCTION: SADX 0x0055e510
void FUN_0055e510(void *param_1)
{
	if (param_1 != NULL)
	{
		Free(*(void **)((char *)param_1 + 0x10));
		Free(param_1);
	}
}

// STUB: SADX 0x0055e540
void *FUN_0055e540(void)
{
	return (void *)0;
}

// FUNCTION: SADX 0x0055e820
void hintbox_exec_wait(struct task *task_p)
{
	struct taskwk *local_cg;
	struct anywk *local_8g;
	local_cg = task_p->twp;
	local_8g = task_p->awp;
	if (hintbox_test_range(task_p, *(float *)((char *)local_8g + 0x1c)) != 0)
	{
		local_cg->mode = 1;
		local_cg->timer.l = FUN_0055f390(task_p);
		if (EV_CheckCansel() == 0)
		{
			SetLookingPointP(0, &local_cg->pos);
			dsPlay_oneshot(0xe, 0, 0, 0);
		}
		InputHookSet(task_p, &local_cg->pos, 0, (long *)&local_cg->counter, 0, 25.0);
	}
}

#pragma optimize("", off)
// STUB: SADX 0x0055e8c0
static long hintbox_test_range(struct task *task_p, float range)
{
	return (long)0;
}
#pragma optimize("", on)

// STUB: SADX 0x0055ea20
void FUN_0055ea20(void *param_1)
{
}

// FUNCTION: SADX 0x0055eab0
void hintbox_exec_turn_back(struct task *task_p)
{
	struct taskwk *local_8;
	if (FUN_0055eaf0(task_p) != 0)
	{
		local_8 = task_p->twp;
		local_8->mode = 0;
	}
	hintbox_exec_wait(task_p);
}

// STUB: SADX 0x0055eaf0
int FUN_0055eaf0(void *param_1)
{
	return (int)0;
}

// STUB: SADX 0x0055ebc0
void hintbox_exec_turn(struct task *task_p)
{
}

// STUB: SADX 0x0055ec70
long hintbox_turn(struct task *task_p)
{
	return (long)0;
}

// STUB: SADX 0x0055ed40
void hintbox_exec_turn_wait(struct task *task_p)
{
}

// FUNCTION: SADX 0x0055ee00
void hintbox_exec_message(struct task *task_p)
{
	struct taskwk *local_8;
	local_8 = task_p->twp;
	hintbox_turn(task_p);
	if ((signed char)local_8->btimer == 0)
	{
		local_8->mode = 0;
		local_8->timer.l = FUN_0055f110(task_p);
		if (EV_CheckCansel() == 0)
		{
			CancelLookingAtP(0);
		}
		InputHookDelete(task_p);
		hintbox_exec_wait(task_p);
		WakeTimer();
		CameraReleaseEventCamera();
	}
}

// STUB: SADX 0x0055f0c0
void hintbox_end(struct task *task_p)
{
}

// FUNCTION: SADX 0x0055f110
long FUN_0055f110(struct task *param_1)
{
	return (long)hintbox_monitor_set(param_1, (enum monitor_mode)0);
}

#pragma optimize("", off)
// STUB: SADX 0x0055f130
static struct task *hintbox_monitor_set(struct task *task_p, enum monitor_mode mode)
{
	return (struct task *)0;
}
#pragma optimize("", on)

// STUB: SADX 0x0055f280
void hintbox_monitor_exec(struct task *montask_p)
{
}
