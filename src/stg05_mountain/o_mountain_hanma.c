#include "decls.h"

// FUNCTION: SADX 0x00833fb0
void HanmaExec(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct taskwk *var2 = tp->ptp->twp;
	njPushMatrix(NULL);
	njUnitMatrix(NULL);
	njTranslateV(NULL, &var2->pos);
	if (*(int *)((char *)var2 + 0x18) != 0)
	{
		njRotateY(NULL, (unsigned short)*(short *)((char *)var2 + 0x18));
	}
	if ((long)var2->counter.f != 0)
	{
		njRotateX(NULL, (unsigned short)(short)var2->counter.f);
	}
	njCalcPoint(NULL, &var1->scl, &var1->pos);
	njPopMatrix(1);
	EntryColliList(var1);
}

// STUB: SADX 0x008343a0
void HanmaInit(struct task *tp)
{
}
