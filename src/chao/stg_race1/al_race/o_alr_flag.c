#include "decls.h"
static void dispObject(struct task *task_p);
static void execObject(struct task *task_p);
static void initObject(struct task *task_p, void *param_p);
extern int DAT_05b9d838;

#pragma optimize("", off)
// STUB: SADX 0x00717660
static void initObject(struct task *task_p, void *param_p)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x007176c0
static void dispObject(struct task *task_p)
{
	struct taskwk *var3;
	struct motionwk *var4;
	float var1;
	long var2;

	if (DAT_05b9d838 != 0)
	{
		return;
	}
	if (CheckRange(task_p) != 0)
	{
		return;
	}
	var3 = task_p->twp;
	var4 = task_p->mwp;
	njPushMatrix(0);
	njTranslateV(0, &var3->pos);
	njRotateY(0, 0x7000);
	___njSetTexture(&texlist_obj_al_race);
	var1 = var4->work.f;
	var2 = *(long *)((char *)var4 + 8);
	FUN_004a88c0((NJS_ACTION *)var2, var1);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x00717730
static void execObject(struct task *task_p)
{
	struct motionwk *var1 = task_p->mwp;

	var1->work.f = var1->work.f + 1.0f;
	if (var1->spd.x <= var1->work.f)
	{
		var1->work.f = var1->work.f - var1->spd.x;
	}
	dispObject(task_p);
}

// GLOBAL: SADX 0x009c8afc
static struct TaskInfo ObjectTaskInfo = {12, 2, initObject, execObject, dispObject, 0};
