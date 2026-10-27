#include "decls.h"

#pragma optimize("", off)
// STUB: SADX 0x006edba0
void EffMiniBallDisplay(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x006edc60
void EffMiniBall(struct task *tp)
{
	struct taskwk *local_8 = tp->twp;
	switch (local_8->mode)
	{
	case 0:
		local_8->counter.f = 1.0f;
		tp->disp = EffMiniBallDisplay;
		local_8->mode = 1;
	case 1:
		local_8->counter.f = local_8->counter.f - 0.06666667014360428f;
		if (local_8->counter.f <= 0.0f)
		{
			DestroyTask(tp);
			return;
		}
	}
	EffMiniBallDisplay(tp);
}
