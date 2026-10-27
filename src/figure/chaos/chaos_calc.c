#include "decls.h"
extern float DAT_05edd144;
long AdjustAngle(long ang0, long ang1, long dang);
extern struct bosswk *DAT_05edd138;
extern "C" double atan2(double v, double u);
extern "C" double atan2(double v, double u);
extern "C" double atan2(double v, double u);

// FUNCTION: SADX 0x008c6bd0
void moveToTarget(struct taskwk *twp, struct motionwk2 *mwp, struct bosswk *bwp)
{
	struct bosswk *local_8g;
	int local_cg;
	local_8g = bwp;
	local_cg = (int)(atan2(*(float *)((char *)local_8g + 0x6c) - twp->pos.z, *(float *)((char *)local_8g + 0x64) - twp->pos.x) * 65536.0 / 6.283184);
	*(long *)((char *)twp + 0x18) = AdjustAngle(*(long *)((char *)twp + 0x18), local_cg, *(long *)((char *)DAT_05edd138 + 0x10));
	twp->pos.x = njCos(*(long *)((char *)twp + 0x18)) * *(float *)((char *)DAT_05edd138 + 0xc) + twp->pos.x;
	twp->pos.z = njSin(*(long *)((char *)twp + 0x18)) * *(float *)((char *)DAT_05edd138 + 0xc) + twp->pos.z;
	DAT_05edd144 = DAT_05edd144 + *(float *)((char *)DAT_05edd138 + 0xc);
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
