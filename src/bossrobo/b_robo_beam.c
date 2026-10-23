#include "decls.h"
extern int DAT_060bd12c;
extern int DAT_060bd110;
extern int DAT_060bd128;
long chkColli();
extern int DAT_060bd148;
extern int DAT_060bcfdc;

// STUB: SADX 0x006df690
void RoboBeam_Init(struct NJS_POINT3 *pPos, struct NJS_POINT3 *pVec, long *pAng)
{
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
