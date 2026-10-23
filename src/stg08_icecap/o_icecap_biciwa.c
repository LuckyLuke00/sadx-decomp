#include "decls.h"

// FUNCTION: SADX 0x0085fd70
void Object_IcecapBicIwaExec(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOut(tp) == 0)
	{
		ModelTurnWhite(var1, 0xff);
		Object_IcecapBicIwaDraw(tp);
		ResetMaterial();
		Object_IcecapBicIwa_MovableMRegularExecute(tp, &var1->scl);
	}
}

// STUB: SADX 0x0085fdb0
void Object_IcecapBicIwaInit(struct task *tp)
{
}

// FUNCTION: SADX 0x0085fe30
void ObjectIcecapBicIwa(struct task *tp)
{
	if (CheckRangeOut(tp) == 0)
	{
		Object_IcecapBicIwaInit(tp);
	}
}
