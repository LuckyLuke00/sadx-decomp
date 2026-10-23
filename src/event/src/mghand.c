#include "decls.h"

// STUB: SADX 0x007dd900
void mghand_exec(struct task *tp)
{
}

// FUNCTION: SADX 0x007dda40
void chgMghandMod(struct task *tp, signed char mode)
{
	if (tp != NULL)
	{
		if (tp->twp->mode == 0)
		{
			tp->twp->mode = mode;
		}
	}
}

// FUNCTION: SADX 0x007dda60
void mghandsetspd(struct task *tp, long open_spd, long close_spd)
{
	if (tp != 0)
	{
		tp->mwp->ang_spd.x = open_spd;
		tp->mwp->ang_spd.y = close_spd;
	}
}
