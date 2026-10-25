#include "decls.h"
extern struct task *DAT_060c60ec;

// STUB: SADX 0x00710a10
long DigitsToInt(const signed char *dig)
{
	return (long)0;
}

// FUNCTION: SADX 0x007110e0
void ALO_RingWinDelete()
{
	if (DAT_060c60ec)
	{
		FreeTask(DAT_060c60ec);
		DAT_060c60ec = 0;
	}
}
