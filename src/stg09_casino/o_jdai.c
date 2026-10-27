#include "decls.h"
extern int DAT_060dbcb0;
extern unsigned char DAT_060dbca7;

// FUNCTION: SADX 0x00885010
void cCameraReturn(struct task *ctp)
{
	struct taskwk *var1 = ctp->twp;
	if (--var1->btimer == 0)
	{
		DAT_060dbca7 = 0x80;
		if (var1->smode != 0)
		{
			DAT_060dbcb0 |= 2;
		}
		else
		{
			DAT_060dbcb0 |= 4;
		}
		ctp->ptp->twp->flag &= 0xfeff;
		FreeTask(ctp);
	}
}

// STUB: SADX 0x00885060
void cNormal(struct task *ctp)
{
}
