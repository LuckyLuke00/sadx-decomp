#include "decls.h"
extern void *DAT_060cb328;
void FUN_0044c4b0(void *);

// FUNCTION: SADX 0x00716330
void AL_ReleaseMessageTable()
{
	if (DAT_060cb328)
	{
		FUN_0044c4b0(DAT_060cb328);
		DAT_060cb328 = 0;
	}
}
