#include "decls.h"
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

// STUB: SADX 0x00529090
void FUN_00529090(int param_1, int param_2, int param_3)
{
}

// STUB: SADX 0x005290f0
int FUN_005290f0(struct taskwk *tpw, int param_2, struct taskwk *tpw2)
{
	return (int)0;
}

// STUB: SADX 0x005293e0
long FUN_005293e0(char *twp, char *param_2, char *param_3)
{
	return (long)0;
}

// STUB: SADX 0x0052aea0
long FUN_0052aea0(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	return (long)0;
}

// STUB: SADX 0x0052bb80
long KnucklesCheckBeInTheAir(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	return (long)0;
}

// STUB: SADX 0x0052bc30
long FUN_0052bc30(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	return (long)0;
}

// STUB: SADX 0x0052bcd0
long FUN_0052bcd0(struct taskwk *twp, int param_2, struct taskwk *param_3)
{
	return (long)0;
}

// STUB: SADX 0x0052bd30
long KnucklesCheckStartPunch(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	return (long)0;
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

// STUB: SADX 0x0052dd10
void KnucklesLaterSE(struct task *tp)
{
}

// STUB: SADX 0x0052dd70
float FUN_0052dd70()
{
	return (float)0;
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

// STUB: SADX 0x0052ea20
void KnucklesTouchWallInit(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
}

// STUB: SADX 0x0052ed90
void Knuckles_KakeraGame(struct task *tp)
{
}

// STUB: SADX 0x0052ee30
void Knuckles_KakeraGamePutRadar1(struct task *tp)
{
}

// STUB: SADX 0x0052f7a0
void Knuckles_KakeraGameFinish(struct task *tp)
{
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
