#include "decls.h"

// STUB: SADX 0x006a3790
void HallBridgeDisplayer(struct task *tp)
{
}

// FUNCTION: SADX 0x006a3910
void bridgechiledexec(struct task *tp)
{
	struct task *var1 = tp->ptp;
	struct taskwk *var2 = var1->twp;
	if (var2->flag & 0x800)
	{
		tp->twp->flag |= 0x100;
		return;
	}
	tp->twp->flag &= 0xfeff;
}

// STUB: SADX 0x006a3940
void bridgechiled(struct task *ptp, struct obj *obj)
{
}
