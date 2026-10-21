#include "decls.h"

// FUNCTION: SADX 0x0060cf40
void EffectLightning(struct sp_task *tp, struct sp_link *lp)
{
	tp->no = (short)(int)(tp->frame);
	if (tp->no >= 8)
	{
		tp->no = 7;
		SpFreeTask(tp);
	}
	else
	{
		tp->frame = tp->frame + 1.0f;
	}
}
