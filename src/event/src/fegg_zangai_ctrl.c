#include "decls.h"

// STUB: SADX 0x007e08d0
void EV_zangai_ctrl_cons(struct task *tp)
{
}

// FUNCTION: SADX 0x007e0940
struct task *EV_zangai_ctrl(float x, float y, float z, float spd, float scl, float range, unsigned short interval)
{
	struct task *var1 = CreateElementalTask(2, 3, EV_zangai_ctrl_cons);
	if (var1 != 0)
	{
		struct taskwk *var2 = var1->twp;
		var2->pos.x = x;
		var2->pos.y = y;
		var2->pos.z = z;
		var2->scl.x = scl;
		var2->scl.y = range;
		var2->scl.z = spd;
		var2->mode = 0;
		var2->counter.w[0] = interval;
	}
	return var1;
}
