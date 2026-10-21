#include "decls.h"
void StopBlowingWind(struct task *tp);
extern struct task *DAT_05edcc38;

// STUB: SADX 0x005da830
void SetWind(unsigned char str, long *pAngy)
{
}

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
