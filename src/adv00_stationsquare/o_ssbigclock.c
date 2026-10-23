#include "decls.h"

// FUNCTION: SADX 0x0068dbc0
void ObjectSSBigClock(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOutWithR(tp, 9610000.0f) == 0)
	{
		if (CheckEditMode())
		{
			if (var1->counter.l == 0)
			{
				var1->counter.l = (long)&object_ssobj_bigclock_bigclock;
			}
			dispSSBigClock(tp);
			return;
		}
		switch (var1->mode)
		{
		case 0:
			var1->mode = 1;
			var1->wtimer = 0;
			var1->timer.l = 0xa0000;
			var1->counter.l = (long)&object_ssobj_bigclock_bigclock;
			tp->dest = destChaos7Float;
			tp->disp = dispSSBigClock;
			break;
		case 1:
			var1->wtimer += 1;
			if (var1->wtimer > 0xe10)
			{
				var1->timer.w[0] += 1;
				if (var1->timer.w[0] > 0x3c)
				{
					var1->timer.w[1] += 1;
					if (var1->timer.w[1] > 0xc)
					{
						var1->timer.w[1] = 0;
					}
					var1->timer.w[0] = 0;
				}
				var1->wtimer = 0;
			}
			dispSSBigClock(tp);
			return;
		}
	}
}
