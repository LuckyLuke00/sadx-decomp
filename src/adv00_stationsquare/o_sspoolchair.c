#include "decls.h"

// GLOBAL: SADX 0x026ddef8
static struct CCL_INFO ccinfo[1];

static void ObjectMain(struct task *tp);
static void ObjectDisplay(struct task *tp);

#pragma optimize("", off)
// STUB: SADX 0x0068afc0
static void ObjectDisplay(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x0068b030
static void ObjectMain(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (FUN_004c39c0(tp) != 0)
	{
		ObjectDisplay(tp);
		return;
	}

	if (CheckRangeOut(tp) == 0)
	{
		ObjectDisplay(tp);
		EntryColliList(var1);
	}
}

// FUNCTION: SADX 0x0068b070
void ObjectSSPoolchair(struct task *tp)
{
	if (CheckRangeOut(tp) == 0)
	{
		CCL_Init(tp, ccinfo, 1, 4);
		tp->exec = ObjectMain;
		tp->disp = ObjectDisplay;
	}
}
