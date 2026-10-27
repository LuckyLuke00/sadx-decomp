#include "decls.h"
extern struct MJOIN_VERTEX DAT_0317857c;
extern struct task *DAT_060cca6c;

// FUNCTION: SADX 0x007da460
void frog_disp(struct task *tp)
{
	njPushMatrix(0);
	FUN_0067d830(0, 0.0, 140.0, -430.0);
	njRotateX(0, 0x1800);
	FUN_0067d2d0(0, 6.0, 6.0, 1.5);
	if (tp->twp->ang.y)
	{
		njRotateY(0, tp->twp->ang.y);
	}
	___njSetTexture(&texlist_frog);
	MJoinVertexes(_action_f_f0001_frog[0].object, _action_f_f0001_frog[0].motion, 0.0, &DAT_0317857c);
	ds_ActionClip((struct NJS_ACTION *)&_action_f_f0001_frog, 0.0, 6.0);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x007da530
void frog_exec(struct task *tp)
{
	tp->twp->ang.y = (tp->twp->ang.y + 0x200) & 0xffff;
	frog_disp(tp);
}

// FUNCTION: SADX 0x007da5a0
void frog_delete()
{
	if (DAT_060cca6c)
	{
		FreeTask(DAT_060cca6c);
		DAT_060cca6c = 0;
	}
}
