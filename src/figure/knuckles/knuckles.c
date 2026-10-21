#include "decls.h"
extern int DAT_06274afc;
extern int DAT_05cc62c0;
extern int DAT_05cc62d0;

// FUNCTION: SADX 0x00530110
long IsKnucklesWhistling(struct taskwk *twp)
{
	if (twp->mode == 0x38)
		return 1;
	return 0;
}

// FUNCTION: SADX 0x00530130
long IsKnucklesShakingTree(struct taskwk *twp)
{
	if (twp->mode == 0x28)
		return 1;
	return 0;
}

// FUNCTION: SADX 0x00530150
void _knucklesmot_init()
{
	DAT_05cc62c0 = *(int *)(DAT_06274afc + 0xa0);
	DAT_05cc62d0 = *(int *)(DAT_06274afc + 0xa4);
}
