#include "decls.h"

// FUNCTION: SADX 0x008458f0
void ObjectSkydeck_cannon_m(struct task *tp)
{
	if (CheckRangeOut(tp) == 0)
	{
		struct taskwk *var1 = tp->twp;
		if (FUN_004c39c0(tp) == 0)
		{
			CCL_Init(tp, &object_cannon_m_info[0], 1, 2);
		}
		tp->disp = ObjectSkydeck_cannon_m_Draw;
		tp->exec = ObjectSkydeck_cannon_m_Exec;
		var1->wtimer = 0;
		var1->mode = 0;
		var1->ang.x = 0;
		var1->ang.z = 0;
	}
}
