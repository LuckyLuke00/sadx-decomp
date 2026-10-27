#include "decls.h"
extern void setDashParam(struct task *tp);
void setDashParam(struct task *tp);
void SetCartBonusAdd(float spd);
void FreeTask(struct task *tp);
extern float DAT_060cd270;
extern int DAT_060cd26c;

// FUNCTION: SADX 0x007e4e70
void setDashParam(struct task *tp)
{
	unsigned short var1;

	SetCartBonusAdd(DAT_060cd270);
	var1 = tp->twp->wtimer;
	tp->twp->wtimer = var1 + 1;
	if (var1 > 0x3c)
	{
		FreeTask(tp);
	}
}

#pragma optimize("", off)
// STUB: SADX 0x007e4eb0
void startDushCheck(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x007e4f60
void InitStartDushCheck()
{
	CreateElementalTask(2, 3, startDushCheck);
	DAT_060cd26c = 0;
}
