#include "decls.h"
void ReSetMiStatus(unsigned char u8MissionNo, unsigned char u8Flag);
void SetTaskMissionClear(struct task *tp);
extern void MissionClearDest(struct task *);
void FUN_004998c0();
extern void *DAT_05b37394;
extern void *DAT_05b37390;
extern unsigned char DAT_05b3739a;
void ReleaseMiMessage();

// STUB: SADX 0x00499ab0
void ReSetMiStatus(unsigned char u8MissionNo, unsigned char u8Flag)
{
}

// STUB: SADX 0x00499b10
unsigned char isRangeMission(struct NJS_POINT3 *src, struct NJS_POINT3 *trg, float f32Range)
{
	return (unsigned char)0;
}

// FUNCTION: SADX 0x00499e20
void MissionClearDest(struct task *tp)
{
	ReleaseMiMessage();
	DAT_05b3739a = 0;
}

// STUB: SADX 0x0049a0d0
struct task *GetTargetTask(struct task *tp, unsigned short u16ObjNo)
{
	return (struct task *)0;
}

// STUB: SADX 0x0049a110
unsigned char IsMissionStatus(void *ptr)
{
	return (unsigned char)0;
}

// STUB: SADX 0x0049a130
unsigned char IsMissionDispFlag(struct task *tp)
{
	return (unsigned char)0;
}

// STUB: SADX 0x0049a170
unsigned char IsMissionAppear(struct task *tp)
{
	return (unsigned char)0;
}

// STUB: SADX 0x0049a230
void InitMissionObject()
{
}

// FUNCTION: SADX 0x0049a260
void ReleaseMissionObject()
{
	FUN_004998c0();
	if (DAT_05b37394 != 0)
	{
		syFree(DAT_05b37394);
		DAT_05b37394 = 0;
	}
	if (DAT_05b37390 != 0)
	{
		syFree(DAT_05b37390);
		DAT_05b37390 = 0;
	}
	ReleaseMissionCamera();
}

// STUB: SADX 0x0049a2b0
void SetTaskMissionClear(struct task *tp)
{
}

// STUB: SADX 0x0049a330
void CheckMissionClear_GetObj(struct task *tp)
{
}

// STUB: SADX 0x0049a420
void CheckMissionClear_BreakObj(struct task *tp)
{
}
