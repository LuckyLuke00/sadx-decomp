#include "decls.h"
extern unsigned char DAT_05cbef64;

// FUNCTION: SADX 0x00847180
void ObjectSkydeck_c_cyl1_End(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (var1->counter.ptr != 0)
	{
		WithdrawCollisionEntry(tp, (struct obj *)var1->counter.ptr);
		ReleaseMobileLandObject((struct obj *)var1->counter.ptr);
	}
	if (var1->value.ptr != 0)
	{
		Free(var1->value.ptr);
	}
	FreeTaskC(tp);
}

// FUNCTION: SADX 0x00847310
void ObjectSkydeck_c_cyl1_Exec(struct task *tp)
{
	if (SDCheckRangeOut(tp) == 0 && (DAT_05cbef64 & 1) != 0)
	{
		ObjectSkydeck_c_cyl1_Draw(tp);
		LoopTaskC(tp);
		FUN_004c39c0(tp);
	}
}

// FUNCTION: SADX 0x00847420
void ObjectSkydeck_c_cyl1(struct task *tp)
{
	if (CheckRangeOutWithR(tp, 4410100.0f) == 0)
	{
		ObjectSkydeck_c_cyl1_Init(tp);
	}
}
