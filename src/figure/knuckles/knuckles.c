#include "decls.h"
void FUN_00528530(struct taskwk *param_1, struct motionwk2 *param_2, struct playerwk *param_3);
void FUN_00528530(struct taskwk *param_1, struct motionwk2 *param_2, struct playerwk *param_3);
long FUN_0052aea0(struct taskwk *param_1, struct motionwk2 *param_2, struct playerwk *param_3);
extern unsigned short DAT_05cc63b6;
extern unsigned short DAT_05cc63c6;
extern unsigned short DAT_05cc63d6;
extern "C" int rand(void);
void FUN_00528530(struct taskwk *param_1, struct motionwk2 *param_2, struct playerwk *param_3);
extern long action_button;
void Knuckles_KakeraGamePutRadar0(struct taskwk *twp, long cnt, long level);
void FUN_00528530(struct taskwk *param_1, struct motionwk2 *param_2, struct playerwk *param_3);
long FUN_0052aea0(struct taskwk *param_1, struct motionwk2 *param_2, struct playerwk *param_3);
void FUN_00528530(struct taskwk *param_1, struct motionwk2 *param_2, struct playerwk *param_3);
long FUN_0052aea0(struct taskwk *param_1, struct motionwk2 *param_2, struct playerwk *param_3);
long FUN_0052aea0(struct taskwk *param_1, struct motionwk2 *param_2, struct playerwk *param_3);
extern int DAT_05cc603c;
extern int DAT_05cc6040;
extern int DAT_06274af0;
void FUN_00528530(struct taskwk *param_1, struct motionwk2 *param_2, struct playerwk *param_3);
extern int DAT_06274afc;
extern int DAT_05cc62c0;
extern int DAT_05cc62d0;

// FUNCTION: SADX 0x00527600
void KnucklesDestruct(struct task *tp)
{
	struct taskwk *local_8;
	local_8 = tp->twp;
	PDestruct((long)local_8->counter.b[0]);
	ReleasePlayersTexture(3);
}

// FUNCTION: SADX 0x00528530
void FUN_00528530(struct taskwk *param_1, struct motionwk2 *param_2, struct playerwk *param_3)
{
	param_1->mode = 1;
	param_3->waittimer = 0;
	KnucklesChangeWaitingMotion(param_1, param_2, param_3);
}

// STUB: SADX 0x00528810
void KnucklesChangeRunningMotion(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
}

// STUB: SADX 0x00529090
void FUN_00529090(int param_1, int param_2, int param_3)
{
}

// STUB: SADX 0x005290f0
int FUN_005290f0(struct taskwk *tpw, int param_2, struct taskwk *tpw2)
{
	return (int)0;
}

// FUNCTION: SADX 0x005293e0
long FUN_005293e0(struct taskwk *param_1, char *param_2, struct playerwk *param_3)
{
	if (DAT_05b932e8[param_1->counter.b[0]].press & action_button)
	{
		param_1->mode = 9;
		param_3->spd.z = 0.0f;
		param_3->spd.y = 0.0f;
		param_3->spd.x = 0.0f;
		*(short *)((char *)param_3 + 0x124) = 0x13;
		param_3->work.f = 0.0f;
		param_1->flag &= ~0x500;
		return 1;
	}
	else
	{
		return 0;
	}
}

// STUB: SADX 0x00529450
long KnucklesCheckKickWall(struct taskwk *twp, struct playerwk *pwp)
{
	return (long)0;
}

// FUNCTION: SADX 0x0052aea0
long FUN_0052aea0(struct taskwk *param_1, struct motionwk2 *param_2, struct playerwk *param_3)
{
	long local_8;

	PAdjustHoldingPosition(param_1, param_2, param_3);
	if (param_3->mj.nframe >= 6.0f)
	{
		local_8 = PCheckHoldObject(param_1);
		if (local_8)
		{
			switch (PCheckColliAngle(param_1, param_2))
			{
			case 4:
				if ((local_8 & 0x200) != 0)
				{
					param_1->mode = 0x36;
					return 1;
				}
				break;
			}
			FUN_00528530(param_1, param_2, param_3);
		}
	}
	return 0;
}

// STUB: SADX 0x0052af40
long KnucklesCheckHoldObject(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	return (long)0;
}

// STUB: SADX 0x0052b080
long KnucklesCheckPickObject(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	return (long)0;
}

// STUB: SADX 0x0052b190
long KnucklesCheckThrowObject(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	return (long)0;
}

// FUNCTION: SADX 0x0052bb80
long KnucklesCheckBeInTheAir(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	if (((twp->flag & 3) == 0))
	{
		if ((twp->flag & 0x100) != 0)
		{
			twp->mode = 6;
			return 1;
		}
		else if ((0x800 & twp->flag) != 0)
		{
			if ((PCheckHoldObject(twp) & 0x200) != 0)
			{
				twp->mode = 0x22;
				*(unsigned short *)((char *)pwp + 0x124) = 0x5e;
				return 1;
			}
			SonicThrowTheObjectOut(twp, mwp, pwp);
		}
		twp->mode = 9;
		*(unsigned short *)((char *)pwp + 0x124) = 0x13;
		return 1;
	}
	else
	{
		return 0;
	}
}

// FUNCTION: SADX 0x0052bc30
long FUN_0052bc30(struct taskwk *param_1, struct motionwk2 *param_2, struct playerwk *param_3)
{
	if ((PCheckPower(param_1, 0, 0) == 0) && (param_3->spd.x == 0.0f))
	{
		if ((param_1->flag & 0x800) != 0)
		{
			if ((PCheckHoldObject(param_1) & 0xc00) != 0)
			{
				param_1->mode = 0x1e;
				*(short *)((char *)param_3 + 0x124) = 0x5b;
			}
			else
			{
				param_1->mode = 0x1d;
				*(short *)((char *)param_3 + 0x124) = 0x4a;
			}
		}
		else
		{
			FUN_00528530(param_1, param_2, param_3);
		}
		return 1;
	}
	else
	{
		return 0;
	}
}

// FUNCTION: SADX 0x0052bcd0
long FUN_0052bcd0(struct taskwk *param_1, int param_2, struct taskwk *param_3)
{
	if (DAT_05b932e8[param_1->counter.b[0]].press & action_button)
	{
		param_1->mode = 4;
		*(short *)((char *)param_3 + 0x124) = 0xf;
		param_1->flag |= 0x500;
		*(float *)((char *)param_3 + 0x0) = *(float *)((char *)param_3 + 0x38);
		return 1;
	}
	else
	{
		return 0;
	}
}

// FUNCTION: SADX 0x0052bd30
long KnucklesCheckStartPunch(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	if ((DAT_05b932e8[twp->counter.b[0]].press & action_button) != 0)
	{
		DAT_05cc63b6 = 0;
		DAT_05cc63c6 = 0;
		DAT_05cc63d6 = 0;
		twp->mode = 0x1a;
		*(short *)((char *)pwp + 0x124) = 0x36;
		*(short *)((char *)pwp + 0x86) = 0;
		dsStop_num(0x318);
		return 1;
	}
	return 0;
}

// STUB: SADX 0x0052bda0
long FUN_0052bda0(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	return (long)0;
}

// FUNCTION: SADX 0x0052c320
void KnucklesHeadSpikesShakeEnd(struct task *tp)
{
	*(int *)(*(int *)(DAT_06274af0 + 0xc4) + 4) = DAT_05cc603c;
	*(int *)(*(int *)(DAT_06274af0 + 0xc8) + 4) = DAT_05cc6040;
}

// FUNCTION: SADX 0x0052c350
void KnucklesChargeEffect(struct task *tp)
{
	*(void (**)(struct task *))(void *)(&tp->dest) = (void (*)(struct task *))FUN_005b5aa0;
	tp->exec = KnucklesChargeEffectExe;
}

// STUB: SADX 0x0052c370
void KnucklesChargeEffectExe(struct task *tp)
{
}

// STUB: SADX 0x0052c440
void FUN_0052c440(int param_1, int param_2, int param_3)
{
}

// STUB: SADX 0x0052d120
long KnuckCheckOnWall(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	return (long)0;
}

// STUB: SADX 0x0052d2d0
void FUN_0052d2d0(struct task *tp, int param_2)
{
}

// STUB: SADX 0x0052dd10
void KnucklesLaterSE(struct task *tp)
{
}

// FUNCTION: SADX 0x0052dd70
float FUN_0052dd70()
{
	int local_8g;
	float local_cg;
	local_8g = rand();
	local_cg = local_8g / 32768.0;
	return local_cg;
}

// FUNCTION: SADX 0x0052e120
int FUN_0052e120(unsigned char param_1, const int *param_2)
{
	struct task *local_cg;
	struct motionwk *local_8g;

	local_cg = CreateElementalTask(2, 2, KnucklesDirectAhead);
	if (local_cg != (struct task *)0x0)
	{
		local_8g = (struct motionwk *)MAlloc(0x88);
		if (local_8g == (struct motionwk *)0x0)
		{
			FreeTask(local_cg);
			return 0;
		}
		*(struct motionwk **)((char *)local_cg + 0x24) = local_8g;
		local_cg->twp->counter.b[0] = param_1;
		*(int *)((char *)local_8g + 0x58) = param_2[0];
		*(int *)((char *)local_8g + 0x5c) = param_2[1];
		*(int *)((char *)local_8g + 0x60) = param_2[2];
	}
	else
	{
		return 0;
	}
	return 1;
}

// STUB: SADX 0x0052e6c0
void KnucklesDirectAheadEnd(struct task *tp)
{
}

// STUB: SADX 0x0052e760
long Knuckles_Status(long plnmb)
{
	return (long)0;
}

// STUB: SADX 0x0052e890
struct taskwk *KnucklesGetNearEnemyTWP(struct taskwk *twp)
{
	return (struct taskwk *)0;
}

// FUNCTION: SADX 0x0052ea20
void KnucklesTouchWallInit(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	twp->flag |= 1;
	pwp->spd.x = 0.0f;
	pwp->spd.z = 0.0f;
	twp->ang.x = pwp->cstsp->angx;
	*(int *)((char *)twp + 0x1c) = *(int *)((char *)pwp->cstsp + 0x38);
	twp->pos.x = pwp->cstsp->onpoly.x;
	twp->pos.y = pwp->cstsp->onpoly.y;
	twp->pos.z = pwp->cstsp->onpoly.z;
	twp->flag &= ~0x400;
	twp->mode = 0x18;
	*(short *)((char *)pwp + 0x124) = 0x34;
	dsStop_num(0x30c);
}

// STUB: SADX 0x0052ead0
long Knuckles_KakeraGameInit()
{
	return (long)0;
}

// STUB: SADX 0x0052ed90
void Knuckles_KakeraGame(struct task *tp)
{
}

// STUB: SADX 0x0052ee30
void Knuckles_KakeraGamePutRadar1(struct task *tp)
{
}

// STUB: SADX 0x0052ef10
void Knuckles_KakeraGamePutRadar1C(struct task *tp)
{
}

// STUB: SADX 0x0052f670
void Knuckles_KakeraGamePutRadar0(struct taskwk *twp, long cnt, long level)
{
}

// STUB: SADX 0x0052f7a0
void Knuckles_KakeraGameFinish(struct task *tp)
{
}

// STUB: SADX 0x0052f830
long Knuckles_KakeraGame_GetNearEmePos(struct NJS_POINT3 *chkpos, struct NJS_POINT3 *emepos, float *emedst)
{
	return (long)0;
}

// STUB: SADX 0x0052f9b0
long Knuckles_KakeraGame_InThereGroundEme(struct NJS_POINT3 *chkpos)
{
	return (long)0;
}

// STUB: SADX 0x0052faa0
long Knuckles_KakeraGame_Set_CheckEme(long emeid, struct NJS_POINT3 *emepos)
{
	return (long)0;
}

// STUB: SADX 0x0052feb0
void Knuckles_KakeraGamePutRadar0C(struct task *tp)
{
}

// STUB: SADX 0x0052ff80
long Knuckles_KakeraGame_Set_ContPos(long emeid, struct NJS_POINT3 *contpos)
{
	return (long)0;
}

// STUB: SADX 0x00530040
void Knuckles_KakeraPrintLapTime(struct task *tp)
{
}

// FUNCTION: SADX 0x00530110
long IsKnucklesWhistling(struct taskwk *twp)
{
	if (twp->mode == 0x38)
		return 1;
	return 0;
}

// FUNCTION: SADX 0x00530130
long IsKnucklesShakingTree(struct taskwk *twp)
{
	if (twp->mode == 0x28)
		return 1;
	return 0;
}

// FUNCTION: SADX 0x00530150
void _knucklesmot_init()
{
	DAT_05cc62c0 = *(int *)(DAT_06274afc + 0xa0);
	DAT_05cc62d0 = *(int *)(DAT_06274afc + 0xa4);
}
