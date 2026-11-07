#include "decls.h"

// FUNCTION: SADX 0x004932f0
void ADV1_AL_InitIcon(struct taskwk *twp, struct alifewk *awp)
{
	awp->icon.mode = 0;
	awp->icon.next_mode = 0xffff;
}
