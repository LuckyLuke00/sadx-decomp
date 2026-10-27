#include "decls.h"

// STUB: SADX 0x0087c740
long ObjectCasinoHyoujiki_DispDigit(int hyoujikiID, int num)
{
	return (long)0;
}

// STUB: SADX 0x0087c7d0
void ObjectCasinoHyoujikiEnd(struct task *tp)
{
}

// FUNCTION: SADX 0x0087ce00
void ObjectCasinoHyoujiki(struct task *tp)
{
	if (CheckRangeOutWithR(tp, 360010.0f) == 0)
	{
		ObjectCasinoHyoujikiInit(tp);
	}
}
