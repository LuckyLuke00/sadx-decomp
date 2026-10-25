#include "decls.h"

// FUNCTION: SADX 0x0087ce00
void ObjectCasinoHyoujiki(struct task *tp)
{
	if (CheckRangeOutWithR(tp, 360010.0f) == 0)
	{
		ObjectCasinoHyoujikiInit(tp);
	}
}
