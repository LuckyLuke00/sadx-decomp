#include "decls.h"

// STUB: SADX 0x006c2e40
long GetVsPlayerAng(struct taskwk *twp)
{
	return (long)0;
}

// STUB: SADX 0x006c2e80
long GetVsPlayerAbsAng(struct taskwk *twp)
{
	return (long)0;
}

// FUNCTION: SADX 0x006c2ec0
int GetBossAngMode(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct anywk *var2 = tp->awp;
	if (((var1->mode == 1) || (var1->mode == 2)) && (*(int *)((char *)var2 + 0x38) >= 0xc))
	{
		return 1;
	}
	return 0;
}
