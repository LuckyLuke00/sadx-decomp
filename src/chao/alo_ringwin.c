#include "decls.h"
extern struct task *DAT_060c60ec;

// FUNCTION: SADX 0x007110e0
void ALO_RingWinDelete()
{
	if (DAT_060c60ec)
	{
		FreeTask(DAT_060c60ec);
		DAT_060c60ec = 0;
	}
}
