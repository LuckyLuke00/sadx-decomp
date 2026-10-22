#include "decls.h"

// STUB: SADX 0x005d3530
void E102BeamDestruct(struct task *tp)
{
}

// FUNCTION: SADX 0x005d3950
void SetE102BeamNoHorming(struct task *tp, struct NJS_POINT3 *vec)
{
	tp->twp->mode = 2;
	tp->twp->value.l = 0;
	if (vec != (struct NJS_POINT3 *)0)
	{
		tp->mwp->spd = *vec;
	}
}

// STUB: SADX 0x005d3b00
void FUN_005d3b00(struct task *tp)
{
}
