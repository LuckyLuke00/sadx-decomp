#include "decls.h"

// FUNCTION: SADX 0x00521a60
long IsAmyWhistling(struct taskwk *twp)
{
	if (twp->mode == 0x34)
		return 1;
	return 0;
}

// FUNCTION: SADX 0x00521a80
long IsAmyPutting(struct taskwk *twp)
{
	if (twp->mode == 0x18)
		return 1;
	return 0;
}

// FUNCTION: SADX 0x00521aa0
long IsAmyShakingTree(struct taskwk *twp)
{
	if (twp->mode == 0x24)
		return 1;
	return 0;
}
