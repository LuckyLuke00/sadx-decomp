#include "decls.h"

extern struct AlrReal *DAT_05b33108;
int FUN_004825a0(struct AlrReal *param_1);

// FUNCTION: SADX 0x004822c0
struct AlrReal *FUN_004822c0()
{
	struct AlrReal *pReal = (struct AlrReal *)CAlloc(1, 0x1590);
	if (DAT_05b33108 == 0)
	{
		DAT_05b33108 = pReal;
		if (pReal == 0)
		{
			return 0;
		}
		else
		{
			if (FUN_004825a0(pReal))
			{
				return pReal;
			}
		}
	}
	else
	{
		return 0;
	}
	return 0;
}
