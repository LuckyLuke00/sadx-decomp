#include "decls.h"
void FUN_006c1b20(struct task *param_1);
extern int DAT_05b3ebbc;
extern const struct HintMessageString *tikal_mes_egm1[5];
extern int DAT_060b990c;

// FUNCTION: SADX 0x006c1530
void egm1serifu(int adx_num)
{
	if (DAT_060b990c == 0)
	{
		Serif_Play(adx_num);
	}
}

// FUNCTION: SADX 0x006c1540
void TikalTaskExec(struct task *tp)
{
	if (--tp->twp->counter.l == 0)
	{
		DestroyTask(tp);
	}
}

// FUNCTION: SADX 0x006c1560
void TikalTaskExit(struct task *tp)
{
	DAT_060b990c = 0;
}

// FUNCTION: SADX 0x006c1570
void ChkEgm1Tikal(struct task *tp, struct taskwk *twp, struct bossextwk *bxwp)
{
	struct task *var1;
	var1 = CreateElementalTask(2, 1, TikalTaskExec);
	if (var1 != 0)
	{
		var1->dest = TikalTaskExit;
		*(int *)((char *)var1->twp + 8) = tikal_mes_egm1[DAT_05b3ebbc]->wait;
		DAT_060b990c = 1;
		ObjectTikalBoss(tikal_mes_egm1[DAT_05b3ebbc], 0x629);
	}
}

// FUNCTION: SADX 0x006c1bd0
void TaskBossEnd(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct anywk *var2 = tp->awp;

	EraseDolbyCtrl(var1);
	*(short *)((char *)var2 + 4) = 0xe;
	BSetMotion(var1, (struct bosswk *)var2);
	FreeEgm1JetTask();
}

// FUNCTION: SADX 0x006c1e20
void setBoss_egm1()
{
	struct task *var1;

	var1 = CreateElementalTask(3, 1, TaskBossExec);
	if (var1 != NULL)
	{
		TaskBossInit(var1);
		var1->exec = TaskBossExec;
		var1->disp = FUN_006c1b20;
		var1->dest = TaskBossEnd;
	}
}
