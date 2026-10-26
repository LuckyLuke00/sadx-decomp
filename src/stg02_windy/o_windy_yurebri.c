#include "decls.h"
static void Draw(struct task *tp);

#pragma optimize("", off)
// STUB: SADX 0x0080a740
static void Draw(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x0080a810
void ObjectWindyYureBri(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOut(tp) == 0)
	{
		switch (var1->mode)
		{
		case 0:
			tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
			tp->disp = Draw;
			var1->mode = 1;
			break;
		case 1:
			if (FUN_004c39c0(tp) == 0)
			{
				var1->counter.f += var1->scl.x;
			}
			if (FUN_004c39c0(tp) != 0)
			{
				njPrintC(0x110013, "<- MOTION_SPEED");
			}
			Draw(tp);
			return;
		}
	}
}
