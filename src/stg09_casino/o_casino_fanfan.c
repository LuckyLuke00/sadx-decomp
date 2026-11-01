#include "decls.h"
extern void *DAT_060dc41c;
extern int DAT_060dc420;
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

// FUNCTION: SADX 0x008752f0
void EndKuzu(struct task *twp)
{
	struct taskwk *var1 = twp->twp;

	if (var1->counter.l != 0)
	{
		if (DAT_060dc41c != 0)
		{
			if (--DAT_060dc420 == 0)
			{
				Free(DAT_060dc41c);
				DAT_060dc41c = 0;
			}
		}
		var1->counter.l = 0;
	}
}

// STUB: SADX 0x00875a30
void ObjectCasinoFanfan(struct task *tp)
{
}
