#include "decls.h"

// FUNCTION: SADX 0x0085e530
void Object_IcecapHasihasiExec(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOut(tp))
	{
		return;
	}
	Object_IcecapHasihasiDraw(tp);
	if (!FUN_004c39c0(tp))
	{
		EntryColliList(var1);
	}
}

// FUNCTION: SADX 0x0085e570
void ObjectIcecapHasihasi(struct task *tp)
{
	struct taskwk *var1;
	if (CheckRangeOut(tp) == 0)
	{
		var1 = tp->twp;
		if (FUN_004c39c0(tp) == 0)
		{
			CCL_Init(tp, &object_hasihasi_info[0], 1, 4);
			CheckCollisionScale(var1);
		}
		tp->disp = Object_IcecapHasihasiDraw;
		tp->exec = Object_IcecapHasihasiExec;
		tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
	}
}
