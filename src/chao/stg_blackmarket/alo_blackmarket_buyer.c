#include "decls.h"

// FUNCTION: SADX 0x0046e080
void FBuyerDest(struct task *tp)
{
	if (tp->awp != NULL)
	{
		Free(tp->awp);
		tp->awp = NULL;
	}
}

// STUB: SADX 0x0046e300
void FBuyerDisp(struct task *tp)
{
}

// FUNCTION: SADX 0x0046e4b0
struct task *ALO_BlackmarketBuyerCreate(struct task *ptp)
{
	struct task *var1 = CreateChildTask(2, FBuyerExec, ptp);
	if (var1 != NULL)
	{
		var1->twp->mode = 0;
	}
	return var1;
}
