#include "decls.h"

// FUNCTION: SADX 0x00809220
void ObjectWindyGate(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOut(tp) == 0)
	{
		switch (var1->mode)
		{
		case 0:
			var1->mode = 1;
			tp->disp = DrawGate;
			CCL_Init(tp, (struct CCL_INFO *)0x3b75848, 7, 4);
			break;
		case 1:
			var1->counter.f = *(float *)((char *)var1 + 0x2c) + var1->counter.f;
			var1->timer.f = *(float *)((char *)var1 + 0x30) + var1->timer.f;
			if (FUN_004c39c0(tp))
			{
				njPrintC(0x110013, "<- ROTATEY_SPEED");
				njPrintC(0x110014, "<- ROTATEZ_SPEED");
			}
			DrawGate(tp);
			EntryColliList(var1);
			return;
		}
	}
}
