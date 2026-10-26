#include "decls.h"
static void initShadowTask(struct task *p_task);
static void execShadowTask(struct task *p_task);
static void dispShadowTask(struct task *p_task);
extern struct task *DAT_060cba88[16];

// FUNCTION: SADX 0x0077e8b0
void shadowOff(signed char num)
{
	if (DAT_060cba88[num] != 0)
	{
		DestroyTask(DAT_060cba88[num]);
		DAT_060cba88[num] = 0;
	}
}

// FUNCTION: SADX 0x0077e8e0
static void dispShadowTask(struct task *p_task)
{
	struct taskwk *var1 = p_task->twp;
	void *var2 = var1->value.ptr;

	SetRegularTexture();
	njPushMatrix(0);
	FUN_0067d830(0, var1->pos.x, var1->pos.y, (*(float *)((char *)var2 + 8)) - 1.0f + var1->pos.z);
	FUN_0067d2d0(0, (*(float *)((char *)var2 + 8)) * 0.5f, 1.0f, *(float *)((char *)var2 + 8));
	ds_DrawObjectClip(&DAT_05a862dc, FUN_00500c70((*(float *)((char *)var2 + 8)) * 0.5f, 1.0f, *(float *)((char *)var2 + 8)));
	njPopMatrix(1);
}

#pragma optimize("", off)
// STUB: SADX 0x0077e9a0
static void execShadowTask(struct task *p_task)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x0077ea20
static void initShadowTask(struct task *p_task)
{
	struct taskwk *var1 = p_task->twp;

	var1->value.ptr = MAlloc(0x10);
	p_task->exec = execShadowTask;
	p_task->disp = dispShadowTask;
	p_task->dest = FUN_007d6940;
}

// FUNCTION: SADX 0x0077ea50
void shadowOn(signed char num, float pos_x, float pos_y, float pos_z, int bigInt, int smallInt, float scaleMax)
{
	struct task *var1;
	struct taskwk *var2;
	struct motionwk *var3;

	var1 = CreateElementalTask(2, 6, initShadowTask);
	DAT_060cba88[num] = var1;
	initShadowTask(var1);
	var2 = DAT_060cba88[num]->twp;
	var2->mode = 1;
	var2->pos.x = pos_x;
	var2->pos.y = pos_y;
	var2->pos.z = pos_z;
	var3 = (struct motionwk *)var2->value.ptr;
	var3->work.f = (scaleMax - 1.0f) / (float)bigInt;
	var3->spd.x = (scaleMax - 1.0f) / (float)smallInt;
	var3->spd.z = scaleMax;
	var3->spd.y = 1.0f;
}
