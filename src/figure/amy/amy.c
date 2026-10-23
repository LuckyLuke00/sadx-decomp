#include "decls.h"
struct task *CreateElementalTask(unsigned short im, long level, void (*exec)(struct task *));
extern short DAT_05b9d724;
extern short DAT_05b9d744;
void FUN_0051b800(struct taskwk *param_1, struct motionwk2 *param_2, struct playerwk *param_3);

// FUNCTION: SADX 0x0051afc0
void AmyDestruct(struct task *tp)
{
	struct taskwk *local_8;
	local_8 = tp->twp;
	PDestruct(local_8->counter.b[0]);
	ReleasePlayersTexture(5);
}

// STUB: SADX 0x0051b730
long FUN_0051b730(struct taskwk *twp, int *out1, float *out2)
{
	return (long)0;
}

// STUB: SADX 0x0051b7b0
void FUN_0051b7b0(int param_1)
{
}

// FUNCTION: SADX 0x0051b800
void FUN_0051b800(struct taskwk *param_1, struct motionwk2 *param_2, struct playerwk *param_3)
{
	param_1->mode = 1;
	param_3->waittimer = 0;
	AmyChangeWaitingMotion(param_1, param_2, param_3);
}

// STUB: SADX 0x0051c960
long FUN_0051c960(struct taskwk *twp, int param_2, int param_3)
{
	return (long)0;
}

// STUB: SADX 0x0051c9d0
long AmyCheckStartHandle(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	return (long)0;
}

// STUB: SADX 0x0051ca90
long FUN_0051ca90(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *plp)
{
	return (long)0;
}

// STUB: SADX 0x0051ce40
long AmyBalanceCheckBadStatus(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	return (long)0;
}

// STUB: SADX 0x0051e350
long FUN_0051e350(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	return (long)0;
}

// STUB: SADX 0x0051f1f0
long FUN_0051f1f0(struct taskwk *twp, int param_2, int param_3)
{
	return (long)0;
}

// STUB: SADX 0x0051f2e0
long AmyCheckStartDrumCan(struct taskwk *twp, struct playerwk *pwp)
{
	return (long)0;
}

// STUB: SADX 0x0051f370
long AmyCheckEndDrumCan(struct taskwk *twp, struct playerwk *pwp)
{
	return (long)0;
}

// STUB: SADX 0x0051f990
void AmyPutHammerWave(struct task *tp)
{
}

// STUB: SADX 0x0051fa50
void AmyGetFrfrRotation(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
}

// STUB: SADX 0x0051ff70
void AmyHeadSpikesShakeEnd(struct task *tp)
{
}

// STUB: SADX 0x005205f0
void AmySkirtShapeEnd(struct task *tp)
{
}

// STUB: SADX 0x00520bd0
void AmyFaceMotion(struct task *tp)
{
}

// STUB: SADX 0x00520c50
long AmyDrumCanPutOnCheck(long plnmb)
{
	return (long)0;
}

// STUB: SADX 0x00520ca0
long Amy_Status(long plnmb)
{
	return (long)0;
}

// STUB: SADX 0x00520f10
void AmyERobApperChecker(struct task *tp)
{
}

// FUNCTION: SADX 0x005210f0
void FUN_005210f0(void)
{
	if (((DAT_05b9d724 << 8) | DAT_05b9d744) == 0xc00)
		CreateElementalTask(2, 3, AmyBalanceGameStartChecker);
}

// STUB: SADX 0x00521550
long AmyForEventHammerScaleIm(unsigned char playernmb, float scale)
{
	return (long)0;
}

// FUNCTION: SADX 0x005215c0
long AmyHandleEntry()
{
	struct playerwk *local_8;

	local_8 = GetPlayerWorkPointer(0);
	if (local_8 == NULL)
		return 0;
	*(char *)((char *)local_8 + 0x82) |= 1;
	return 1;
}

// FUNCTION: SADX 0x00521600
long AmyBlindEntry()
{
	struct playerwk *local_8;

	local_8 = GetPlayerWorkPointer(0);
	if (local_8 == 0)
		return 0;
	local_8->free.sb[6] |= 4;
	return 1;
}

// STUB: SADX 0x00521640
void FUN_00521640(struct task *ptp, struct taskwk *twp, struct motionwk *mwp)
{
}

// FUNCTION: SADX 0x00521a60
long IsAmyWhistling(struct taskwk *twp)
{
	if (twp->mode == 0x34)
		return 1;
	return 0;
}

// FUNCTION: SADX 0x00521a80
long IsAmyPutting(struct taskwk *twp)
{
	if (twp->mode == 0x18)
		return 1;
	return 0;
}

// FUNCTION: SADX 0x00521aa0
long IsAmyShakingTree(struct taskwk *twp)
{
	if (twp->mode == 0x24)
		return 1;
	return 0;
}
