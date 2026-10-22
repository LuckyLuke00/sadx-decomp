#include "decls.h"

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
