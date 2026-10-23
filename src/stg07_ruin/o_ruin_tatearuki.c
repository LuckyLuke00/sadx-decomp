#include "decls.h"
extern char DAT_060d131b;

// FUNCTION: SADX 0x00854100
void PanelTerm(struct task *tp)
{
	struct taskwk *var1;
	int var2;

	DAT_060d131b--;
	var1 = tp->twp;
	var2 = FUN_004c39c0(tp);
	if (var2 == 0)
	{
		WithdrawCollisionEntry(tp, (struct obj *)var1->value.ptr);
		ReleaseMobileLandObject((struct obj *)var1->value.ptr);
		NpcMilesSetStandByFlag(0);
	}
}

// FUNCTION: SADX 0x00854790
void PanelExecEdit(struct task *tp)
{
	tp->twp->wtimer = tp->twp->ang.x;
	PanelExec(tp);
}
