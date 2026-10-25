#include "decls.h"
static void Draw(struct task *tp);

#pragma optimize("", off)
// STUB: SADX 0x00821ff0
static void Draw(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00822190
void Norm(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOutWithR(tp, 25000000.0f))
	{
		return;
	}
	if (!FUN_004c39c0(tp))
	{
		EntryColliList(var1);
		ObjectSetupInput(var1, 0);
	}
	Draw(tp);
	var1->wtimer++;
}
