#include "decls.h"
void FUN_007d21b0(void *param_1);

// FUNCTION: SADX 0x00835fa0
void Object_Mountain_Kumonosu(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOut(tp) == 0)
	{
		if (FUN_004c39c0(tp))
		{
			var1->timer.l = (long)&object_kumonosu_kumonosu1a_kumonosu1a;
			var1->value.l = (long)&texlist_obj_mountain;
			return;
		}
		switch (var1->mode)
		{
		case 0:
			var1->mode = 1;
			var1->timer.l = (long)&object_kumonosu_kumonosu1a_kumonosu1a;
			var1->value.l = (long)&texlist_obj_mountain;
			tp->disp = Object_Mountain_Kumonosu_Display;
			tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
			break;
		case 1:
			Object_Mountain_Kumonosu_Display(tp);
			return;
		}
	}
}
