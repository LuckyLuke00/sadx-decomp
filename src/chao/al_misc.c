#include "decls.h"

// STUB: SADX 0x00437c40
float ___njUnitVector(struct NJS_POINT3 *p)
{
	return (float)0;
}

// STUB: SADX 0x00438030
void AL_DrawRectangle2(int x1, int y1, int x2, int y2, unsigned long color, float depth)
{
}

// FUNCTION: SADX 0x00438090
float AL_Dist2FromAim(struct task *tp)
{
	struct taskwk *var1;
	struct motionwk *var2;

	var1 = tp->twp;
	var2 = tp->mwp;
	return (*(float *)((char *)var2 + 0x5c) - var1->pos.z) * (*(float *)((char *)var2 + 0x5c) - var1->pos.z) + (*(float *)((char *)var2 + 0x54) - var1->pos.x) * (*(float *)((char *)var2 + 0x54) - var1->pos.x);
}

// STUB: SADX 0x004380c0
long AL_IsGroundStop(struct task *tp)
{
	return (long)0;
}

// FUNCTION: SADX 0x00438390
long AL_IsOnScreen2(struct task *tp, float radius, float OffsetY)
{
	return AL_IsOnScreen3(tp, radius, radius, OffsetY);
}

#pragma optimize("", off)
// STUB: SADX 0x004383c0
long AL_CalcTaskAngle(struct task *pMyTask, struct task *pTargetTask)
{
	return (long)0;
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00438400
long AL_TurnToTask(struct task *pMyTask, struct task *pTargetTask, long RotSpd)
{
	if ((pMyTask != NULL) && (pTargetTask != NULL))
	{
		struct taskwk *var1;
		struct motionwk *var2;
		long var3;

		var1 = pMyTask->twp;
		var2 = pMyTask->mwp;
		var3 = AL_CalcTaskAngle(pMyTask, pTargetTask);
		var2->ang_aim.y = var3;
		var3 = AdjustAngle(var1->ang.y, var3, RotSpd);
		var1->ang.y = var3;
		return DiffAngle(var2->ang_aim.y, var3);
	}
	return 0;
}

// FUNCTION: SADX 0x00438450
float AL_CalcDistFromTask(struct task *pMyTask, struct task *pTargetTask)
{
	if ((pMyTask != NULL) && (pTargetTask != NULL))
	{
		struct taskwk *var1;
		struct taskwk *var2;

		var1 = pMyTask->twp;
		var2 = pTargetTask->twp;
		return njSqrt((var1->pos.x - var2->pos.x) * (var1->pos.x - var2->pos.x) + (var1->pos.y - var2->pos.y) * (var1->pos.y - var2->pos.y) + (var1->pos.z - var2->pos.z) * (var1->pos.z - var2->pos.z));
	}
	return -1.0f;
}

// FUNCTION: SADX 0x004384b0
void AL_ForwardAcc(struct task *tp, float acc)
{
	struct taskwk *var1;
	struct motionwk *var2;

	var1 = tp->twp;
	var2 = tp->mwp;
	var2->acc.x = njSin(var1->ang.y) * acc;
	var2->acc.z = njCos(var1->ang.y) * acc;
}

// FUNCTION: SADX 0x004384f0
void AL_ForwardSpd(struct task *tp, float spd)
{
	struct taskwk *var1;

	var1 = tp->twp;
	var1->pos.x = njSin(var1->ang.y) * spd + var1->pos.x;
	var1->pos.z = njCos(var1->ang.y) * spd + var1->pos.z;
}

// STUB: SADX 0x00438530
void AL_Brake(struct task *tp, float brake)
{
}

// FUNCTION: SADX 0x00438570
struct task *AL_IsHitKindWithNum(struct task *tp, long info_num, unsigned char kind)
{
	CCL_ClearSearch();
	return CCL_IsHitKindWithNum2(tp->twp, info_num, kind);
}
