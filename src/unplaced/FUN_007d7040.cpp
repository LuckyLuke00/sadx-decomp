#include "decls.h"
extern struct task *DAT_060cc69c;

// FUNCTION: SADX 0x007d7040
void FUN_007d7040(float param_1, float param_2, float param_3, float param_4, float param_5)
{
	struct task *var1;
	struct taskwk *var2;

	DAT_060cc69c = CreateElementalTask(2, 5, initWaterPillarTask);
	var1 = DAT_060cc69c;
	var2 = var1->twp;
	var2->pos.x = param_1;
	var2->mode = 0;
	var2->pos.y = param_2;
	var2->counter.l = 0;
	var2->pos.z = param_3;
	var2->scl.x = param_5;
	var2->scl.y = param_5;
	var2->scl.z = param_5;
	var2->timer.f = param_4;
}
