#include "decls.h"
long CheckRangeOut(struct task *pTask);
static void dispTrackBeam(struct task *pTask);
void init();
void FUN_006dfc40();
extern int DAT_060bd030;
extern int DAT_060bd034;
extern int DAT_060bd114;
extern float DAT_060bd118;
extern int DAT_060bcfe0;
extern int DAT_060bcff0[16];
extern int DAT_060bd12c;
extern int DAT_060bd110;
extern int DAT_060bd128;
long chkColli();
extern int DAT_060bd148;
extern int DAT_060bcfdc;

// FUNCTION: SADX 0x006df690
void RoboBeam_Init(struct NJS_POINT3 *pPos, struct NJS_POINT3 *pVec, long *pAng)
{
	int var1;
	DAT_060bd118 = 0.0f;
	DAT_060bd148 = 0;
	DAT_060bd12c = 0;
	DAT_060bd110 = 0;
	DAT_060bcfdc = (int)pPos;
	DAT_060bd114 = (int)pVec;
	DAT_060bcfe0 = (int)pAng;
	for (var1 = 0; var1 < 16; var1++)
		DAT_060bcff0[var1] = 0xc0c000;
	DAT_060bd030 = 0xc0c000;
	DAT_060bd034 = 0xc0c000;
}

// FUNCTION: SADX 0x006df730
void RoboBeam_Exit()
{
	DAT_060bcfdc = 0;
}

// FUNCTION: SADX 0x006df740
void RoboBeam_SetMode(enum ROBO_BEAM_MODE nMode)
{
	DAT_060bd148 = nMode;
}

// FUNCTION: SADX 0x006df8d0
long RoboBeam_ChkLockOn()
{
	if ((DAT_060bd128 & 1) != 0)
	{
		return 1;
	}
	if ((DAT_060bd128 & 2) == 0)
	{
		if (chkColli() != 0)
		{
			DAT_060bd128 |= 1;
			return 1;
		}
	}
	return 0;
}

// STUB: SADX 0x006df900
void init()
{
}

// FUNCTION: SADX 0x006dfc40
void FUN_006dfc40()
{
	DAT_060bd12c++;
	if (DAT_060bd12c >= 9)
	{
		DAT_060bd12c = 0;
	}
	DAT_060bd110++;
	if (DAT_060bd110 >= 8)
	{
		DAT_060bd110 = 8;
	}
}

#pragma optimize("", off)
// STUB: SADX 0x006dfdf0
static void dispTrackBeam(struct task *pTask)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x006dfef0
void execTrackBeam(struct task *pTask)
{
	struct taskwk *var1 = pTask->twp;

	var1->wtimer++;
	if (var1->wtimer >= 0x2d)
	{
		FreeTask(pTask);
		return;
	}
	dispTrackBeam(pTask);
	CheckRangeOut(pTask);
}

// STUB: SADX 0x006e0100
void FUN_006e0100()
{
}
