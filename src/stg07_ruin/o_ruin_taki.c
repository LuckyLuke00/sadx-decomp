#include "decls.h"
static void Object_beach_taki_Exec(struct task *tp);
static void Object_beach_taki_Draw(struct task *tp);
// GLOBAL: SADX 0x043ac3a0
static int takipapam_fallspeed;

#pragma optimize("", off)
// STUB: SADX 0x00851240
static void Object_beach_taki_Draw(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00851410
static void Object_beach_taki_Exec(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOutWithR(tp, 1440000.0f))
	{
		return;
	}
	if (FUN_004c39c0(tp))
	{
		njPrintC(0x120010, "TakiSpeed:");
		njPrintD(0x200010, ((int)(signed char)var1->ang.x + takipapam_fallspeed) & 0xff, 3);
	}
	Object_beach_taki_Draw(tp);
	var1->wtimer++;
}

// FUNCTION: SADX 0x00851480
void Object_ruin_taki(struct task *tp)
{
	if (CheckRangeOutWithR(tp, 1440000.0f) == 0)
	{
		tp->disp = Object_beach_taki_Draw;
		tp->exec = Object_beach_taki_Exec;
		tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
		tp->twp->wtimer = 0;
	}
}
