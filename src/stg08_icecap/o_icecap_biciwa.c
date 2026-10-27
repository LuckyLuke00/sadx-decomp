#include "decls.h"

// STUB: SADX 0x0085f150
void CreateSnowR(struct NJS_POINT3 *pos, struct NJS_POINT3 *vec, float scl, float rad)
{
}

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

#pragma optimize("", off)
// STUB: SADX 0x0085fdb0
void Object_IcecapBicIwaInit(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x0085fe30
void ObjectIcecapBicIwa(struct task *tp)
{
	if (CheckRangeOut(tp) == 0)
	{
		Object_IcecapBicIwaInit(tp);
	}
}
