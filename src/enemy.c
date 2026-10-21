#include "decls.h"
void FUN_005e2cc0(struct taskwk *param_1, struct enemywk *param_2);

// FUNCTION: SADX 0x005e3b40
void EnemyCheckGroundCollision(struct taskwk *twp, struct enemywk *ewp)
{
	EnemyGetShadow(twp, ewp);
	FUN_005e2cc0(twp, ewp);
	EnemyCheckFloor(twp, ewp);
	EnemyCheckWall(twp, ewp);
}

// FUNCTION: SADX 0x005e3b90
void EnemyPreserveHomePosition(struct taskwk *twp, struct enemywk *ewp)
{
	ewp->home = twp->pos;
}

// FUNCTION: SADX 0x005e3bc0
void EnemyPreservePreviousPosition(struct taskwk *twp, struct enemywk *ewp)
{
	ewp->pre = twp->pos;
}

// FUNCTION: SADX 0x005e3bf0
void EnemyBackToPreviousPosition(struct taskwk *twp, struct enemywk *ewp)
{
	twp->pos = ewp->pre;
}

// FUNCTION: SADX 0x005e3c20
float EnemyDist2FromAim(struct taskwk *twp, struct enemywk *ewp)
{
	float local_8;

	local_8 = (ewp->aim.x - twp->pos.x) * (ewp->aim.x - twp->pos.x) +
	         (ewp->aim.y - twp->pos.y) * (ewp->aim.y - twp->pos.y) +
	         (ewp->aim.z - twp->pos.z) * (ewp->aim.z - twp->pos.z);
	return local_8;
}

// STUB: SADX 0x005e3d10
long FUN_005e3d10(struct taskwk *twp, struct enemywk *ewp)
{
	return (long)0;
}

// STUB: SADX 0x005e3d60
float EnemyDistFromHome(struct taskwk *twp, struct enemywk *ewp)
{
	return (float)0;
}

// FUNCTION: SADX 0x005e3dd0
float EnemyDist2FromHome(struct taskwk *twp, struct enemywk *ewp)
{
	float local_8;

	local_8 = (ewp->home.x - twp->pos.x) * (ewp->home.x - twp->pos.x) + (ewp->home.y - twp->pos.y) * (ewp->home.y - twp->pos.y) + (ewp->home.z - twp->pos.z) * (ewp->home.z - twp->pos.z);
	return local_8;
}

// FUNCTION: SADX 0x005e3ec0
long EnemyTurnToHome(struct taskwk *twp, struct enemywk *ewp)
{
	long local_8;
	local_8 = EnemyCalcHomeAngle(twp, ewp);
	*(long *)((char *)twp + 0x18) = AdjustAngle(*(long *)((char *)twp + 0x18), ewp->aim_angle, ewp->angy_spd);
	return local_8;
}

// FUNCTION: SADX 0x005e4850
void EnemyPartsDisplayer(struct task *tp)
{
	EnemyPartsDraw(tp->twp);
}

// FUNCTION: SADX 0x005e4870
void DestructorEnemyParts(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	local_8->wtimer = 0xff;
	local_8->counter.l = 0;
	local_8->value.l = 0;
}

// FUNCTION: SADX 0x005e4950
void EnemyBaneDisplayer(struct task *tp)
{
	EnemyBaneDraw(tp->twp);
}
