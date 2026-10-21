#include "decls.h"
extern int DAT_0263d6f0;

// FUNCTION: SADX 0x005b2450
void SetEventWork(struct taskwk *twp)
{
	struct eventwk *local_8;

	if (twp->ewp == 0)
	{
		local_8 = (struct eventwk *)CAlloc(1, 0x7c);
		twp->ewp = local_8;
		local_8->mode = 3;
	}
}

// STUB: SADX 0x005b24c0
void FreeEventAction(struct taskwk *twp)
{
}

// FUNCTION: SADX 0x005b2640
void DrawEventAction(struct taskwk *twp)
{
	DrawEventActionPL(twp, DAT_0263d6f0);
}
