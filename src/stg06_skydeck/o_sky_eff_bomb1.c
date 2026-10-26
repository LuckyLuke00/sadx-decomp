#include "decls.h"

// STUB: SADX 0x0084be30
void FUN_0084be30(struct task *tp)
{
}

// STUB: SADX 0x0084be90
struct task *CreateEffSmallBomb1(struct NJS_POINT3 *pos, float scl)
{
	return (struct task *)0;
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
