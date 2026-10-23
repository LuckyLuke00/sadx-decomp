#include "decls.h"

// FUNCTION: SADX 0x00846e90
void ObjectSkydeck_cannon_s1(struct task *tp)
{
	if (CheckRangeOut(tp) == 0)
	{
		struct taskwk *var1 = tp->twp;
		if (FUN_004c39c0(tp) == 0)
		{
			CCL_Init(tp, &object_cannon_s1_info[0], 1, 2);
		}
		tp->disp = ObjectSkydeck_cannon_s1_Draw;
		tp->exec = ObjectSkydeck_cannon_s1_Exec;
		tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
		var1->wtimer = 0;
		var1->mode = 0;
	}
}
