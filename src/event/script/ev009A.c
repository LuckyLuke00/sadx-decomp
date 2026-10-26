#include "decls.h"
extern struct obj DAT_05a862dc;
static void initShadowTask(struct task *p_task);
void *MAlloc(unsigned int size);
static void execShadowTask(struct task *p_task);
static void dispShadowTask(struct task *p_task);
void FUN_007d6940(struct task *param_1);
extern struct task *DAT_060cb8d4;
extern struct task *DAT_060cb8d0;

// STUB: SADX 0x00758c60
void light_cons(struct task *tp)
{
}

// FUNCTION: SADX 0x00758d00
void FUN_00758d00()
{
	DAT_060cb8d0 = CreateElementalTask(0, 1, light_cons);
}

// FUNCTION: SADX 0x00758d20
void FUN_00758d20()
{
	if (DAT_060cb8d0)
	{
		DestroyTask(DAT_060cb8d0);
		DAT_060cb8d0 = 0;
	}
}

// FUNCTION: SADX 0x00758d40
void FUN_00758d40()
{
	if (DAT_060cb8d4)
	{
		FreeTask(DAT_060cb8d4);
	}
}

// FUNCTION: SADX 0x00758d60
static void dispShadowTask(struct task *p_task)
{
	struct taskwk *var1;
	struct motionwk *var2;
	float var3;

	var1 = DAT_060cb8d4->twp;
	var2 = (struct motionwk *)var1->value.ptr;
	SetRegularTexture();
	njPushMatrix(NULL);
	FUN_0067d830(NULL, var1->pos.x, var1->pos.y + 0.5f, ((float *)var2->work.b)[2] - 1.0f + var1->pos.z);
	FUN_0067d2d0(NULL, 1.0f, 1.0f, ((float *)var2->work.b)[2]);
	if (1.0 > ((float *)var2->work.b)[2])
	{
		var3 = 1.0f;
	}
	else
	{
		var3 = ((float *)var2->work.b)[2];
	}
	ds_DrawObjectClip(&DAT_05a862dc, var3);
	njPopMatrix(1);
}

#pragma optimize("", off)
// STUB: SADX 0x00758e20
static void execShadowTask(struct task *p_task)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00758ea0
static void initShadowTask(struct task *p_task)
{
	struct taskwk *var1 = p_task->twp;
	var1->value.ptr = MAlloc(0x10);
	p_task->exec = execShadowTask;
	p_task->disp = dispShadowTask;
	p_task->dest = FUN_007d6940;
}

// FUNCTION: SADX 0x00758ed0
void FUN_00758ed0(float param_1, float param_2, float param_3, int param_4, int param_5, float param_6)
{
	struct taskwk *var1;
	struct motionwk *var2;

	DAT_060cb8d4 = CreateElementalTask(2, 5, initShadowTask);
	FUN_0056aea0(1);
	var1 = DAT_060cb8d4->twp;
	var1->pos.x = param_1;
	var1->mode = 1;
	var1->pos.y = param_2;
	var1->pos.z = param_3;
	var2 = (struct motionwk *)var1->value.ptr;
	var2->work.f = (param_6 - 1.0f) / (float)param_4;
	var2->spd.x = (param_6 - 1.0f) / (float)param_5;
	var2->spd.z = param_6;
	var2->spd.y = 1.0f;
}
