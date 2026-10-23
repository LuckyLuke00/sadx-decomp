#include "decls.h"

// STUB: SADX 0x007dec40
void eggmissile_draw(struct task *tp)
{
}

// STUB: SADX 0x007ded40
void FUN_007ded40(struct NJS_MESHSET *param_1)
{
}

// STUB: SADX 0x007def30
void SetEggMissileParam(struct task *tp, float scl)
{
}

// FUNCTION: SADX 0x007def50
void SetMissileEffect(struct task *tp, unsigned char attr)
{
	if (tp != 0)
	{
		tp->twp->btimer = attr;
	}
}

// STUB: SADX 0x007def70
void ExecEggmissileFire(struct sp_task *tp, struct sp_link *lp)
{
}

// STUB: SADX 0x007df210
void eggmissile_init(struct task *tp)
{
}

// FUNCTION: SADX 0x007df270
struct task *Create_EV_Eggmissile()
{
	return CreateElementalTask(2, 3, eggmissile_init);
}
