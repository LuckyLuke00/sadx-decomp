#include "decls.h"
extern struct task *DAT_060cc9ac;

// FUNCTION: SADX 0x007d9500
void ChgEffectMod(signed char mode)
{
	if (DAT_060cc9ac)
	{
		DAT_060cc9ac->twp->mode = mode;
	}
}

// FUNCTION: SADX 0x007d9520
void DelE102Effect()
{
	if (DAT_060cc9ac)
	{
		FreeTask(DAT_060cc9ac);
		DAT_060cc9ac = 0;
	}
}
