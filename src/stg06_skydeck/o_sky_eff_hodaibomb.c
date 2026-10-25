#include "decls.h"

// FUNCTION: SADX 0x0084c560
void EffHodaiBombReflectPlayer(struct taskwk *twp)
{
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
