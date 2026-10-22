#include "decls.h"

// STUB: SADX 0x006b2d50
void PalmDisplayer(struct task *tp)
{
}

// FUNCTION: SADX 0x006b2dd0
void ObjectMysticRuinPalm(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOut(tp) == 0)
	{
		if (var1->mode == 0)
		{
			tp->disp = PalmDisplayer;
			var1->mode = 1;
		}
		PalmDisplayer(tp);
	}
}
