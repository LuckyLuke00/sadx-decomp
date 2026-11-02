#include "decls.h"
static void Disp(struct task *tp);

#pragma optimize("", off)
// STUB: SADX 0x00686e90
static void Disp(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00686f00
void ExecNotBig(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOut(tp) == 0)
	{
		EntryColliList(var1);
		Disp(tp);
	}
}
