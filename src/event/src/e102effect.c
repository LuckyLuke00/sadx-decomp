#include "decls.h"
extern struct task *DAT_060cc9ac;

// STUB: SADX 0x007d94a0
void e102effect_init(struct task *tp)
{
}

// FUNCTION: SADX 0x007d94c0
void SetE102Effect(float x, float y, float z)
{
	struct task *var1 = CreateElementalTask(2, 5, e102effect_init);
	DAT_060cc9ac = var1;
	if (var1 != 0)
	{
		struct taskwk *var2 = var1->twp;
		var2->pos.x = x;
		var2->pos.y = y;
		var2->pos.z = z;
	}
}

// FUNCTION: SADX 0x007d9500
void ChgEffectMod(signed char mode)
{
	if (DAT_060cc9ac)
	{
		DAT_060cc9ac->twp->mode = mode;
	}
}

// FUNCTION: SADX 0x007d9520
void DelE102Effect()
{
	if (DAT_060cc9ac)
	{
		FreeTask(DAT_060cc9ac);
		DAT_060cc9ac = 0;
	}
}
