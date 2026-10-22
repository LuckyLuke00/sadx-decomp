#include "decls.h"
extern int DAT_05ccde0c;

// FUNCTION: SADX 0x0056a2a0
void FUN_0056a2a0()
{
	PadReadOn();
}

// FUNCTION: SADX 0x0056a2b0
void FUN_0056a2b0()
{
	PadReadOff();
}

// FUNCTION: SADX 0x0056a2c0
void FUN_0056a2c0()
{
	void *local_8;
	local_8 = TH_GetWork(0);
	if (DAT_05ccde0c == 0)
	{
		DAT_05ccde0c = *(int *)local_8;
	}
}
