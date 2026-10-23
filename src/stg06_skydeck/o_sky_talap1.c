#include "decls.h"
extern unsigned char DAT_05cbef64;

// FUNCTION: SADX 0x00848060
void ObjectSkydeck_c_talap1_End(struct task *tp)
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
}

// FUNCTION: SADX 0x008481e0
void ObjectSkydeck_c_talap1_Exec(struct task *tp)
{
	if (CheckRangeOutWithR(tp, 4410100.0f) == 0)
	{
		if (DAT_05cbef64 & 1)
		{
			ObjectSkydeck_c_talap1_Draw(tp);
			FUN_004c39c0(tp);
		}
	}
}

// FUNCTION: SADX 0x008482c0
void ObjectSkydeck_c_talap1(struct task *tp)
{
	if (CheckRangeOutWithR(tp, 4410100.0f) == 0)
	{
		ObjectSkydeck_c_talap1_Init(tp);
	}
}
