#include "decls.h"
extern int DAT_060dff60;
extern short DAT_05b9d724;
extern short DAT_05b9d744;
void FUN_008cf820(int param_1, int param_2);
void FUN_008cfbb0(int param_1, int param_2);

// STUB: SADX 0x008cbb40
void SetCartBonusAdd(float spd)
{
}

// STUB: SADX 0x008cbd30
void cartSnatchPlayerInfo(struct task *tp)
{
}

// STUB: SADX 0x008cd6a0
void cartShadowPos(struct task *tp, struct taskwk *twp)
{
}

// STUB: SADX 0x008cf620
void FUN_008cf620(struct task *tp)
{
}

// FUNCTION: SADX 0x008cf7d0
void FUN_008cf7d0(int param_1, int param_2)
{
	if ((((DAT_05b9d724 << 8) | DAT_05b9d744) & 0xff00) == 0x2300)
	{
		FUN_008cf820(param_1, param_2);
	}
	else
	{
		FUN_008cfbb0(param_1, param_2);
	}
}

// STUB: SADX 0x008d0250
void FUN_008d0250(int param_1)
{
}

// STUB: SADX 0x008d02a0
void returnSonicCollision(struct task *tp)
{
}

// STUB: SADX 0x008d0810
void FUN_008d0810(void)
{
}

// STUB: SADX 0x008d0870
void FUN_008d0870(void)
{
}

// STUB: SADX 0x008d0ca0
long distCheck(struct task *tp)
{
	return (long)0;
}

// STUB: SADX 0x008d1350
void FUN_008d1350(int param_1, char *param_2)
{
}

// STUB: SADX 0x008d1380
void cartColliRangeChange(struct task *tp)
{
}

// FUNCTION: SADX 0x008d13d0
void MakeEgo(float rate)
{
	struct task *local_8;
	if (DAT_060dff60 == 0)
	{
		local_8 = CreateElementalTask(2, 3, egoManager);
		local_8->twp->counter.f = rate;
		DAT_060dff60 = 2;
	}
}

// FUNCTION: SADX 0x008d1500
void ego(struct task *tp)
{
	struct taskwk *local_8;
	local_8 = tp->twp;
	drawEgo(tp);
	local_8->counter.f = local_8->counter.f - 0.029999999329447746;
	if (local_8->counter.f <= 0.0)
	{
		local_8->counter.f = 0.0;
		FreeTask(tp);
	}
}
