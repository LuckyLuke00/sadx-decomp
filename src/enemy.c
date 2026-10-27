#include "decls.h"
extern "C" int rand(void);
extern "C" double atan2(double v, double u);
void FUN_005e4370(struct enemywk *param_1);
void FUN_0067d2d0(float *param_1, float param_2, float param_3, float param_4);
void FUN_005e4370(struct enemywk *param_1);
void EnemyBaneDraw(struct taskwk *twp);
void EnemyBaneDisplayer(struct task *tp);
void FUN_005e2cc0(struct taskwk *param_1, struct enemywk *param_2);

// STUB: SADX 0x005e28c0
struct enemywk *EnemyInitialize(struct task *tp, struct taskwk *twp)
{
	return (struct enemywk *)0;
}

// STUB: SADX 0x005e2a10
signed char EnemySearchPlayer(struct taskwk *twp, struct enemywk *ewp)
{
	return (signed char)0;
}

#pragma optimize("", off)
// STUB: SADX 0x005e2b60
void EnemyGetShadow(struct taskwk *twp, struct enemywk *ewp)
{
}
#pragma optimize("", on)

#pragma optimize("", off)
// STUB: SADX 0x005e2cc0
void FUN_005e2cc0(struct taskwk *twp, struct enemywk *ewp)
{
}
#pragma optimize("", on)

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

// FUNCTION: SADX 0x005e3c80
long EnemyCalcAimAngle(struct taskwk *twp, struct enemywk *ewp)
{
	long local_cg;
	long local_8g;

	local_cg = twp->ang.y;
	ewp->aim_angle = (long)(atan2(*(float *)((char *)ewp + 0x5c) - *(float *)((char *)twp + 0x20), *(float *)((char *)ewp + 0x64) - *(float *)((char *)twp + 0x28)) * 65536.0 / 6.283184) - 0x4000;
	local_8g = DiffAngle(ewp->aim_angle, local_cg);
	local_8g &= 0xffff;
	return local_8g;
}

// FUNCTION: SADX 0x005e3d10
long FUN_005e3d10(struct taskwk *param_1, struct enemywk *param_2)
{
	long local_8;
	local_8 = EnemyCalcAimAngle(param_1, param_2);
	*(long *)((char *)param_1 + 0x18) = AdjustAngle(*(long *)((char *)param_1 + 0x18), param_2->aim_angle, param_2->angy_spd);
	return local_8;
}

// FUNCTION: SADX 0x005e3d60
float EnemyDistFromHome(struct taskwk *twp, struct enemywk *ewp)
{
	float local_8;

	local_8 = (ewp->home.x - twp->pos.x) * (ewp->home.x - twp->pos.x) +
	         (ewp->home.y - twp->pos.y) * (ewp->home.y - twp->pos.y) +
	         (ewp->home.z - twp->pos.z) * (ewp->home.z - twp->pos.z);
	return njSqrt(local_8);
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

// FUNCTION: SADX 0x005e3f10
float EnemyDist2FromPlayer(struct taskwk *twp, int num)
{
	struct taskwk *local_8g;
	float local_cg;

	local_8g = DAT_05baf368[num];
	if (local_8g == 0)
	{
		___OutputDebugString("%s %d:playertwp=0\n", "..\\..\\src\\enemy.c", 0x316);
		return 0.0f;
	}
	local_cg = (local_8g->pos.x - twp->pos.x) * (local_8g->pos.x - twp->pos.x) +
	          (local_8g->pos.y - twp->pos.y) * (local_8g->pos.y - twp->pos.y) +
	          (local_8g->pos.z - twp->pos.z) * (local_8g->pos.z - twp->pos.z);
	return local_cg;
}

// STUB: SADX 0x005e3fa0
long EnemyCalcPlayerAngle(struct taskwk *twp, struct enemywk *ewp, unsigned char pnum)
{
	return (long)0;
}

// FUNCTION: SADX 0x005e4060
long EnemyTurnToPlayer(struct taskwk *twp, struct enemywk *ewp, unsigned char pnum)
{
	long local_8;
	local_8 = EnemyCalcPlayerAngle(twp, ewp, pnum);
	*(long *)((char *)twp + 0x18) = AdjustAngle(*(long *)((char *)twp + 0x18), ewp->aim_angle, ewp->angy_spd);
	return local_8;
}

// FUNCTION: SADX 0x005e40b0
signed char EnemyCheckFrameIn(struct NJS_POINT3 *pos)
{
	struct NJS_POINT2 prj_pos;

	njProjectScreen((float (*)[16])0, pos, &prj_pos);
	if (prj_pos.x >= 0.0f && prj_pos.x <= 640.0f && prj_pos.y >= 0.0f && prj_pos.y <= 400.0f)
		return 1;
	return 0;
}

// STUB: SADX 0x005e4120
void EnemyAimAroundPlayer(struct taskwk *twp, struct enemywk *ewp, int pnum, int aim_num)
{
}

// STUB: SADX 0x005e4210
void EnemyPartsMove(struct taskwk *twp)
{
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

// FUNCTION: SADX 0x005e43f0
void EnemyPartsDraw(struct taskwk *twp)
{
	struct NJS_POINT3 *local_8g;
	struct NJS_MODEL *local_cg;

	local_cg = (struct NJS_MODEL *)twp->counter.ptr;
	local_8g = (struct NJS_POINT3 *)((char *)local_cg + 0x18);
	if (dsCheckViewV(&twp->pos, 10.0f) == 0)
	{
		return;
	}
	___njSetTexture((struct NJS_TEXLIST *)twp->value.ptr);
	njPushMatrix(0);
	njTranslateV(0, &twp->pos);
	if (twp->ang.z != 0)
	{
		njRotateZ(0, (unsigned short)twp->ang.z);
	}
	if (twp->ang.x != 0)
	{
		njRotateX(0, (unsigned short)twp->ang.x);
	}
	if (twp->ang.y != 0)
	{
		njRotateY(0, (unsigned short)twp->ang.y);
	}
	FUN_0067d830(0, -local_8g->x, -local_8g->y, -local_8g->z);
	___dsDrawModel(local_cg);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x005e44f0
void EnemyBaneDraw(struct taskwk *twp)
{
	struct NJS_MODEL *local_8g;
	struct NJS_MODEL *local_cg;

	local_8g = (struct NJS_MODEL *)twp->counter.ptr;
	if (local_8g == 0)
	{
		return;
	}
	local_cg = (struct NJS_MODEL *)local_8g->points;
	if (dsCheckViewV(&twp->pos, 10.0f) == 0)
	{
		return;
	}
	SetRegularTexture();
	njPushMatrix(0);
	njTranslateV(0, &twp->pos);
	if (twp->ang.z != 0)
	{
		njRotateZ(0, (unsigned short)twp->ang.z);
	}
	if (twp->ang.x != 0)
	{
		njRotateX(0, (unsigned short)twp->ang.x);
	}
	if (twp->ang.y != 0)
	{
		njRotateY(0, (unsigned short)twp->ang.y);
	}
	FUN_0067d2d0(0, 0.5f, 1.5f, 0.5f);
	FUN_0067d2d0(0, 0.6f, 0.6f, 0.6f);
	___dsDrawModel(local_8g);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x005e4610
void EnemySmoke(struct taskwk *twp)
{
	struct sp_task *local_8g;
	int local_cj;
	float local_10m;
	int local_14;
	float local_18g;

	local_8g = SpCreateTask(particle_smoke.link, EffectSmokeExp);
	if (local_8g != NULL)
	{
		local_8g->pos = twp->pos;
		local_8g->scl = 0.015000001f;
		local_cj = rand();
		local_10m = (float)(local_cj / 32768.0);
		local_8g->frame = (float)(local_10m * 6.0);
		local_14 = rand();
		local_18g = (float)(local_14 / 32768.0);
		local_8g->ang = (int)((local_18g * 360.0) * 65536.0 / 360.0);
	}
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

// STUB: SADX 0x005e4970
void CreateExpParts(struct taskwk *twp, struct NJS_MODEL * *model, struct NJS_TEXLIST *tex)
{
}

// STUB: SADX 0x005e4b30
void CreateExpSpring(struct taskwk *twp, unsigned char num)
{
}

// FUNCTION: SADX 0x005e4cc0
void EnemyBuyoScale(struct taskwk *twp, struct enemywk *ewp)
{
	float local_8;

	local_8 = twp->scl.y - 1.0f;
	ewp->buyoscale = (-ewp->buyoscale * 0.2f - local_8 * 0.32f) + ewp->buyoscale;
	twp->scl.y = twp->scl.y + ewp->buyoscale;
	if (twp->scl.y > 1.7f)
	{
		twp->scl.y = 1.7f;
	}
	else
	{
		if (twp->scl.y < 0.3f)
		{
			twp->scl.y = 0.3f;
		}
	}
	twp->scl.x = 2.0f - twp->scl.y;
}

// STUB: SADX 0x005e4d70
void EnemyBumpPlayer(signed char pnum)
{
}

// STUB: SADX 0x005e4e00
long EnemyCheckDamage(struct taskwk *twp, struct enemywk *ewp)
{
	return (long)0;
}
