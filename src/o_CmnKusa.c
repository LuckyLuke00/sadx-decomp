#include "decls.h"

// FUNCTION: SADX 0x008bbba0
void NomalObject(struct task *tp)
{
	void (*local_8)(struct task *);
	local_8 = tp->disp;
	local_8(tp);
	CheckRangeOut(tp);
}

// FUNCTION: SADX 0x008bbfc0
void FUN_008bbfc0(struct task *param_1)
{
	long local_8;
	local_8 = ChkItemInPercent(CmnKusaRanItemTbl);
	if (local_8 == 0)
	{
		return;
	}
	MakePopUpItem((struct taskwk *)param_1, local_8);
}
