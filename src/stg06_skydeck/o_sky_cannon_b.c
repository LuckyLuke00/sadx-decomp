#include "decls.h"

// STUB: SADX 0x00840070
void OnHitMissile(long lParam, struct NJS_POINT3 *hitpos, struct NJS_POINT3 *hitspd)
{
}

// FUNCTION: SADX 0x0084ab20
void ObjectSkydeck_cannon_b_End(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (var1->btimer != 0)
	{
		OCMunregister((struct OCMDATA *)var1->value.ptr);
	}
	Free(var1->timer.ptr);
}

#pragma optimize("", off)
// STUB: SADX 0x0084b3d0
void ObjectSkydeck_cannon_b_Init(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x0084b4a0
void ObjectSkydeck_cannon_b(struct task *tp)
{
	if (CheckRangeOut(tp) == 0)
	{
		ObjectSkydeck_cannon_b_Init(tp);
	}
}
