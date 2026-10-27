#include "decls.h"
void E102AddSecTotalNew(struct task *tp);
struct task *CreateElementalTask(unsigned short im, long level, void (*exec)(struct task *));
void AddTime(int sec);
int dsPlay_oneshot(int tone, int id, int pri, int volofs);
extern int DAT_05edc134;
extern unsigned char DAT_05cc43a1;
extern int DAT_05edc138;

// FUNCTION: SADX 0x005b9b20
void AddTimeComboAfter(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	if (((short)local_8->timer.w[1]) > 0)
	{
		local_8->timer.w[1]--;
	}
	else
	{
		local_8->timer.w[1] = 3;
		if (((short)local_8->timer.w[0]) > 0)
		{
			local_8->timer.w[0]--;
			AddTime(1);
			dsPlay_oneshot(4, 0, 0, 0);
		}
		if (((short)local_8->timer.w[0]) == 0)
		{
			DAT_05cc43a1 = 1;
			DestroyTask(tp);
		}
	}
}

// STUB: SADX 0x005b9bc0
void DispDigitTotal(long digit, float scl, struct NJS_POINT3 *pos)
{
}

// FUNCTION: SADX 0x005b9d40
void E102AddRestTime(int add_time)
{
	struct task *local_8;

	if (DAT_05edc134 == 0)
	{
		local_8 = CreateElementalTask(2, 2, E102AddSecTotalNew);
		if (local_8 == 0)
		{
			AddTime(1);
			dsPlay_oneshot(4, 0, 0, 0);
			return;
		}
	}
	else
	{
		local_8 = (struct task *)DAT_05edc134;
	}
	local_8->twp->timer.b[1]++;
}

// FUNCTION: SADX 0x005b9db0
void E102AddRestTimeNew(struct task *atp)
{
	if (atp == 0)
	{
		if (DAT_05edc134 == 0)
		{
			atp = CreateElementalTask(2, 2, E102AddSecTotalNew);
			if (atp == 0)
			{
				AddTime(1);
				dsPlay_oneshot(4, 0, 0, 0);
				return;
			}
		}
		else
		{
			atp = (struct task *)DAT_05edc134;
		}
		if (atp->twp != 0)
		{
			atp->twp->timer.b[0]++;
		}
	}
	if (atp->twp != 0)
	{
		atp->twp->timer.b[1]++;
	}
}

// FUNCTION: SADX 0x005ba1d0
void AddTimeComboAfterDest(struct task *tp)
{
	DAT_05edc138--;
}

// STUB: SADX 0x005ba1f0
void E102AddSecTotalNewDisplay(struct task *tp)
{
}

// FUNCTION: SADX 0x005ba3b0
void E102AddSecTotalNewDest(struct task *tp)
{
	DAT_05edc134 = 0;
	DAT_05cc43a1 = 1;
	if (((signed char)tp->twp->mode) != 0x7f)
	{
		DAT_05edc138 = DAT_05edc138 - 1;
	}
}
