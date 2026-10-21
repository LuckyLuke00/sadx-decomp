#include "decls.h"
extern struct task *DAT_060cc69c;

// FUNCTION: SADX 0x007d69d0
void WaterPillarOff()
{
	if (DAT_060cc69c)
	{
		FreeTask(DAT_060cc69c);
		DAT_060cc69c = 0;
	}
}
