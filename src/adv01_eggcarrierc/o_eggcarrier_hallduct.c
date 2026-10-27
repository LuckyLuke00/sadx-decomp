#include "decls.h"

#pragma optimize("", off)
// STUB: SADX 0x006a3be0
void DuctDisplayer(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x006a3c70
void ObjectECHallDuct(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOut(tp) == 0)
	{
		if (var1->mode == 0)
		{
			tp->disp = DuctDisplayer;
			var1->mode = 1;
		}
		DuctDisplayer(tp);
	}
}
