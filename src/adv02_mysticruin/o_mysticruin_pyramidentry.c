#include "decls.h"

// FUNCTION: SADX 0x006ac0f0
int CheckOpenState()
{
	if (GetPlayerCharacterName(0) == 0)
	{
		if (SeqCheckFlag(0xae))
		{
			return SeqCheckFlag(0xaf);
		}
	}
	{
		int var1 = SeqVarID[GetPlayerCharacterName(0)];
		if (var1 >= 0)
		{
			return *(unsigned char *)(0x5bafb00 + var1);
		}
		return 0;
	}
}

// FUNCTION: SADX 0x006ac750
void DesertATask(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	WithdrawCollisionEntry(tp, (struct obj *)var1->counter.ptr);
	ReleaseMobileLandObject((struct obj *)var1->counter.ptr);
	Free(var1->value.ptr);
}
