#include "decls.h"

// FUNCTION: SADX 0x00828d40
void ExplosionRockDestructor(struct task *_this)
{
	FreeTaskC(_this);
}

// STUB: SADX 0x00828e10
void EffectSteam(struct sp_task *tp, struct sp_link *lp)
{
}

// FUNCTION: SADX 0x00829bb0
void SetUpExplosionRock()
{
	CreateElementalTask(2, 3, ObjectMountainExplosionRock1);
	CreateElementalTask(2, 3, ObjectMountainExplosionRock2);
}
