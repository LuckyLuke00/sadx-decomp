#include "decls.h"

// STUB: SADX 0x0084bb10
void EffBombThrowPlayer(struct taskwk *twp)
{
}

#pragma optimize("", off)
// STUB: SADX 0x0084bd50
void ObjectSkydeck_eff_bomb1_Init(struct task *tp)
{
}
#pragma optimize("", on)

// STUB: SADX 0x0084be30
void FUN_0084be30(struct task *tp)
{
}

// FUNCTION: SADX 0x0084be90
struct task *CreateEffSmallBomb1(struct NJS_POINT3 *pos, float scl)
{
	struct task *var1;
	struct taskwk *var2;
	var1 = CreateElementalTask(2, 3, (void (__cdecl *)(struct task *))FUN_0084be30);
	if (var1 != 0)
	{
		var2 = var1->twp;
		var2->pos = *pos;
		var2->timer.f = scl;
		return var1;
	}
	return 0;
}

// FUNCTION: SADX 0x0084bed0
void ObjectSkydeck_eff_bomb1(struct task *tp)
{
	if (CheckRangeOutWithR(tp, 2250100.0f) == 0)
	{
		ObjectSkydeck_eff_bomb1_Init(tp);
	}
}

// STUB: SADX 0x0084bf00
struct task *CreateEffBomb2(struct NJS_POINT3 *pos, float scl, long angX, long angZ)
{
	return (struct task *)0;
}
