#include "decls.h"
extern "C" double atan2(double v, double u);
extern "C" double atan2(double v, double u);

// STUB: SADX 0x008c6bd0
void moveToTarget(struct taskwk *twp, struct motionwk2 *mwp, struct bosswk *bwp)
{
}

// STUB: SADX 0x008c6ca0
void turnToPlayer(struct taskwk *twp, struct bosswk *bwp)
{
}

// FUNCTION: SADX 0x008c6d30
long getForPlayerAngle(struct taskwk *twp, int num)
{
	if (DAT_05baf368[num] == 0)
		return 0;
	return (long)(atan2(DAT_05baf368[num]->pos.z - twp->pos.z, DAT_05baf368[num]->pos.x - twp->pos.x) * 65536.0 / 6.283184);
}
