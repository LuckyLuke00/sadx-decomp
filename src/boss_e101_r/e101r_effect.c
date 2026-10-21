#include "decls.h"
extern struct task *DAT_060c4aa4;

// FUNCTION: SADX 0x0070e510
void E101R_NozzleLightExit()
{
	if (DAT_060c4aa4)
	{
		FreeTask(DAT_060c4aa4);
		DAT_060c4aa4 = 0;
	}
}
