#include "decls.h"
extern struct NJS_ACTION action_skymain_eskwa_u[1];

// FUNCTION: SADX 0x00701f50
void exitSkyEscalatorManager(struct task *tp)
{
	FreeTaskC(tp);
	FreeTask(tp);
}

// FUNCTION: SADX 0x008412d0
void execSkyEscalator(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	switch (var1->mode)
	{
		case 0:
			var1->mode = 1;
			var1->counter.ptr = &action_skymain_eskwa_u;
			tp->dest = destChaos7Float;
			tp->disp = dispSkyEscalator;
			break;
		case 1:
			dispSkyEscalator(tp);
			break;
	}
}
