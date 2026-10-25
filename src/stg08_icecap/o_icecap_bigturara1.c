#include "decls.h"
extern int DAT_060dbbb0;

// FUNCTION: SADX 0x00861120
long GetBigturaraStatus()
{
	if (DAT_060dbbb0 != 0)
	{
		int *var1 = *(int **)((char *)DAT_060dbbb0 + 0x20);
		int *var2 = *(int **)((char *)var1 + 0x10);
		if (*(int *)((char *)var2 + 0x27c) == 0 || *(int *)((char *)var2 + 0x20) == 2 || *(int *)((char *)var2 + 0x20) == 3)
		{
			return 1;
		}
	}
	return 0;
}

// FUNCTION: SADX 0x00861410
void Object_IcecapBigturaraEnd(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_060dbbb0 == (int)tp)
	{
		DAT_060dbbb0 = 0;
	}
	if (var1->counter.ptr != 0)
	{
		WithdrawCollisionEntry(tp, (struct obj *)var1->counter.ptr);
		ReleaseMobileLandObject((struct obj *)var1->counter.ptr);
	}
	Free(var1->value.ptr);
}

// FUNCTION: SADX 0x00862990
void ObjectIcecapBigturara(struct task *tp)
{
	if (CheckRangeOutWithR(tp, 4410100.0f) == 0)
	{
		if (DAT_060dbbb0 == 0)
		{
			DAT_060dbbb0 = (int)tp;
		}
		Object_IcecapBigturaraInit(tp);
	}
}
