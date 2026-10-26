#include "decls.h"

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
