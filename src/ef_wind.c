#include "decls.h"
extern struct task *DAT_05edcc38;

// FUNCTION: SADX 0x005da900
void StopWind()
{
	if (DAT_05edcc38 != 0)
	{
		DestroyTask(DAT_05edcc38);
		DAT_05edcc38 = 0;
	}
}

// FUNCTION: SADX 0x005da930
void StopBlowingWind(struct task *tp)
{
	DAT_05edcc38 = 0;
}
