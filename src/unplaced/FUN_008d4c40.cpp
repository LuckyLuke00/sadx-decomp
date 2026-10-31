#include "decls.h"

// FUNCTION: SADX 0x008d4c40
void FUN_008d4c40(struct task *param_1)
{
	struct taskwk *local_8g;
	struct NJS_POINT3 local_18;
	local_8g = param_1->twp;
	if ((local_8g->cwp->flag & 1) != 0)
	{
		local_18.x = 0.0;
		local_18.y = 0.0;
		local_18.z = -10.0;
		local_18.z = local_8g->scl.x;
		njPushMatrix(&_nj_unit_matrix_);
		if (local_8g->ang.z != 0)
		{
			njRotateZ(0, (unsigned short)local_8g->ang.z);
		}
		if (local_8g->ang.x != 0)
		{
			njRotateX(0, (unsigned short)local_8g->ang.x);
		}
		if (local_8g->ang.y + 0x8000 != 0)
		{
			njRotateY(0, (unsigned short)(local_8g->ang.y + 0x8000));
		}
		njCalcVector(0, &local_18, &local_18);
		njPopMatrix(1);
		SetCartVelocity(local_8g->cwp->hit_cwp->mytask, &local_18);
		dsPlay_oneshot(0x2e2, 0, 0, 0);
		dsVolume_id(0, -0x1e);
	}
	EntryColliList(local_8g);
}
