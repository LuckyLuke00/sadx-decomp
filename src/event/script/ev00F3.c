#include "decls.h"
extern struct task *DAT_060cb654;
void FUN_007d6940(struct task *param_1);

#pragma auto_inline(off)

// FUNCTION: SADX 0x007318d0
static void dispChaos0Task(struct task *p_task)
{
	struct taskwk *var1 = DAT_060cb654->twp;

	*((unsigned char *)&object_c0_manju_c0_manju->model->mats->diffuse + 3) = *((unsigned char *)var1->value.ptr + 0x1c);
	SetParamDispChaosWater(&var1->pos, &var1->scl);
}

#pragma auto_inline(on)

// FUNCTION: SADX 0x00731900
static void execChaos0Task(struct task *p_task)
{
	struct taskwk *var1 = p_task->twp;
	char *var2 = (char *)var1->value.ptr;

	switch (var1->mode)
	{
	case 0:
		var1->scl.x = njCos((int)((var1->counter.f += 6.0) * 65536.0 / 360.0)) * 0.125 + 1.0;
		var1->scl.y = njCos((int)(var1->counter.f * 65536.0 / 360.0)) * 0.125 + 1.0;
		var1->scl.z = njSin((int)(var1->counter.f * 65536.0 / 360.0)) * 0.125 + 1.0;
		break;
	case 1:
		var1->pos.x = *(float *)(var2 + 4) + var1->pos.x;
		var1->pos.y = *(float *)(var2 + 8) + var1->pos.y;
		var1->pos.z = *(float *)(var2 + 0xc) + var1->pos.z;
		var1->timer.l++;
		if (var1->timer.l > *(long *)(var2 + 0x10))
		{
			var1->mode = 0;
		}
		var1->scl.y = njCos((int)((var1->counter.f += 6.0) * 65536.0 / 360.0)) * 0.5 + 1.5;
		break;
	case 2:
		var1->counter.f += 18.0;
		*(float *)(var2 + 0x14) -= *(float *)(var2 + 0x18);
		var1->timer.l++;
		if (var1->timer.l > *(long *)(var2 + 0x10))
		{
			var1->mode = 3;
		}
		var1->scl.x = njCos((int)(var1->counter.f * 65536.0 / 360.0)) * 0.125 + 1.0;
		var1->scl.y = njCos((int)(var1->counter.f * 65536.0 / 360.0)) * 0.125 + 1.0;
		var1->scl.z = njSin((int)(var1->counter.f * 65536.0 / 360.0)) * 0.125 + 1.0;
		var1->scl.x = *(float *)(var2 + 0x14) * var1->scl.x;
		var1->scl.y = var1->scl.y * *(float *)(var2 + 0x14);
		var1->scl.z = var1->scl.z * *(float *)(var2 + 0x14);
		*(unsigned char *)(var2 + 0x1c) -= *(unsigned char *)(var2 + 0x1d);
		break;
	case 3:
		return;
	}
	dispChaos0Task(p_task);
}

// FUNCTION: SADX 0x00731b20
static void initChaos0Task(struct task *p_task)
{
	p_task->exec = execChaos0Task;
	p_task->disp = dispChaos0Task;
	p_task->dest = FUN_007d6940;
}

// FUNCTION: SADX 0x00731b40
void createChaos0(float pos_x, float pos_y, float pos_z, long ang)
{
	struct taskwk *var1;
	char *var2;
	struct task *var3;

	DAT_060cb654 = CreateElementalTask(2, 5, initChaos0Task);
	var2 = (char *)MAlloc(0x20);
	var1 = DAT_060cb654->twp;
	var1->pos.x = pos_x;
	var1->value.ptr = var2;
	var1->pos.y = pos_y;
	var1->mode = 0;
	var1->ang.y = ang;
	var1->pos.z = pos_z;
	var1->scl.x = 0.8f;
	var1->scl.y = 0.8f;
	var1->scl.z = 0.8f;
	var1->counter.f = 0.0f;
	var3 = SetTaskDispChaosWater(ang);
	*(struct task **)var2 = var3;
	*(unsigned char *)(var2 + 0x1c) = 0x99;
	initialChaos(var3->twp, (struct chaoswk *)var3->awp, 5);
}
