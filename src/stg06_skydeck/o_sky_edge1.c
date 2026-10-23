#include "decls.h"

// FUNCTION: SADX 0x00847710
void ObjectSkydeck_c_edge1_End(struct task *tp)
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
	OCMunregister((struct OCMDATA *)var1->timer.ptr);
}

// FUNCTION: SADX 0x00847da0
void ObjectSkydeck_c_edge1(struct task *tp)
{
	if (CheckRangeOutWithR(tp, 4410100.0f) == 0)
	{
		ObjectSkydeck_c_edge1_Init(tp);
	}
}
