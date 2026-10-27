#include "decls.h"
#include <math.h>

extern int DAT_060cef14;
void FUN_0060d560(struct NJS_POINT3 *param_1, float param_2);
void FUN_005e5770(struct task *param_1);
float njSqrt(float param_1);
void njUnitMatrix(float *param_1);
static __inline void death(struct task *pTask, float fSize);
static void chkDamage(struct task *pTask);
static void updownHeight(struct task *pTask);
static void FUN_00810290(struct NJS_POINT3 *param_1, float param_2);
static void smoke(struct task *pTask);
static void disp(struct task *pTask);
static void dest(struct task *pTask);
static void _exec(struct task *pTask);

// GLOBAL: SADX 0x03b760f8
static struct CCL_INFO colliInfo[1];

// GLOBAL: SADX 0x03b76128
static struct particle_info missile_smoke;

// FUNCTION: SADX 0x00810080
static void chkDamage(struct task *pTask)
{
	struct taskwk *local_8 = pTask->twp;
	struct enemywk *local_c = (struct enemywk *)pTask->mwp;
	int *local_10 = (int *)pTask->awp;
	struct colliwk *local_14;
	struct task *local_18;
	struct NJS_POINT3 vecDummy;
	if (DAT_060cef14 < 0)
	{
		FUN_005e5770(pTask);
		death(pTask, 0.5f);
		return;
	}
	if ((local_8->flag & 4) && local_c->lock_tp != 0)
	{
		FUN_005e5770(pTask);
		death(pTask, 0.5f);
		return;
	}
	if (ChkE104ColliLandXZ(&local_8->pos, 2.0f, 0, &vecDummy) == 1)
	{
		death(pTask, 0.5f);
		return;
	}
	local_14 = local_8->cwp;
	if ((local_14->flag & 1) && local_14->hit_cwp != (struct colliwk *)local_10[8])
	{
		if (local_14->hit_cwp->id != 1)
		{
			death(pTask, 0.5f);
			return;
		}
		local_18 = local_14->hit_cwp->mytask;
		local_18 = GetE102LockCsTaskPointer(local_18);
		if (local_18 != 0 && local_c->lock_tp == local_18)
		{
			death(pTask, 0.5f);
			return;
		}
	}
	if (local_10[3] <= 0)
	{
		death(pTask, 0.5f);
	}
}

// FUNCTION: SADX 0x008101d0
static void updownHeight(struct task *pTask)
{
	struct NJS_POINT3 *local_4 = (struct NJS_POINT3 *)pTask->awp;
	struct taskwk *var2 = pTask->twp;
	float local_8;
	if (DAT_05baf368[0] == 0)
	{
		local_8 = -var2->pos.y;
	}
	else
	{
		local_8 = GetPlayerWorkPointer(0)->p.center_height + DAT_05baf368[0]->pos.y - var2->pos.y;
	}
	if (fabs(local_8) < 0.1f)
	{
		local_4->y *= 0.7f;
	}
	else
	{
		local_8 = local_8 > 0.0f ? 0.03f : -0.02f;
		local_4->y += local_8;
	}
	local_8 = local_4->y < -1.5f ? -1.5f : (local_4->y > 2.0f ? 2.0f : local_4->y);
	local_4->y = local_8;
}

// FUNCTION: SADX 0x00810290
static void FUN_00810290(struct NJS_POINT3 *param_1, float param_2)
{
	float local_8 = param_1->x * param_1->x + param_1->y * param_1->y + param_1->z * param_1->z;
	local_8 = njSqrt(local_8);
	if (local_8 > param_2)
	{
		param_2 /= local_8;
		param_1->x *= param_2;
		param_1->y *= param_2;
		param_1->z *= param_2;
	}
}

// FUNCTION: SADX 0x00810300
static void smoke(struct task *pTask)
{
	struct taskwk *local_8 = pTask->twp;
	struct NJS_POINT3 pos;
	njPushMatrix(_nj_unit_matrix_);
	pos.z = 0.0f;
	if (local_8->ang.y)
	{
		pos.y = 0.0f;
		pos.x = 2.0f;
		njRotateY(0, local_8->ang.y);
	}
	else
	{
		pos.y = 0.0f;
		pos.x = 2.0f;
	}
	if (local_8->ang.x)
	{
		njRotateX(0, local_8->ang.x);
	}
	njCalcPoint(0, &pos, &missile_smoke.velo);
	njPopMatrix(1);
	missile_smoke.pos.x = local_8->pos.x + missile_smoke.velo.x;
	missile_smoke.pos.y = local_8->pos.y + missile_smoke.velo.y;
	missile_smoke.pos.z = local_8->pos.z + missile_smoke.velo.z;
	CreateAddSmoke(&missile_smoke);
}

// FUNCTION: SADX 0x008103d0
static void disp(struct task *pTask)
{
	struct taskwk *local_8 = pTask->twp;
	float *local_c = (float *)pTask->awp;
	struct NJS_ARGB argb;
	local_c[7] = Shadow(local_8, 1.0f);
	___njSetTexture(&texlist_e103);
	if (((int *)local_c)[6] == 0)
	{
		njPushMatrix(0);
		njTranslateV(0, &local_8->pos);
		if (local_8->ang.y - 0x4000)
		{
			njRotateY(0, local_8->ang.y - 0x4000);
		}
		if (local_8->ang.x + 0x4000)
		{
			njRotateX(0, local_8->ang.x + 0x4000);
		}
		___dsDrawObject(object_03_misile_03_misile_03_misile);
		njPopMatrix(1);
		return;
	}
	SaveControl3D();
	SaveConstantAttr();
	njControl3D(0x14);
	argb.a = 0.0f;
	argb.r = argb.g = argb.b = 1.0f;
	___njSetConstantMaterial(&argb);
	OffConstantAttr(0x200000, 0);
	OnConstantAttr(0, 0x2000000);
	njPushMatrix(0);
	njTranslateV(0, &local_8->pos);
	if (local_8->ang.y - 0x4000)
	{
		njRotateY(0, local_8->ang.y - 0x4000);
	}
	if (local_8->ang.x + 0x4000)
	{
		njRotateX(0, local_8->ang.x + 0x4000);
	}
	njDrawObject(object_03_misile_03_misile_03_misile);
	njPopMatrix(1);
	LoadConstantAttr();
	LoadControl3D();
}

// FUNCTION: SADX 0x00810570
static void dest(struct task *pTask)
{
	int *local_8 = (int *)pTask->awp;
	if (local_8[5] == 0)
	{
		local_8[5] = 1;
		if (DAT_060cef14 > 0)
		{
			DAT_060cef14--;
		}
	}
}

// FUNCTION: SADX 0x008105a0
static void _exec(struct task *pTask)
{
	struct NJS_POINT3 *local_8 = (struct NJS_POINT3 *)pTask->awp;
	struct taskwk *local_c = pTask->twp;
	struct taskwk *local_10;
	long local_14;
	struct NJS_POINT3 local_60;
	struct NJS_POINT3 local_54;
	float local_48[16];
	float local_64;
	((int *)local_8)[3]--;
	chkDamage(pTask);
	local_10 = pTask->twp;
	local_14 = SubAngle(local_10->ang.y, (long)(atan2(
		(double)(float)(local_10->pos.z - DAT_05baf368[0]->pos.z),
		(double)(float)(local_10->pos.x - DAT_05baf368[0]->pos.x)) * 65536.0 / -6.283184));
	if (local_14 < -0x38e)
	{
		local_14 = -0x38e;
	}
	else if (local_14 > 0x38e)
	{
		local_14 = 0x38e;
	}
	local_10->ang.y += local_14;
	updownHeight(pTask);
	local_60.x = -0.4f;
	local_60.y = local_60.z = 0.0f;
	njUnitMatrix(local_48);
	if (local_c->ang.y)
	{
		njRotateY(local_48, local_c->ang.y);
	}
	njCalcPoint(local_48, &local_60, &local_54);
	local_8->x += local_54.x;
	local_8->z = local_8->z + local_54.z;
	FUN_00810290(local_8, 1.0f);
	local_64 = (local_8->z * local_8->z) + local_8->x * local_8->x;
	local_64 = njSqrt(local_64);
	local_c->ang.x = (long)(atan2((double)local_64, (double)local_8->y) * 65536.0 / 6.283184);
	local_c->pos.x += local_8->x;
	local_c->pos.y += local_8->y;
	local_c->pos.z += local_8->z;
	if (((int *)local_8)[3] < 5)
	{
		((int *)local_8)[6] = 1;
	}
	else if (((int *)local_8)[3] < 24)
	{
		((int *)local_8)[6] = (((int *)local_8)[3] >> 1) & 1;
	}
	smoke(pTask);
	EntryColliList(local_c);
	dsPlay_Dolby_time(0x9a, (int)pTask, 1, 0, 4, local_c);
	disp(pTask);
}

// FUNCTION: SADX 0x00810760
void FUN_00810760(struct NJS_POINT3 *param_1, struct NJS_POINT3 *param_2, struct colliwk *param_3)
{
	struct task *local_8 = CreateElementalTask(2, 3, _exec);
	struct taskwk *local_c;
	float *local_10;
	if (local_8)
	{
		local_c = local_8->twp;
		CCL_Init(local_8, colliInfo, 1, 3);
		EnemyInitialize(local_8, local_c);
		local_10 = (float *)MAlloc(0x24);
		local_8->awp = (struct anywk *)local_10;
		local_c->pos = *param_1;
		local_c->ang.y = (long)(atan2((double)param_2->z, (double)param_2->x) * 65536.0 / -6.283184);
		local_10[0] = local_10[1] = local_10[2] = 0.0f;
		((int *)local_10)[3] = 0xd2;
		((int *)local_10)[5] = 0;
		((int *)local_10)[6] = 0;
		local_10[7] = -9999.0f;
		((struct colliwk **)local_10)[8] = param_3;
		DAT_060cef14++;
		local_8->exec = _exec;
		local_8->disp = disp;
		local_8->dest = dest;
	}
}

// FUNCTION: SADX 0x00837700
static __inline void death(struct task *pTask, float fSize)
{
	struct taskwk *local_8 = pTask->twp;
	FUN_0060d560(&local_8->pos, fSize);
	FreeTask(pTask);
	dsPlay_oneshot_Dolby(0x9e, 0, 0, 0, 0x78, local_8);
}
