#include "decls.h"

// FUNCTION: SADX 0x004932f0
void ADV1_AL_InitIcon(struct taskwk *twp, struct alifewk *awp)
{
	*(short *)((char *)awp + 0x812) = 0;
	*(unsigned short *)((char *)awp + 0x816) = 0xffff;
}
