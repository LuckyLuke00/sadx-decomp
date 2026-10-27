#include "decls.h"
extern long DAT_060dc408[5];

// FUNCTION: SADX 0x00874d80
long ObjCasino_GetFanStatus(signed char ID)
{
	if (ID < 5)
	{
		return DAT_060dc408[ID];
	}
	return 0;
}

// STUB: SADX 0x008752f0
void EndKuzu(struct taskwk *twp)
{
}

// STUB: SADX 0x00875a30
void ObjectCasinoFanfan(struct task *tp)
{
}
