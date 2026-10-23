#include "decls.h"

// STUB: SADX 0x0084e020
void ObjectSkydeck_eff_hahen1_End(struct task *tp)
{
}

// FUNCTION: SADX 0x0084e210
void ObjectSkydeck_eff_hahen1(struct task *tp)
{
	struct taskwk *var1;

	if (CheckRangeOutWithR(tp, 2250100.0f) == 0)
	{
		var1 = tp->twp;
		tp->disp = ObjectSkydeck_eff_hahen1_Draw;
		tp->exec = ObjectSkydeck_eff_hahen1_Exec;
		tp->dest = ObjectSkydeck_eff_hahen1_End;
		var1->wtimer = 0;
		var1->mode = 0;
	}
}
