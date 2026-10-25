#include "decls.h"
extern int takipapam_fallspeed;

// FUNCTION: SADX 0x007f9cf0
void Object_beach_taki_Exec(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOutWithR(tp, 1440000.0f))
	{
		return;
	}
	if (FUN_004c39c0(tp))
	{
		njPrintC(0x120010, "TakiSpeed:");
		njPrintD(0x200010, (signed char)var1->ang.x + takipapam_fallspeed & 0xff, 3);
	}
	Object_beach_taki_Draw(tp);
	var1->wtimer++;
}

// FUNCTION: SADX 0x007f9d60
void Object_beach_taki(struct task *tp)
{
	if (CheckRangeOutWithR(tp, 1440000.0f) == 0)
	{
		tp->disp = Object_beach_taki_Draw;
		tp->exec = Object_beach_taki_Exec;
		tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
		tp->twp->wtimer = 0;
	}
}
