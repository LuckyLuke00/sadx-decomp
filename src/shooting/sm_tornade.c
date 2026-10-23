#include "decls.h"

// FUNCTION: SADX 0x007ea050
void TornadeDestruct(struct task *tp)
{
	PDestruct(tp->twp->counter.b[0]);
}

// STUB: SADX 0x007ea280
long TornadeCheckInput(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	return (long)0;
}

// STUB: SADX 0x007ea3d0
int CheckLockMode()
{
	return (int)0;
}

// STUB: SADX 0x007ea4c0
void RapidShotCheck(struct task *tp)
{
}
