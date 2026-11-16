#include "decls.h"

// FUNCTION: SADX 0x0046e080
void FHangyoDest(struct task *tp)
{
	if (tp->awp != NULL)
	{
		Free(tp->awp);
		tp->awp = NULL;
	}
}

// STUB: SADX 0x0046e0a0
void FHangyoDisp(struct task *tp)
{
}

// FUNCTION: SADX 0x0046e2e0
struct task *ALO_BlackmarketHangyoCreate(struct task *parent_tp)
{
	return CreateChildTask(0, FHangyoExec, parent_tp);
}
