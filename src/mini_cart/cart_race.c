#include "decls.h"
extern struct task *DAT_060cd274;

// FUNCTION: SADX 0x007e5000
void CartRaceDestroyManageTask()
{
	if (DAT_060cd274)
	{
		DestroyTask(DAT_060cd274);
		DAT_060cd274 = 0;
	}
}
