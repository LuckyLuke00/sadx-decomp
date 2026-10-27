#include "decls.h"

// STUB: SADX 0x007ecac0
void DirectionToPlayer(struct taskwk *twp)
{
}

// STUB: SADX 0x007ecbc0
void Zako2GunDraw(struct task *tp)
{
}

// FUNCTION: SADX 0x007ecca0
void Zako2GunDead(struct task *tp)
{
	tp->twp->mode = 5;
}
