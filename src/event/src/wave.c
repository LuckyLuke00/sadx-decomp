#include "decls.h"
static void initWaveTask(struct task *p_task);
static void execWaveTask(struct task *p_task);
static void dispWaveTask(struct task *p_task);
extern struct task *DAT_060cc7d0[1];
void FUN_007d21b0(...);
void FUN_007d6940(struct task *param_1);
void execWaveCtrlTask(struct task *p_task);
extern struct task *DAT_060cc7d0[];
void FreeTask(struct task *tp);

#pragma optimize("", off)
// STUB: SADX 0x007d7660
static void dispWaveTask(struct task *p_task)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x007d76e0
void stopWaveCtrl(int id)
{
	if (DAT_060cc7d0[id] != NULL)
	{
		FreeTask(DAT_060cc7d0[id]);
		DAT_060cc7d0[id] = NULL;
	}
}

#pragma optimize("", off)
// STUB: SADX 0x007d7710
static void execWaveTask(struct task *p_task)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x007d7790
static void initWaveTask(struct task *p_task)
{
	p_task->exec = execWaveTask;
	p_task->disp = dispWaveTask;
	p_task->dest = FUN_007d6940;
}

// FUNCTION: SADX 0x007d77b0
void FUN_007d77b0(float param_1, float param_2, float param_3, float param_4, float param_5)
{
	struct task *var1 = CreateElementalTask(2, 5, initWaveTask);
	void *var2 = MAlloc(8);
	struct taskwk *var3 = var1->twp;
	var3->pos.x = param_1;
	var3->value.ptr = var2;
	var3->mode = 0;
	var3->pos.y = param_2;
	var3->pos.z = param_3;
	var3->counter.f = 0.0f;
	*(float *)var2 = param_4;
	*(float *)((char *)var2 + 4) = param_5;
}

// FUNCTION: SADX 0x007d7800
void execWaveCtrlTask(struct task *p_task)
{
	struct taskwk *var1 = p_task->twp;
	void *var2 = var1->value.ptr;
	switch (var1->mode)
	{
	case 0:
		var1->mode = 1;
		break;
	case 1:
		var1->counter.l = var1->counter.l + 1;
		if (var1->counter.l % *(int *)((char *)var2 + 8) == 0)
		{
			FUN_007d77b0(var1->pos.x, var1->pos.y, var1->pos.z, *(float *)var2, *(float *)((char *)var2 + 4));
		}
		if (var1->counter.l > *(int *)((char *)var2 + 0xc))
		{
			var1->mode = 2;
			return;
		}
		break;
	case 2:
		FreeTask(p_task);
		return;
	}
}

// FUNCTION: SADX 0x007d7880
void initWaveCtrlTask(struct task *p_task)
{
	p_task->exec = execWaveCtrlTask;
	p_task->disp = (void (__cdecl *)(struct task *))FUN_007d21b0;
	p_task->dest = FUN_007d6940;
}

// STUB: SADX 0x007d78a0
void createWaveCtrl(float pos_x, float pos_y, float pos_z, float play_spd, float scale, int wave_int, int life_int, int id)
{
	struct task *var1;
	struct taskwk *var2;
	struct anywk *var3;

	var1 = CreateElementalTask(2, 5, initWaveCtrlTask);
	DAT_060cc7d0[id] = var1;
	var3 = (struct anywk *)MAlloc(0x10);
	var2 = DAT_060cc7d0[id]->twp;
	var2->pos.x = pos_x;
	var2->value.ptr = var3;
	var2->pos.y = pos_y;
	var2->mode = 0;
	var2->counter.l = 0;
	var2->pos.z = pos_z;
	var3->work.f[0] = play_spd;
	*(int *)&var3->work.f[2] = wave_int;
	*(int *)&var3->work.f[3] = life_int;
	var3->work.f[1] = scale;
}
