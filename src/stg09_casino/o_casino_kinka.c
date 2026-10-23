#include "decls.h"

// STUB: SADX 0x00879580
void ObjectCasinoKinkaExec(struct task *tp)
{
}

// FUNCTION: SADX 0x008796a0
void ObjectCasinoKinka(struct task *tp)
{
	if (CheckRangeOutWithR(tp, 360010.0f) == 0)
	{
		ObjectCasinoKinkaInit(tp);
	}
}
