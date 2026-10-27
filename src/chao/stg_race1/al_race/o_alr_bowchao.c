#include "decls.h"
static void dispObject(struct task *task_p);
static void execObject(struct task *task_p);
static void initObject(struct task *task_p, void *param_p);
int FUN_00717df0();

// GLOBAL: SADX 0x009c8a60
static struct TaskInfo ObjectTaskInfo = {20, 2, initObject, execObject, dispObject, 0};

// GLOBAL: SADX 0x009c8a78
static struct ActionParam DAT_009c8a78;

// FUNCTION: SADX 0x00717130
void ObjectAlrBowChao(struct task *task_p)
{
	MirenInitTask(task_p, &ObjectTaskInfo, &DAT_009c8a78);
}

#pragma optimize("", off)
// STUB: SADX 0x00717150
static void initObject(struct task *param_1, void *param_2)
{
}
#pragma optimize("", on)

#pragma optimize("", off)
// STUB: SADX 0x007171c0
static void dispObject(struct task *param_1)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00717230
static void execObject(struct task *task_p)
{
	if (CheckRangeOut(task_p) == 0)
	{
		struct taskwk *var1 = task_p->twp;
		struct motionwk *var2 = task_p->mwp;
		if (FUN_004c39c0(task_p) == 0)
		{
			switch (var2->work.l)
			{
			case 0:
				if (FUN_00717df0() == 0)
				{
					if ((var1->cwp->flag & 1) == 0)
					{
						break;
					}
				}
				var2->work.l = 1;
				break;
			case 1:
				var2->spd.x += var2->spd.z;
				if (var2->spd.y <= var2->spd.x)
				{
					var2->work.l = 0;
					var2->spd.x = 0.0f;
				}
				break;
			}
			EntryColliList(var1);
		}
		dispObject(task_p);
	}
}
