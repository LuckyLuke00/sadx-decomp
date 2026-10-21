#include "decls.h"
int FUN_004d9d50(struct taskwk *param_1, void *param_2, unsigned char param_3);
int FUN_004d9d50(struct taskwk *param_1, void *param_2, unsigned char param_3);
void njPushMatrix(float *param_1);
void njPopMatrix(int param_1);
extern float _nj_unit_matrix_[16];
void FUN_004da910(int param_1);
extern int DAT_05b9e4c0;
void FUN_004d9b30(int param_1);
int FUN_004d9a50(int param_1);
extern struct taskwk *DAT_05b9ecd8[16];
extern struct taskwk *DAT_05ba2490[16];
int FUN_004da3f0(char *param_1);
extern int DAT_025d9b40[256];
extern int DAT_05ba0bb0[256];
extern int DAT_05b9e0b8;
extern short DAT_05b9e0bc;
extern short DAT_05b9f324;
extern short DAT_05b9f2d8;
extern short DAT_05ba2ea0;
extern int DAT_05ba0bf0;
extern int DAT_05ba2698;
extern int DAT_05b9f528;
extern int DAT_05b9e4d0;
extern unsigned short DAT_05ba248c;
extern unsigned short DAT_05b9e4c4;
extern unsigned short DAT_05ba2690;
extern unsigned short DAT_05b9e4cc;
extern unsigned short DAT_05ba2eac;
extern unsigned short DAT_05ba2ea8;
extern unsigned short DAT_05b9f320;
extern unsigned short DAT_05ba2ea4;
extern unsigned short DAT_05ba2488;
extern unsigned short DAT_05b9e4c8;
extern unsigned short DAT_05b9f2dc;
extern unsigned short DAT_05ba2694;
void FUN_004d05a0();
void FUN_004d0520();
void FUN_004da540(int param_1);
extern int DAT_05ba2478;
extern int DAT_05ba247c;
extern int DAT_05ba2480;
extern int DAT_05ba2484;

// STUB: SADX 0x004cfcb0
long CCL_InitShare(struct task *tp, struct CCL_INFO *info, long nbInfo, unsigned char id)
{
	return (long)0;
}

// STUB: SADX 0x004cfd90
void CCL_ClearInfo(struct taskwk *twp)
{
}

// FUNCTION: SADX 0x004d0460
void CCL_ColliLine2Sphere(struct taskwk *twp1, struct CCL_INFO *info1, struct taskwk *twp2, struct CCL_INFO *info2)
{
	if ((info1->attr & 0x20) != 0)
	{
		*(float *)twp2 = info1->center.x;
		*(float *)((char *)twp2 + 4) = info1->center.y;
		*(float *)((char *)twp2 + 8) = info1->center.z;
	}
	else
	{
		*(float *)twp2 = twp1->pos.x + info1->center.x;
		*(float *)((char *)twp2 + 4) = twp1->pos.y + info1->center.y;
		*(float *)((char *)twp2 + 8) = twp1->pos.z + info1->center.z;
	}
}

// FUNCTION: SADX 0x004d04d0
void CCL_ClearSearch()
{
	DAT_05ba2478 = 0;
	DAT_05ba247c = 0;
	DAT_05ba2480 = 0xffffffff;
	DAT_05ba2484 = 0xffffffff;
}

// FUNCTION: SADX 0x004d0500
void FUN_004d0500()
{
	CCL_ClearSearch();
	FUN_004d05a0();
	FUN_004d0520();
	FUN_004da540(3);
}

// FUNCTION: SADX 0x004d0520
void FUN_004d0520()
{
	DAT_05ba248c = 0;
	DAT_05b9e4c4 = 0;
	DAT_05b9e4cc = DAT_05ba2690;
	DAT_05ba2ea8 = DAT_05ba2eac;
	DAT_05ba2690 = 0;
	DAT_05ba2eac = 0;
	DAT_05b9f320 = 0;
	DAT_05ba2ea4 = 0;
	DAT_05ba2488 = 0;
	DAT_05b9e4c8 = 0;
	DAT_05b9f2dc = 0;
	DAT_05ba2694 = 0;
}

// FUNCTION: SADX 0x004d05a0
void FUN_004d05a0()
{
	DAT_05b9e0bc = 0;
	DAT_05b9f324 = 0;
	DAT_05b9f2d8 = 0;
	DAT_05ba2ea0 = 0;
	DAT_05ba0bf0 = 0;
	DAT_05ba2698 = 0;
	DAT_05b9f528 = 0;
	DAT_05b9e4d0 = 0;
}

// FUNCTION: SADX 0x004d05f0
void CCL_Analyze()
{
	int local_8;

	if (DAT_05b9e0b8)
	{
		for (local_8 = 0; local_8 < DAT_05ba248c; local_8++)
		{
			CCL_ClearInfo((struct taskwk *)DAT_05ba0bb0[local_8]);
		}
	}
	CCL_ClearSearch();
	FUN_004d05a0();
	njPushMatrixEx();
	CCL_PCheckColli();
	CCL_BCheckColli();
	CCL_CCheckColli();
	CCL_E2CheckColli();
	CCL_OCheckColli();
	CCL_O2CheckColli();
	njPopMatrixEx();
	FUN_004d0520();
}

// STUB: SADX 0x004d0930
void CCL_CalcColli(struct taskwk *twp1, struct taskwk *twp2)
{
}

// STUB: SADX 0x004d0ad0
float FUN_004d0ad0(float *param_1, float *param_2)
{
	return (float)0;
}

// FUNCTION: SADX 0x004d0ca0
int FUN_004d0ca0(int param_1, int param_2, int param_3, int param_4)
{
	int local_cg;
	int local_8g;

	local_cg = *(int *)(param_1 + 0x38);
	local_8g = *(int *)(param_3 + 0x38);
	if (((*(int *)(param_4 + 4)) & DAT_025d9b40[*(unsigned short *)local_cg]) != 0)
	{
		return 1;
	}
	if (((*(int *)(param_2 + 4)) & DAT_025d9b40[*(unsigned short *)local_8g]) != 0)
	{
		return 1;
	}
	return 0;
}

// STUB: SADX 0x004d1330
long CCL_CheckPushOut(struct colliwk *cwp1, struct CCL_INFO *info1, struct colliwk *cwp2, struct CCL_INFO *info2)
{
	return (long)0;
}

// FUNCTION: SADX 0x004d2a50
void ConvertPositionGlobalToLocal(struct NJS_POINT3 *center1, struct NJS_POINT3 *center2, long angy, struct NJS_POINT3 *v)
{
	struct NJS_POINT3 v2;
	struct NJS_POINT3 v1;

	v1.x = center1->x - center2->x;
	v1.y = center1->y - center2->y;
	v1.z = center1->z - center2->z;
	njPushMatrix(_nj_unit_matrix_);
	if (angy != 0)
	{
		njRotateY(0, angy);
	}
	njCalcVector(0, &v1, &v2);
	njPopMatrix(1);
	v->x = v2.x;
	v->y = v2.y;
	v->z = v2.z;
}

// STUB: SADX 0x004d2b00
void ConvertPositionLocalToGlobal(struct NJS_POINT3 *center1, struct NJS_POINT3 *center2, long angy, struct NJS_POINT3 *v)
{
}

// FUNCTION: SADX 0x004d52d0
void FUN_004d52d0(char *param_1, char *param_2, NJS_POINT3 *param_3)
{
	switch (FUN_004da3f0(param_1))
	{
	case 0:
		GetPlayerPosition(*(unsigned char *)(*(int *)(*(int *)(param_2 + 0x9c) + 0x20) + 8), 1, param_3, 0);
		break;
	default:
		*param_3 = *(NJS_POINT3 *)(param_1 + 0x20);
		break;
	}
}

// FUNCTION: SADX 0x004d5330
void FUN_004d5330(char *param_1, int param_2, struct NJS_POINT3 *param_3)
{
	int local_8;
	local_8 = FUN_004da3f0(param_1);
	if (local_8 != 0)
	{
	}
	else
	{
		SetPlayerPosition(*(char *)((char *)*(int *)(*(int *)(param_2 + 0x9c) + 0x20) + 8), 0, param_3, 0);
	}
}

// STUB: SADX 0x004d7f60
void FUN_004d7f60(struct taskwk *twp1, struct CCL_INFO *info1, struct taskwk *twp2, struct CCL_INFO *info2)
{
}

// FUNCTION: SADX 0x004d8e80
void CCL_OCheckColli()
{
	struct taskwk **local_ci;
	struct taskwk **local_14;
	struct taskwk **local_8g;
	struct taskwk **local_10;

	local_ci = &DAT_05b9ecd8[DAT_05b9f320];
	for (local_14 = &DAT_05b9ecd8[0]; local_14 < local_ci; local_14++)
	{
		local_8g = &DAT_05ba2490[DAT_05ba2ea4];
		for (local_10 = &DAT_05ba2490[0]; local_10 < local_8g; local_10++)
		{
			CCL_CalcColli(*local_14, *local_10);
		}
	}
}

// FUNCTION: SADX 0x004d8f00
void CCL_O2CheckColli()
{
	struct taskwk **local_8g;
	struct taskwk **local_cj;
	struct taskwk **local_10m;
	struct taskwk **local_14;

	local_cj = (struct taskwk **)((char *)&DAT_05ba248c + DAT_05ba2ea4 * 4);
	local_14 = DAT_05ba2490;
	for (; local_14 < local_cj; local_14++)
	{
		local_8g = &DAT_05ba2490[DAT_05ba2ea4];
		local_10m = local_14 + 1;
		for (; local_10m < local_8g; local_10m++)
		{
			CCL_CalcColli(*local_14, *local_10m);
		}
	}
}

// FUNCTION: SADX 0x004d90f0
void CalcColliRange(struct colliwk *cwp)
{
	CCL_CalcRange(cwp->mytask->twp);
}

// FUNCTION: SADX 0x004d9110
long CCL_GetHitFaceNormal(struct taskwk *twp, struct NJS_POINT3 *norm)
{
	return (long)(signed char)_GetColliFaceNormalPO(twp, norm);
}

// FUNCTION: SADX 0x004d9680
long CCL_IsPushed(struct taskwk *twp)
{
	if (twp == 0)
	{
		return 0;
	}
	if (twp->cwp != 0 && (twp->cwp->flag & 0x10) != 0)
	{
		return 1;
	}
	return 0;
}

// FUNCTION: SADX 0x004d96b0
long CCL_IsHit(struct taskwk *twp)
{
	if (!twp)
	{
		return 0;
	}
	if (twp->cwp && (twp->cwp->flag & 1))
	{
		return 1;
	}
	return 0;
}

// FUNCTION: SADX 0x004d96e0
taskwk *CCL_IsHitPlayer(taskwk *twp)
{
	c_colli_hit_info *local_8;

	local_8 = CCL_IsHitPlayerEx(twp);
	if (local_8 != NULL)
	{
		return local_8->hit_twp;
	}
	else
	{
		return NULL;
	}
}

// STUB: SADX 0x004d9710
struct c_colli_hit_info *CCL_IsHitPlayerEx(struct taskwk *twp)
{
	return (struct c_colli_hit_info *)0;
}

// FUNCTION: SADX 0x004d97c0
int FUN_004d97c0(struct taskwk *param_1, int param_2)
{
	if (DAT_05ba2478 != (int)param_1)
	{
		DAT_05ba2478 = (int)param_1;
		DAT_05ba247c = 0;
		DAT_05ba2484 = 0xffffffff;
		DAT_05ba2480 = 0xffffffff;
	}
	if (DAT_05ba247c != param_2)
	{
		DAT_05ba247c = param_2;
		DAT_05ba2484 = 0xffffffff;
		DAT_05ba2480 = 0xffffffff;
	}
	DAT_05ba2480++;
	if (DAT_05ba2480 > 0x10)
	{
		DAT_05ba2480 = 0x10;
	}
	return DAT_05ba2480;
}

// FUNCTION: SADX 0x004d9850
void FUN_004d9850(int param_1)
{
	DAT_05ba2480 = param_1;
}

// FUNCTION: SADX 0x004d9860
taskwk *CCL_IsHitBullet(taskwk *twp)
{
	c_colli_hit_info *local_8;

	local_8 = CCL_IsHitBulletEx(twp);
	if (local_8 != 0)
	{
		return local_8->hit_twp;
	}
	else
	{
		return 0;
	}
}

// STUB: SADX 0x004d9890
struct c_colli_hit_info *CCL_IsHitBulletEx(struct taskwk *twp)
{
	return (struct c_colli_hit_info *)0;
}

// FUNCTION: SADX 0x004d9940
taskwk *CCL_IsHitEnemy(taskwk *twp)
{
	c_colli_hit_info *local_8;

	local_8 = CCL_IsHitEnemyEx(twp);
	if (local_8 != 0)
	{
		return local_8->hit_twp;
	}
	else
	{
		return 0;
	}
}

// STUB: SADX 0x004d9970
struct c_colli_hit_info *CCL_IsHitEnemyEx(struct taskwk *twp)
{
	return (struct c_colli_hit_info *)0;
}

// FUNCTION: SADX 0x004d9a20
int FUN_004d9a20(int param_1)
{
	int local_8;

	local_8 = FUN_004d9a50(param_1);
	if (local_8 != 0)
	{
		return *(int *)(local_8 + 4);
	}
	else
	{
		return 0;
	}
}

// STUB: SADX 0x004d9a50
int FUN_004d9a50(int param_1)
{
	return (int)0;
}

// FUNCTION: SADX 0x004d9b00
int FUN_004d9b00(int param_1)
{
	int local_8;

	local_8 = ((int (*)(int))FUN_004d9b30)(param_1);
	if (local_8 != 0)
	{
		return *(int *)(local_8 + 4);
	}
	else
	{
		return 0;
	}
}

// STUB: SADX 0x004d9b30
void FUN_004d9b30(int param_1)
{
}

// FUNCTION: SADX 0x004d9be0
struct taskwk *CCL_IsHitKind(struct taskwk *twp, unsigned char kind)
{
	struct c_colli_hit_info *local_8;

	local_8 = CCL_IsHitKindEx(twp, kind);
	if (local_8 != NULL)
	{
		return local_8->hit_twp;
	}
	else
	{
		return NULL;
	}
}

// FUNCTION: SADX 0x004d9c10
struct task *CCL_IsHitKind2(struct taskwk *twp, unsigned char kind)
{
	struct c_colli_hit_info *local_8;

	local_8 = CCL_IsHitKindEx(twp, kind);
	if (local_8)
	{
		if (local_8->hit_twp)
		{
			if (local_8->hit_twp->cwp)
			{
				return local_8->hit_twp->cwp->mytask;
			}
		}
	}
	return 0;
}

// STUB: SADX 0x004d9c60
struct c_colli_hit_info *CCL_IsHitKindEx(struct taskwk *twp, unsigned char kind)
{
	return (struct c_colli_hit_info *)0;
}

// STUB: SADX 0x004d9d50
int FUN_004d9d50(struct taskwk *param_1, void *param_2, unsigned char param_3)
{
	return (int)0;
}

// FUNCTION: SADX 0x004d9e00
struct taskwk *CCL_IsHitPlayerWithNum(struct taskwk *twp, long info_num)
{
	struct c_colli_hit_info *local_8;
	local_8 = CCL_IsHitPlayerWithNumEx(twp, info_num);
	if (local_8 != 0)
		return local_8->hit_twp;
	else
		return 0;
}

// FUNCTION: SADX 0x004d9e30
struct task *CCL_IsHitPlayerWithNum2(struct taskwk *twp, long info_num)
{
	struct c_colli_hit_info *local_8;

	local_8 = CCL_IsHitPlayerWithNumEx(twp, info_num);
	if (local_8 != 0 && local_8->hit_twp != 0 && local_8->hit_twp->cwp != 0)
		return local_8->hit_twp->cwp->mytask;
	return 0;
}

// STUB: SADX 0x004d9e80
struct c_colli_hit_info *CCL_IsHitPlayerWithNumEx(struct taskwk *twp, long info_num)
{
	return (struct c_colli_hit_info *)0;
}

// FUNCTION: SADX 0x004d9f30
struct taskwk *CCL_IsHitObjectWithNum(struct taskwk *twp, long info_num)
{
	struct c_colli_hit_info *local_8;
	local_8 = CCL_IsHitObjectWithNumEx(twp, info_num);
	if (local_8 != 0)
		return local_8->hit_twp;
	else
		return 0;
}

// STUB: SADX 0x004d9f60
struct c_colli_hit_info *CCL_IsHitObjectWithNumEx(struct taskwk *twp, long info_num)
{
	return (struct c_colli_hit_info *)0;
}

// FUNCTION: SADX 0x004da020
struct task *CCL_IsHitKindWithNum2(struct taskwk *twp, long info_num, unsigned char kind)
{
	struct c_colli_hit_info *local_8g = CCL_IsHitKindWithNumEx(twp, info_num, kind);

	if (local_8g != NULL)
	{
		if (local_8g->hit_twp != NULL)
		{
			if (local_8g->hit_twp->cwp != NULL)
			{
				return local_8g->hit_twp->cwp->mytask;
			}
		}
	}
	return NULL;
}

// STUB: SADX 0x004da070
struct c_colli_hit_info *CCL_IsHitKindWithNumEx(struct taskwk *twp, long info_num, unsigned char kind)
{
	return (struct c_colli_hit_info *)0;
}

// FUNCTION: SADX 0x004da160
struct taskwk *CCL_IsHitWithNum(struct taskwk *twp, long info_num)
{
	struct c_colli_hit_info *local_8;

	local_8 = CCL_IsHitWithNumEx(twp, info_num);
	if (local_8 != 0)
		return local_8->hit_twp;
	else
		return 0;
}

// STUB: SADX 0x004da190
struct c_colli_hit_info *CCL_IsHitWithNumEx(struct taskwk *twp, long info_num)
{
	return (struct c_colli_hit_info *)0;
}

// FUNCTION: SADX 0x004da3f0
int FUN_004da3f0(char *param_1)
{
	int iVar1;

	if (param_1 == (char *)0x0)
	{
		return -1;
	}
	iVar1 = *(int *)(param_1 + 0x38);
	if (iVar1 == 0)
	{
		return -1;
	}
	return *(unsigned short *)(int *)iVar1;
}

// FUNCTION: SADX 0x004da420
int FUN_004da420(int param_1, int param_2)
{
	int local_8;

	if (param_2 < 0)
	{
		return -1;
	}
	if (param_2 >= 0x10)
	{
		return -1;
	}
	if (param_1 == 0)
	{
		return -1;
	}
	local_8 = *(int *)(param_1 + 0x38);
	if (local_8 == 0)
	{
		return -1;
	}
	return *(unsigned char *)(*(int *)(local_8 + 0xc) + param_2 * 0x30 + 1);
}

// FUNCTION: SADX 0x004da470
void CCL_Enable(struct taskwk *twp, long info_num)
{
	struct colliwk *local_8;
	if (!twp)
	{
		return;
	}
	local_8 = twp->cwp;
	if (!local_8)
	{
		return;
	}
	local_8->info[info_num].attr &= 0xffffffef;
}

// FUNCTION: SADX 0x004da4c0
void CCL_Disable(struct taskwk *twp, long info_num)
{
	struct colliwk *local_8;

	if (!twp)
	{
		return;
	}
	local_8 = twp->cwp;
	if (!local_8)
	{
		return;
	}
	local_8->info[info_num].attr |= 0x10;
}

// FUNCTION: SADX 0x004da510
struct CCL_INFO *CCL_GetInfo(struct taskwk *twp, long info_num)
{
	if (twp == 0)
		return 0;
	if (twp->cwp == 0)
		return 0;
	return (struct CCL_INFO *)((char *)twp->cwp->info + info_num * 0x30);
}

// FUNCTION: SADX 0x004da540
void FUN_004da540(int param_1)
{
	DAT_05b9e4c0 = param_1;
}

// FUNCTION: SADX 0x004da550
int FUN_004da550()
{
	return DAT_05b9e4c0;
}

// FUNCTION: SADX 0x004da560
void CCL_Entry(struct task *tp)
{
	EntryColliList(tp->twp);
}

// FUNCTION: SADX 0x004da8f0
void FUN_004da8f0(int param_1)
{
	if (param_1 != 0)
	{
		FUN_004da910(*(int *)((char *)param_1 + 0x20));
	}
}

// FUNCTION: SADX 0x004da910
void FUN_004da910(int param_1)
{
	int local_8;

	if (param_1 == 0)
	{
		return;
	}
	local_8 = *(int *)((char *)param_1 + 0x38);
	if (local_8 != 0)
	{
		if (((*(unsigned short *)((char *)local_8 + 4) & 0x8000) != 0) && (*(int *)((char *)local_8 + 0xc) != 0))
		{
			Free(*(void **)((char *)local_8 + 0xc));
			*(int *)((char *)local_8 + 0xc) = 0;
		}
		Free((void *)local_8);
		*(int *)((char *)param_1 + 0x38) = 0;
	}
}

// FUNCTION: SADX 0x004da980
void SET_COLLI_RANGE(struct colliwk *cwp, float range)
{
	if (cwp != 0)
	{
		cwp->colli_range = range;
	}
}
