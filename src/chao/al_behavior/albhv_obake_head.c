#include "decls.h"
extern "C" int rand(void);

// FUNCTION: SADX 0x0045fb90
long ALBHV_HoldThink(struct task *tp)
{
	struct taskwk *var1;
	int var2;
	float var3;

	var1 = tp->twp;
	if (*(unsigned short *)((char *)var1 + 0x1c6) == 0)
	{
		AL_SetMotionLinkStep(tp, 0xc1, 0x23);
		*(unsigned short *)((char *)var1 + 0x1c6) = *(unsigned short *)((char *)var1 + 0x1c6) + 1;
		AL_IconSet(tp, 3, 0x78);
		var2 = rand();
		var3 = (float)var2 * 3.0517578125e-05;
		*(unsigned int *)((char *)var1 + 0x1d0) = (unsigned short)((int)(var3 * 61.0) + 0x78);
	}
	var2 = *(int *)((char *)var1 + 0x1d0);
	*(int *)((char *)var1 + 0x1d0) = var2 - 1;
	if (var2 <= 0)
	{
		return 1;
	}
	return AL_MoveHoldingObject(tp) == 0;
}
