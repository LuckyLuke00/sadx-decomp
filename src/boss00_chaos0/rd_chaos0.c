#include "decls.h"

// FUNCTION: SADX 0x006e2810
void Bg_Chaos0(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	FUN_004a0520(DAT_05b3e080.x, DAT_05b3e080.y);
	switch (var1->mode)
	{
	case 0:
		___njSetBackColor(0xff000000, 0xff000000, 0xff000000);
		var1->mode = 1;
		break;
	case 1:
		break;
	case 2:
		var1->mode = 0;
		break;
	default:
		Free(tp);
		break;
	}
	FUN_004a0520(DAT_05b3e050.x, DAT_05b3e050.y);
}
