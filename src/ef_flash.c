#include "decls.h"
#include <stdlib.h>

// FUNCTION: SADX 0x005e81c0
void EffectFlash(struct sp_task *tp, struct sp_link *lp)
{
	*(short *)((char *)tp + 0xa) = (short)(int)*(float *)((char *)tp + 0x10);
	if (*(short *)((char *)tp + 0xa) > 7)
	{
		*(short *)((char *)tp + 0xa) = 7;
		SpFreeTask(tp);
	}
	else
	{
		*(float *)((char *)tp + 0x10) = *(float *)((char *)tp + 0x10) + 0.4f;
	}
}
