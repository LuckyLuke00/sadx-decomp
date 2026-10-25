#include "decls.h"
static void TaskExec(struct task *tp);
static void TaskEnd(struct task *tp);
static void TaskDisp(struct task *tp);
extern struct taskwk *DAT_05baf368[8];

// FUNCTION: SADX 0x0084c560
void EffHodaiBombReflectPlayer(struct taskwk *twp)
{
	struct taskwk *var1;

	var1 = twp->cwp->hit_cwp->mytask->twp;
	if (var1 != DAT_05baf368[1])
	{
		SetVelocityP(0, 0.0f, 2.0f, 0.0f);
		var1->pos.y += 1.0f;
	}
}

// FUNCTION: SADX 0x0084c5b0
int CountObjElements(struct obj *pobject)
{
	int var1 = 1;
	if (!(pobject->evalflags & 0x10))
	{
		for (struct obj *var2 = pobject->child; var2; var2 = var2->sibling)
		{
			var1 += CountObjElements(var2);
		}
	}
	return var1;
}

#pragma optimize("", off)
// STUB: SADX 0x0084cdd0
static void TaskEnd(struct task *tp)
{
}
#pragma optimize("", on)

#pragma optimize("", off)
// STUB: SADX 0x0084ce00
static void TaskDisp(struct task *tp)
{
}
#pragma optimize("", on)

#pragma optimize("", off)
// STUB: SADX 0x0084ce10
static void TaskExec(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x0084ce50
void TaskInit(struct task *tp)
{
	tp->exec = TaskExec;
	tp->disp = TaskDisp;
	tp->dest = TaskEnd;
}
