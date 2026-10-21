#include "decls.h"
long EnemyTurnToPlayer(struct taskwk *twp, struct enemywk *ewp, unsigned char pnum);
void SnowmanBackSmoke(struct taskwk *twp, struct enemywk *ewp);
void SnowmanFootSmoke(struct taskwk *twp, struct enemywk *ewp);
void EnemyCheckGroundCollision(struct taskwk *twp, struct enemywk *ewp);
long EnemyTurnToHome(struct taskwk *twp, struct enemywk *ewp);
void EnemyPreservePreviousPosition(struct taskwk *twp, struct enemywk *ewp);

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

// STUB: SADX 0x00609ba0
void FUN_00609ba0(struct taskwk *param_1, struct enemywk *param_2)
{
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

// STUB: SADX 0x0060a2c0
void SnowmanTurnToAim(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x0060a360
void FUN_0060a360(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x0060a5e0
void FUN_0060a5e0(struct taskwk *param_1, struct enemywk *param_2)
{
}

// STUB: SADX 0x0060a7c0
void FUN_0060a7c0(char *param_1)
{
}

// STUB: SADX 0x0060b0a0
void SnowMobile(struct task *tp)
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

// STUB: SADX 0x0060bb60
void SnowfaceRegular(struct task *tp)
{
}

// STUB: SADX 0x0060c200
void DrawSnowmanRange(struct NJS_POINT3 *pos, float radius)
{
}

// STUB: SADX 0x0060c4e0
void create_whitesmoke(struct particle_info *info, struct NJS_POINT3 *pos, struct NJS_POINT3 *spd, float scl)
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

// STUB: SADX 0x0060cdd0
void colli_freeze(struct task *tp)
{
}
