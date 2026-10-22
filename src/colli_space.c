#include "decls.h"

// FUNCTION: SADX 0x0061d220
void FUN_0061d220(struct taskwk *param_1)
{
	struct CCL_INFO *local_8 = param_1->cwp->info;
	local_8->a = param_1->scl.x + 10.0;
	local_8->b = param_1->scl.y + 10.0;
	local_8->c = param_1->scl.z + 10.0;
	CalcColliRange(param_1->cwp);
}
