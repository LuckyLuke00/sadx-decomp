#include "decls.h"

// FUNCTION: SADX 0x008d88b0
void FUN_008d88b0(struct taskwk *param_1, struct enemywk *param_2)
{
	if (EnemyCheckDamage(param_1, param_2) != 0)
	{
		param_1->mode = 7;
		param_1->counter.b[0] = 0;
		param_1->counter.b[1] = 1;
		param_1->scl.z = 0.35f;
	}
}
