#include "decls.h"
static void Norm(struct task *tp);
static void Draw(struct task *tp);

#pragma optimize("", off)
// STUB: SADX 0x008320b0
static void Norm(struct task *tp)
{
}
#pragma optimize("", on)

#pragma optimize("", off)
// STUB: SADX 0x008321a0
static void Draw(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00832250
void ObjectMountainGear(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOutWithR(tp, 1000000.0f) == 0)
	{
		switch (var1->mode)
		{
		case 0:
			var1->counter.f = 0.0f;
			tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
			tp->disp = Draw;
			var1->mode = 1;
			break;
		case 1:
			Norm(tp);
			Draw(tp);
			return;
		}
	}
}
