#include "decls.h"

// STUB: SADX 0x007d6680
struct task *Create_SphereBomb(float x, float y, float z, long frame, float scl_spd, float sphere_radious)
{
	return (struct task *)0;
}

// FUNCTION: SADX 0x007d6700
void ChgSphereBombMode(struct task *tp, signed char mode)
{
	if (tp != 0)
	{
		tp->twp->mode = mode;
	}
}
