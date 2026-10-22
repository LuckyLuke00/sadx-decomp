#include "decls.h"
extern struct NJS_TEXLIST texlist_b_robo_bg;

// FUNCTION: SADX 0x006d6660
void BgDestructor(struct task *tp)
{
	late_ReleaseTexture(&texlist_b_robo_bg);
}

// STUB: SADX 0x006d67d0
void BgDisplayer(struct task *tp)
{
}

// FUNCTION: SADX 0x006d6800
void Rd_BossRobo(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	SetFreeCameraMode(0);
	var1->mode++;
	if (var1->mode >= 2)
	{
		var1->mode = 0;
		tp->exec = BossRoboExec;
	}
}
