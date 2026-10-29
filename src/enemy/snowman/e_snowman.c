#include "decls.h"
#include <math.h>
void snowfaceRunaway(struct taskwk *twp, struct enemywk *ewp);
void SnowfaceAction(struct taskwk *twp, struct enemywk *ewp);
void SnowfaceRectifyPosition(struct taskwk *twp, struct enemywk *ewp);
long AdjustAngle(long ang0, long ang1, long dang);
float njSin(int);
extern struct taskwk *DAT_05baf368[8];
void FUN_0060a360(struct taskwk *param_1, struct enemywk *param_2);
void FUN_0060a5e0(struct taskwk *param_1, struct enemywk *param_2);
void FUN_0060a0c0(struct taskwk *param_1, struct enemywk *param_2);
extern void FUN_0060a360(struct taskwk *param_1, struct enemywk *param_2);
extern void FUN_0060a0c0(struct taskwk *param_1, struct enemywk *param_2);
extern void FUN_00609e40(int param_1, int param_2);
void FUN_00609ad0(struct task *param_1, struct enemywk *param_2);
void FUN_00609b40(int param_1);
void FUN_00609ba0(struct taskwk *param_1, struct enemywk *param_2);
void FUN_00609d20(struct taskwk *param_1, struct enemywk *param_2);
void snowmanChase(struct taskwk *twp, struct enemywk *ewp);
void snowmanTurn(struct taskwk *twp, struct enemywk *ewp);
void FUN_0060a7c0(char *param_1, int param_2);
void snowmanDestroy(struct taskwk *twp, struct enemywk *ewp);
void SnowMobile(struct task *tp);
void FUN_0060b190(struct task *param_1);
void SnowfaceDisplayer(struct task *tp);
int dsPlay_oneshot(int tone, int id, int pri, int volofs);
extern struct particle_entry particle_pom;
extern "C" int rand(void);
void create_whitesmoke(struct particle_info *info, struct NJS_POINT3 *pos, struct NJS_POINT3 *spd, float scl);
void DisplaySnowface(struct taskwk *twp, struct enemywk *ewp);
void DisplaySnowMobile(struct taskwk *twp, struct enemywk *ewp);
void DrawSnowmanRange(struct NJS_POINT3 *pos, float radius);
void FUN_0060b2f0(struct taskwk *param_1, struct enemywk *param_2);
void SnowmanTurnToAim(struct taskwk *twp, struct enemywk *ewp);
void SnowmanMove(struct taskwk *twp, struct enemywk *ewp);
void SnowmanRectifyPosition(struct taskwk *twp, struct enemywk *ewp);
long EnemyTurnToPlayer(struct taskwk *twp, struct enemywk *ewp, unsigned char pnum);
void SnowmanBackSmoke(struct taskwk *twp, struct enemywk *ewp);
void SnowmanFootSmoke(struct taskwk *twp, struct enemywk *ewp);
void EnemyCheckGroundCollision(struct taskwk *twp, struct enemywk *ewp);
long EnemyTurnToHome(struct taskwk *twp, struct enemywk *ewp);
void EnemyPreservePreviousPosition(struct taskwk *twp, struct enemywk *ewp);

// STUB: SADX 0x006095a0
void EnemySnowman(struct task *tp)
{
}

// FUNCTION: SADX 0x00609820
void SnowmanDestructor(struct task *tp)
{
	struct taskwk *local_cg;
	struct motionwk *local_8g;
	local_cg = tp->twp;
	local_8g = tp->mwp;
	if (local_8g != NULL)
	{
		FUN_005b5aa0(tp, local_cg, local_8g);
	}
}

// STUB: SADX 0x00609860
void SnowmanRegular(struct task *tp)
{
}

// STUB: SADX 0x00609ad0
void FUN_00609ad0(struct task *param_1, struct enemywk *param_2)
{
}

// FUNCTION: SADX 0x00609b40
void FUN_00609b40(int param_1)
{
	float local_8;

	local_8 = *(float *)(param_1 + 0x30) - 1.0f;
	*(float *)(param_1 + 0x34) = (-*(float *)(param_1 + 0x34) * 0.12f - local_8 * 0.32f) + *(float *)(param_1 + 0x34);
	*(float *)(param_1 + 0x30) = *(float *)(param_1 + 0x30) + *(float *)(param_1 + 0x34);
	*(float *)(param_1 + 0x2c) = 2.0f - *(float *)(param_1 + 0x30);
}

// FUNCTION: SADX 0x00609ba0
void FUN_00609ba0(struct taskwk *param_1, struct enemywk *param_2)
{
	struct taskwk *local_8g;
	float local_cg;

	local_8g = DAT_05baf368[0];
	local_cg = (local_8g->pos.x - param_1->pos.x) * (local_8g->pos.x - param_1->pos.x) +
	           (local_8g->pos.z - param_1->pos.z) * (local_8g->pos.z - param_1->pos.z);
	if (local_cg < param_2->radius * param_2->radius)
	{
		if (param_1->mode != -1)
		{
			param_1->mode = 1;
			param_1->smode = 0;
		}
		dsPlay_oneshot(0x36d, 0, 0, 0);
	}
	SnowmanRectifyPosition(param_1, param_2);
}

// FUNCTION: SADX 0x00609c40
void SnowmanRectifyPosition(struct taskwk *twp, struct enemywk *ewp)
{
	while (twp->timer.w[0] - 0x100 > 0)
	{
		SnowmanBackSmoke(twp, ewp);
		twp->timer.w[0] -= 0x100;
	}
	while (twp->timer.w[1] - 0x100 > 0)
	{
		SnowmanFootSmoke(twp, ewp);
		twp->timer.w[1] -= 0x100;
	}
	EnemyCheckGroundCollision(twp, ewp);
	if ((ewp->flag & 0x40) != 0 || (ewp->flag & 0x80) != 0)
	{
		if (twp->mode != -1)
		{
			twp->mode = 4;
			twp->smode = 0;
		}
		EnemyTurnToHome(twp, ewp);
	}
	EnemyPreservePreviousPosition(twp, ewp);
}

// STUB: SADX 0x00609d20
void FUN_00609d20(struct taskwk *param_1, struct enemywk *param_2)
{
}

// FUNCTION: SADX 0x00609e40
void FUN_00609e40(int param_1, int param_2)
{
	*(int *)(param_2 + 0x1b4) += *(int *)(param_2 + 0x1ac);
	*(float *)(param_2 + 0x38) = njSin(*(int *)(param_2 + 0x1b4)) * *(float *)(param_1 + 0x10);
}

// STUB: SADX 0x00609e80
void snowmanChase(struct taskwk *twp, struct enemywk *ewp)
{
}

// FUNCTION: SADX 0x0060a0c0
void FUN_0060a0c0(struct taskwk *param_1, struct enemywk *param_2)
{
	int local_8;

	param_1->flag &= 0xfffffeff;
	local_8 = *(int *)((char *)param_1 + 0x18);
	*(int *)((char *)param_1 + 0x18) = *(int *)((char *)param_2 + 0x1b0);
	if (EnemySearchPlayer(param_1, param_2) == 1)
	{
		param_1->flag |= 0x100;
	}
	*(int *)((char *)param_1 + 0x18) = local_8;
}

// STUB: SADX 0x0060a130
void SnowmanMove(struct taskwk *twp, struct enemywk *ewp)
{
}

// FUNCTION: SADX 0x0060a2c0
void SnowmanTurnToAim(struct taskwk *twp, struct enemywk *ewp)
{
	long local_8;

	ewp->sub_angle[0] = AdjustAngle(ewp->sub_angle[0], ewp->aim_angle, ewp->angx_spd);
	local_8 = ewp->sub_angle[0] - *(long *)((char *)twp + 0x18);
	local_8 &= 0xffff;
	if (local_8 > 0x8000)
	{
		local_8 -= 0x10000;
	}
	if (local_8 > 0x2000)
	{
		local_8 = 0x2000;
	}
	else if (local_8 < -0x2000)
	{
		local_8 = -0x2000;
	}
	ewp->sub_angle[0] = *(long *)((char *)twp + 0x18) + local_8;
}

// STUB: SADX 0x0060a360
void FUN_0060a360(struct taskwk *param_1, struct enemywk *param_2)
{
}

// STUB: SADX 0x0060a3d0
void snowmanWalk(struct taskwk *twp, struct enemywk *ewp)
{
}

// FUNCTION: SADX 0x0060a5e0
void FUN_0060a5e0(struct taskwk *param_1, struct enemywk *param_2)
{
	*(int *)((char *)param_2 + 0x1b0) += *(int *)((char *)param_2 + 0x1a4);
	if (*(int *)((char *)param_2 + 0x1a4) > 0)
	{
		if (*(int *)((char *)param_2 + 0x1b0) >= *(int *)((char *)param_1 + 0x18) + 0x2000)
		{
			*(int *)((char *)param_2 + 0x1b0) = *(int *)((char *)param_1 + 0x18) + 0x2000;
			*(int *)((char *)param_2 + 0x1a4) = *(int *)((char *)param_2 + 0x1a4) * -1;
		}
	}
	else
	{
		if (*(int *)((char *)param_2 + 0x1b0) <= *(int *)((char *)param_1 + 0x18) - 0x2000)
		{
			*(int *)((char *)param_2 + 0x1b0) = *(int *)((char *)param_1 + 0x18) - 0x2000;
			*(int *)((char *)param_2 + 0x1a4) = *(int *)((char *)param_2 + 0x1a4) * -1;
		}
	}
}

// STUB: SADX 0x0060a690
void snowmanTurn(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x0060a7c0
void FUN_0060a7c0(char *param_1, int param_2)
{
}

// STUB: SADX 0x0060a800
void snowmanBreathe(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x0060aa40
void snowmanDestroy(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x0060ad20
void DisplaySnowman(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x0060b0a0
void SnowMobile(struct task *tp)
{
}

// STUB: SADX 0x0060b190
void FUN_0060b190(struct task *param_1)
{
}

// FUNCTION: SADX 0x0060b2f0
void FUN_0060b2f0(struct taskwk *param_1, struct enemywk *param_2)
{
	unsigned short *local_8;

	local_8 = (unsigned short *)*(int *)(*(int *)((char *)param_1 + 0x38) + 0xa4);
	if ((param_1->flag & 4) != 0)
	{
		if (*(signed char *)param_1 != -1)
		{
			*(char *)param_1 = 2;
			*(char *)((char *)param_1 + 1) = 0;
		}
		*(char *)((char *)param_1 + 3) = 0;
		*(float *)((char *)param_1 + 0x34) = 0.35f;
		*(float *)((char *)param_2 + 4) = 0.0f;
		*(float *)((char *)param_2 + 0xc) = 0.0f;
		if (*local_8 == 0)
		{
			SetVelocityP(0, 0.0f, 2.0f, 0.0f);
		}
	}
}

// STUB: SADX 0x0060b380
void snowfaceEscape(struct taskwk *twp, struct enemywk *ewp)
{
}

// FUNCTION: SADX 0x0060b590
void SnowfaceRectifyPosition(struct taskwk *twp, struct enemywk *ewp)
{
	EnemyCheckGroundCollision(twp, ewp);
	if ((ewp->flag & 0x40) != 0)
	{
		ewp->velo.x = ewp->velo.x * -1.0;
		ewp->velo.z = ewp->velo.z * -1.0;
		EnemyTurnToPlayer(twp, ewp, 0);
	}
	else if ((ewp->flag & 0x80) != 0)
	{
		EnemyTurnToPlayer(twp, ewp, 0);
	}
	EnemyPreservePreviousPosition(twp, ewp);
}

// STUB: SADX 0x0060b620
void snowfaceRunaway(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x0060b8a0
void SnowfaceAction(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x0060bb60
void SnowfaceRegular(struct task *tp)
{
}

// STUB: SADX 0x0060bbf0
void SnowfaceDisplayer(struct task *tp)
{
}

// STUB: SADX 0x0060bde0
void DisplaySnowface(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x0060bef0
void DisplaySnowMobile(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x0060c0f0
void SnowmanOnEdit(struct task *tp)
{
}

// STUB: SADX 0x0060c200
void DrawSnowmanRange(struct NJS_POINT3 *pos, float radius)
{
}

#pragma optimize("", off)
// STUB: SADX 0x0060c300
void SnowmanBackSmoke(struct taskwk *twp, struct enemywk *ewp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x0060c4e0
void create_whitesmoke(struct particle_info *info, struct NJS_POINT3 *pos, struct NJS_POINT3 *spd, float scl)
{
	struct sp_task *local_8g;
	int local_cj;
	float local_10m;
	int local_14;
	float local_18g;

	local_8g = SpCreateTask(particle_pom.link, EffectPom);
	if (local_8g != NULL)
	{
		local_cj = rand();
		local_10m = (float)(local_cj / 32768.0);
		local_8g->frame = local_10m * 2.0;
		local_8g->scl = scl;
		local_14 = rand();
		local_18g = (float)(local_14 / 32768.0);
		local_8g->ang = (int)(local_18g * 65536.0) - 0x8000;
		local_8g->work[0].ptr = info;
		local_8g->argb = info->argb;
		njCalcVector(0, spd, &local_8g->spd);
		njCalcPoint(0, pos, &local_8g->pos);
	}
}

// STUB: SADX 0x0060c5c0
void EffectPom(struct sp_task *tp, struct sp_link *lp)
{
}

#pragma optimize("", off)
// STUB: SADX 0x0060c7c0
void SnowmanFootSmoke(struct taskwk *twp, struct enemywk *ewp)
{
}
#pragma optimize("", on)

// STUB: SADX 0x0060c9d0
void SnowmanBreathe(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x0060cb30
void SnowfaceLeftFootSmoke(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x0060cbf0
void SnowfaceRightFootSmoke(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x0060ccc0
void create_freeze_colli(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x0060cdd0
void colli_freeze(struct task *tp)
{
}
