#include "decls.h"

// FUNCTION: SADX 0x0087e000
void ObjectCasinoKkdoor(struct task *tp)
{
	if (CheckRangeOutWithR(tp, 360010.0f) == 0)
	{
		ObjectCasinoKkdoorInit(tp);
	}
}
