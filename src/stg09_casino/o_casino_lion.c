#include "decls.h"

// FUNCTION: SADX 0x0087c710
void ObjectCasinoLion(struct task *tp)
{
	if (CheckRangeOutWithR(tp, 640010.0f) == 0)
	{
		ObjectCasinoLionInit(tp);
	}
}
