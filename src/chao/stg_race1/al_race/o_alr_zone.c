#include "decls.h"
extern short DAT_05ccde90;
extern int DAT_05b9d838;
void MirenObjEditDrawCollision(const struct colliwk *colliWk_p);
static void initObject(struct task *task_p, void *param_p);
static void execObject(struct task *task_p);
static void dispObject(struct task *task_p);

// GLOBAL: SADX 0x00962fb8
static struct TaskInfo DAT_00962fb8 = {0, 2, initObject, execObject, dispObject,
	(void (__cdecl *)(struct task *))FUN_007d21b0};

// STUB: SADX 0x00493630
static void initObject(struct task *task_p, void *param_p)
{
}

// FUNCTION: SADX 0x00493660
static void dispObject(struct task *task_p)
{
	if (DAT_05ccde90 && DAT_05b9d838 == 0)
	{
		MirenObjEditDrawCollision(task_p->twp->cwp);
	}
}

// FUNCTION: SADX 0x00493690
static void execObject(struct task *task_p)
{
	struct taskwk *var1 = task_p->twp;
	if (FUN_004c39c0(task_p))
	{
		var1->cwp->info->a = var1->scl.x;
	}
	else
	{
		EntryColliList(var1);
	}
	dispObject(task_p);
}

// FUNCTION: SADX 0x004936e0
void ObjectAlrZone(struct task *task_p)
{
	MirenInitTask(task_p, &DAT_00962fb8, 0);
}
