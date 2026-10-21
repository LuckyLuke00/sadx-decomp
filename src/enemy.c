#include "decls.h"
void FUN_005e4370(struct enemywk *param_1);
void EnemyBaneDraw(struct taskwk *twp);
void EnemyBaneDisplayer(struct task *tp);
void FUN_005e2cc0(struct taskwk *param_1, struct enemywk *param_2);

// STUB: SADX 0x005e2cc0
void FUN_005e2cc0(struct taskwk *twp, struct enemywk *ewp)
{
}

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

// FUNCTION: SADX 0x005e3d10
long FUN_005e3d10(struct taskwk *param_1, struct enemywk *param_2)
{
	long local_8;
	local_8 = EnemyCalcAimAngle(param_1, param_2);
	*(long *)((char *)param_1 + 0x18) = AdjustAngle(*(long *)((char *)param_1 + 0x18), param_2->aim_angle, param_2->angy_spd);
	return local_8;
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

// STUB: SADX 0x005e3e30
long EnemyCalcHomeAngle(struct taskwk *twp, struct enemywk *ewp)
{
	return (long)0;
}

// FUNCTION: SADX 0x005e3ec0
long EnemyTurnToHome(struct taskwk *twp, struct enemywk *ewp)
{
	long local_8;
	local_8 = EnemyCalcHomeAngle(twp, ewp);
	*(long *)((char *)twp + 0x18) = AdjustAngle(*(long *)((char *)twp + 0x18), ewp->aim_angle, ewp->angy_spd);
	return local_8;
}

// FUNCTION: SADX 0x005e4370
void FUN_005e4370(struct enemywk *param_1)
{
	*(float *)((char *)param_1 + 0x30) -= 0.089999996f;
	*(float *)((char *)param_1 + 0x20) += *(float *)((char *)param_1 + 0x2c);
	*(float *)((char *)param_1 + 0x24) += *(float *)((char *)param_1 + 0x30);
	*(float *)((char *)param_1 + 0x28) += *(float *)((char *)param_1 + 0x34);
	*(int *)((char *)param_1 + 0x14) += 0x200;
	*(int *)((char *)param_1 + 0x18) += 0x1000;
	*(int *)((char *)param_1 + 0x1c) += 0x700;
}

// STUB: SADX 0x005e43f0
void EnemyPartsDraw(struct taskwk *twp)
{
}

// STUB: SADX 0x005e4610
void EnemySmoke(struct taskwk *twp)
{
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

// STUB: SADX 0x005e48b0
void EnemyBaneExplode(struct task *tp)
{
}

// FUNCTION: SADX 0x005e4950
void EnemyBaneDisplayer(struct task *tp)
{
	EnemyBaneDraw(tp->twp);
}

// STUB: SADX 0x005e4cc0
void EnemyBuyoScale(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005e4d70
void EnemyBumpPlayer(signed char pnum)
{
}
