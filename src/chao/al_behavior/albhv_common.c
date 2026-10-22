#include "decls.h"

// FUNCTION: SADX 0x00462350
long ALBHV_TurnToAim(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	if (*(short *)((char *)var1 + 0x1c6) == 0)
	{
		AL_SetMotionLinkStep(tp, 0x64, 0xf);
		*(short *)((char *)var1 + 0x1c6) = *(short *)((char *)var1 + 0x1c6) + 1;
		*(int *)((char *)var1 + 0x1d0) = 0x3c;
	}
	return MOV_TurnToAim2(tp, 0x200) < 0xb6;
}

// STUB: SADX 0x004624c0
long ALBHV_TurnToLockOn(struct task *tp)
{
	return (long)0;
}
