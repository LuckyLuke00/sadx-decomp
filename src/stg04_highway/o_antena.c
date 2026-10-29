#include "decls.h"
static void Draw(struct task *pTask);

#pragma optimize("", off)
// STUB: SADX 0x0081f060
static void Draw(struct task *pTask)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x0081f1f0
void Normal(struct task *pTask)
{
	struct taskwk *var1 = pTask->twp;

	if (CheckRangeOut(pTask))
	{
		return;
	}
	if (!FUN_004c39c0(pTask))
	{
		EntryColliList(var1);
		ObjectSetupInput(var1, 0);
	}
	var1->wtimer += 4;
	Draw(pTask);
}
