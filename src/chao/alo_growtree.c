#include "decls.h"
void FUN_004da910(int param_1);
extern int DAT_05b067d0;
extern int DAT_05b067dc;
extern int DAT_05b067e0;

// FUNCTION: SADX 0x004405d0
void AL_ClearFruitNum()
{
	if (DAT_05b067d0 != 0)
	{
		DAT_05b067d0 = 0;
		DAT_05b067e0 = 0;
	}
	else
	{
		DAT_05b067d0 = 1;
		DAT_05b067dc = 0;
	}
}

// FUNCTION: SADX 0x00440600
void FUN_00440600()
{
	if (DAT_05b067d0 != 0)
	{
		DAT_05b067dc++;
	}
	else
	{
		DAT_05b067e0++;
	}
}

// FUNCTION: SADX 0x00440c80
void ALO_GrowTreeDestructor(struct task *tp)
{
	ALW_CancelEntry(tp);
	if (tp->twp != 0)
	{
		if (tp->twp->cwp != 0)
		{
			FUN_004da910((int)tp->twp);
		}
		syFree(tp->twp);
		tp->twp = 0;
	}
	if (tp->mwp != 0)
	{
		syFree(tp->mwp);
		tp->mwp = 0;
	}
}
