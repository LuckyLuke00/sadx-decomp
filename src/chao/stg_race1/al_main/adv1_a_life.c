#include "decls.h"

// FUNCTION: SADX 0x004925f0
long AL_GetALifewk(struct task *tp, struct al_status *status)
{
	struct al_status *var1 = (struct al_status *)CAlloc(1, 0x8d4);
	if (var1 == 0)
	{
		DestroyTask(tp);
		return 0;
	}
	*(unsigned long *)((char *)var1 + 0x60) |= 0x10;
	*(float *)((char *)var1 + 0xd8) = 1.0f;
	*(unsigned long *)((char *)var1 + 0xec) = (unsigned long)status;
	tp->mwp = (struct motionwk *)var1;
	*(struct task **)((char *)var1 + 0x8cc) = tp;
	return 1;
}
