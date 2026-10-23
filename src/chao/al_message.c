#include "decls.h"
extern void *DAT_060cb328;
void FUN_0044c4b0(void *);

// FUNCTION: SADX 0x00716310
const unsigned long *AL_LoadMessageTable(char *fileid)
{
	return (const unsigned long *)(DAT_060cb328 = (void *)AlMsgStrLoad(fileid));
}

// FUNCTION: SADX 0x00716330
void AL_ReleaseMessageTable()
{
	if (DAT_060cb328)
	{
		FUN_0044c4b0(DAT_060cb328);
		DAT_060cb328 = 0;
	}
}

// FUNCTION: SADX 0x00716350
const char *AL_GetMessage(long MessageId)
{
	const char *var1 = 0;
	if (DAT_060cb328 != 0)
	{
		var1 = (const char *)DAT_060cb328 + *(int *)((char *)DAT_060cb328 + MessageId * 4);
	}
	return var1;
}
