#include "decls.h"

// FUNCTION: SADX 0x008cb190
void EggmanDestruct(struct task *tp)
{
	struct taskwk *local_8;
	local_8 = tp->twp;
	PDestruct(local_8->counter.b[0]);
	ReleasePlayersTexture(1);
}

// STUB: SADX 0x008cb460
void EggmanChangeRunningMotion(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
}

// STUB: SADX 0x008cb540
long EggmanCheckJump(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	return (long)0;
}

// STUB: SADX 0x008cb620
long EggmanCheckInput(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	return (long)0;
}

// STUB: SADX 0x008cb6b0
long EggmanCheckAutoPilot(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	return (long)0;
}

// STUB: SADX 0x008cb770
long EggmanCheckBeInTheAir(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	return (long)0;
}

// STUB: SADX 0x008cb7c0
long EggmanCheckStop(struct taskwk *twp, struct motionwk2 *mwp, struct playerwk *pwp)
{
	return (long)0;
}
