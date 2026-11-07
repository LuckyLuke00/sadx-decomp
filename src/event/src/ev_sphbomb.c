#include "decls.h"
void FUN_007d65f0(struct task *param_1);

// FUNCTION: SADX 0x007d6680
struct task *Create_SphereBomb(float x, float y, float z, long frame, float scl_spd, float sphere_radious)
{
	struct task *var1 = CreateElementalTask(3, 3, FUN_007d65f0);
	if (var1 != 0)
	{
		struct taskwk *var2 = var1->twp;
		struct motionwk *var3 = var1->mwp;
		var2->pos.x = x;
		var2->pos.y = y;
		var2->pos.z = z;
		var2->wtimer = (unsigned short)frame;
		var2->mode = 0;
		var2->value.f = scl_spd;
		var2->timer.l = 0;
		var2->scl.x = 2.0f;
		var2->scl.z = 1.0f;
		var3->work.l = 10;
		var3->spd.x = 0.8f;
		var3->spd.z = sphere_radious;
		SphericalExplosionInit();
	}
	return var1;
}

// FUNCTION: SADX 0x007d6700
void ChgSphereBombMode(struct task *tp, signed char mode)
{
	if (tp != 0)
	{
		tp->twp->mode = mode;
	}
}

// FUNCTION: SADX 0x007d6720
void FUN_007d6720(int param_1, float param_2, float param_3, float param_4)
{
	if (param_1 != 0)
	{
		if (*(char *)*(int *)(param_1 + 0x20) == 0)
		{
			*(float *)(*(int *)(param_1 + 0x24) + 4) = param_2;
			*(int *)(*(int *)(param_1 + 0x24)) = (int)param_3;
			*(float *)(*(int *)(param_1 + 0x24) + 0xc) = param_4;
		}
	}
}
