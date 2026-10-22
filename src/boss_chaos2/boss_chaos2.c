#include "decls.h"

// STUB: SADX 0x006e7ce0
void setChaos2ColliParam(struct taskwk *twp, int mode)
{
}

// FUNCTION: SADX 0x006ea190
void changeHeadColorChaos2Callback(struct obj *obj)
{
	ChaosHeadColorChange(obj);
}

// FUNCTION: SADX 0x006eb1e0
void setChaos2()
{
	CreateElementalTask(3, 2, BossChaos2);
}
