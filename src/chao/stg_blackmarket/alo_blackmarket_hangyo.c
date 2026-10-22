#include "decls.h"

// FUNCTION: SADX 0x0046e2e0
struct task *ALO_BlackmarketHangyoCreate(struct task *parent_tp)
{
	return CreateChildTask(0, FHangyoExec, parent_tp);
}
