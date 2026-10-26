#include "decls.h"
extern long DAT_060b97f0;

// FUNCTION: SADX 0x006bf890
void ObjectPastChaosFire(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOut(tp) == 0)
	{
		tp->disp = DispPastChaosFire;
		switch (var1->mode)
		{
		case 0:
			var1->mode = 1;
			break;
		case 1:
			var1->value.f += 0.5;
			DAT_060b97f0 = (long)var1->value.f;
			if (DAT_060b97f0 >= 0x10)
			{
				DAT_060b97f0 = 0;
				var1->value.f = 0.0;
			}
			DispPastChaosFire(tp);
			return;
		}
	}
}
