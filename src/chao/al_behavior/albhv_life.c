#include "decls.h"

// STUB: SADX 0x00461630
struct task *CreateEggSucceed(struct task *pChaoTask)
{
	return (struct task *)0;
}

// FUNCTION: SADX 0x00461670
long ALBHV_BornPon(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (*(short *)((char *)var1 + 0x1c6) == 0)
	{
		AL_SetMotionLinkStep(tp, 0xd1, 0xf);
		*(short *)((char *)var1 + 0x1c6) = *(short *)((char *)var1 + 0x1c6) + 1;
	}
	return AL_IsMotionEnd(tp) != 0;
}

// FUNCTION: SADX 0x004616b0
long ALBHV_BornKyoro(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (*(unsigned short *)((char *)var1 + 0x1c6) == 0)
	{
		AL_SetMotionLinkStep(tp, 0xd0, 0xf);
		*(unsigned short *)((char *)var1 + 0x1c6) += 1;
	}
	return AL_IsMotionEnd(tp) != 0;
}

// FUNCTION: SADX 0x00461b80
void MayuDestructor(struct task *tp)
{
	late_exec();
	if (tp->ptp != NULL)
	{
		*(int *)((char *)tp->ptp->twp + 0x44) = 0;
	}
}

// STUB: SADX 0x00461c00
void MayuDisplayer(struct task *tp)
{
}
