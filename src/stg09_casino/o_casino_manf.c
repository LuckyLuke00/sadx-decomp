#include "decls.h"

// FUNCTION: SADX 0x0087cf30
void ObjectCasinoManfEnd(struct task *tp)
{
	FUN_008895d0(tp);
}

#pragma optimize("", off)
// STUB: SADX 0x0087d350
void ObjectCasinoManfInit(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x0087d3f0
void ObjectCasinoManf(struct task *tp)
{
	if (CheckRangeOutWithR(tp, 360010.0f) == 0)
	{
		ObjectCasinoManfInit(tp);
	}
}
