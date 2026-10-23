#include "decls.h"
extern int DAT_060d0acc;
extern int DAT_060d0ad0;

// STUB: SADX 0x0083e500
void dispSkyLever(struct task *tp)
{
}

// FUNCTION: SADX 0x0083e590
void exitSkyLever(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (*(void **)((char *)var1 + 8))
	{
		WithdrawCollisionEntry(tp, (struct obj *)*(void **)((char *)var1 + 8));
		ReleaseMobileLandObject((struct obj *)*(void **)((char *)var1 + 8));
		if (tp->ptp)
		{
			DAT_060d0acc = tp->twp->ang.x;
			DAT_060d0ad0 = tp->twp->ang.z;
		}
	}
}

// STUB: SADX 0x0083e5e0
void FUN_0083e5e0(struct task *tp)
{
}
