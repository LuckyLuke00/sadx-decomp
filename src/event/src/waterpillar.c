#include "decls.h"
extern struct task *DAT_060cc634;
static void execSplashTask(struct task *p_task);
static void initWaveTask(struct task *p_task);
static void execWaveTask(struct task *p_task);
static void dispWaveTask(struct task *p_task);
void FUN_007d6940(struct task *param_1);
void FUN_007d21b0(...);
extern struct NJS_TEXLIST texlist_l_sibuki;
extern struct NJS_ACTION action_l_circle[1];
extern struct task *DAT_060cc69c;

// FUNCTION: SADX 0x007d6760
void dispSplashTask(struct task *p_task)
{
	struct taskwk *var1;
	var1 = p_task->twp;
	___njSetTexture(&texlist_l_sibuki);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	njScaleV(0, &var1->scl);
	njPopMatrix(1);
}

// STUB: SADX 0x007d67a0
void textureUVScroll()
{
}

// STUB: SADX 0x007d6850
void dispPillarTask(struct task *p_task)
{
}

// FUNCTION: SADX 0x007d6940
void FUN_007d6940(struct task *param_1)
{
	if (param_1->twp->value.l)
	{
		Free(param_1->twp->value.ptr);
	}
}

// FUNCTION: SADX 0x007d6960
static void dispWaveTask(struct task *p_task)
{
	struct taskwk *var1;
	var1 = p_task->twp;
	___njSetTexture(&texlist_l_sibuki);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	njScaleV(0, &var1->scl);
	late_ActionMesh(&action_l_circle[0], var1->counter.f, 0, FUN_004a1e90((float *)&var1->scl));
	njPopMatrix(1);
}

// FUNCTION: SADX 0x007d69d0
void WaterPillarOff()
{
	if (DAT_060cc69c)
	{
		FreeTask(DAT_060cc69c);
		DAT_060cc69c = 0;
	}
}

// STUB: SADX 0x007d69f0
void execSplashTask(struct task *p_task)
{
}

#pragma optimize("", off)
// STUB: SADX 0x007d6bf0
static void execWaveTask(struct task *p_task)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x007d6c70
void initSplashTask(struct task *p_task)
{
	p_task->exec = execSplashTask;
	p_task->disp = dispSplashTask;
	p_task->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
}

// FUNCTION: SADX 0x007d6c90
void initPillarTask(struct task *p_task)
{
	p_task->exec = execPillarTask;
	p_task->disp = dispPillarTask;
	p_task->dest = FUN_007d6940;
}

// FUNCTION: SADX 0x007d6cb0
static void initWaveTask(struct task *p_task)
{
	p_task->exec = execWaveTask;
	p_task->disp = dispWaveTask;
	p_task->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
}

// FUNCTION: SADX 0x007d6cd0
void FUN_007d6cd0(float param_1, float param_2, float param_3, float param_4, float param_5)
{
	struct task *var1;
	struct taskwk *var2;

	DAT_060cc634 = CreateElementalTask(2, 5, initSplashTask);
	var1 = DAT_060cc634;
	var2 = var1->twp;
	var2->pos.x = param_1;
	var2->mode = 0;
	var2->pos.y = param_2;
	var2->pos.z = param_3;
	var2->scl.x = param_5;
	var2->scl.y = param_5;
	var2->scl.z = param_5;
	var2->timer.f = param_4;
	var2->counter.f = 0.0f;
}

// STUB: SADX 0x007d6d20
void createPillar(float pos_x, float pos_y, float pos_z, float play_spd, float scale)
{
}

// FUNCTION: SADX 0x007d6e10
void FUN_007d6e10(float param_1, float param_2, float param_3, float param_4, float param_5)
{
	struct task *var1 = CreateElementalTask(2, 5, initWaveTask);
	struct taskwk *var2 = var1->twp;
	var2->pos.x = param_1;
	var2->mode = 0;
	var2->pos.y = param_2;
	var2->counter.l = 0;
	var2->pos.z = param_3;
	var2->scl.x = param_5;
	var2->scl.y = param_5;
	var2->scl.z = param_5;
	var2->timer.f = param_4;
}

// STUB: SADX 0x007d7020
void initWaterPillarTask(struct task *p_task)
{
}
