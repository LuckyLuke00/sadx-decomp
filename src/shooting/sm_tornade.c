#include "decls.h"
extern int DAT_060ce3fc;

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

// FUNCTION: SADX 0x007ea3d0
int CheckLockMode()
{
	if ((DAT_05b932e8[0].on & (jump_button | action_button)) != 0)
	{
		if (DAT_060ce3fc++ > 0x1e)
		{
			return 1;
		}
	}
	return 0;
}

// STUB: SADX 0x007ea4c0
void RapidShotCheck(struct task *tp)
{
}
