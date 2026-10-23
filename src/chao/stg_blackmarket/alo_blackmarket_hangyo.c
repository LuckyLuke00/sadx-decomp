#include "decls.h"

// STUB: SADX 0x0046e0a0
void FHangyoDisp(struct task *tp)
{
}

// FUNCTION: SADX 0x0046e2e0
struct task *ALO_BlackmarketHangyoCreate(struct task *parent_tp)
{
	return CreateChildTask(0, FHangyoExec, parent_tp);
}
