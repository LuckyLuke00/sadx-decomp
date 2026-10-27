#include "decls.h"

// FUNCTION: SADX 0x00862f50
void ObjectIcecapFuusya1(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	if (CheckRangeOutWithR(tp, 1000100.0f) != 0)
	{
		return;
	}
	*(struct colliwk **)((char *)var1 + 0x1c) = 0;
	var1->wtimer = 0;
	tp->disp = Object_IcecapFuusya1Draw;
	tp->exec = Object_IcecapFuusya1Exec;
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
}
