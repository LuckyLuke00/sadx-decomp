#include "decls.h"
static void TaskBossExec(struct task *tp);
static void TikalTaskExit(struct task *tp);
static void TaskBossEnd(struct task *tp);
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
static void TikalTaskExit(struct task *tp)
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

// FUNCTION: SADX 0x006c1670
void SetEgm1DispMatrix(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct anywk *var2 = tp->awp;
	njTranslateV((float *)0, &var1->pos);
	if (GetBossAngMode(tp) != 0)
	{
		njRotateZXY(0, var1->ang.x, var1->ang.y, var1->ang.z);
	}
	else
	{
		ZRotateYXZ((float *)((float (*)[16])0), &var1->ang);
	}
	if (*(int *)((char *)var2 + 0xa0) != 0)
	{
		njRotateX(NULL, (unsigned short)*(short *)((char *)var2 + 0xa0));
	}
	if (*(int *)((char *)var2 + 0xa8) != 0)
	{
		njRotateZ((float *)0, (unsigned short)*(short *)((char *)var2 + 0xa8));
	}
	FUN_0067d2d0((float *)0, 2.0f, 2.0f, 2.0f);
}

// FUNCTION: SADX 0x006c1a90
void TaskBossDisp(struct task *tp)
{
	njPushMatrix(0);
	FUN_0067d830(0, 38.15999984741211, 0.0, 0.0);
	___njSetTexture(&texlist_egm1);
	late_DrawObjectClipMesh((struct obj *)&object_egm01_egm00_egm00, 1, 2.0);
	njPopMatrix(1);
	___njSetTexture(&texlist_egm1eggman);
	FUN_0067d830(0, 0.0, -0.7299995422363281, 0.0);
	ds_DrawObjectClip((struct obj *)&object_egman1_body_body, 2.0);
}

// FUNCTION: SADX 0x006c1bd0
static void TaskBossEnd(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct anywk *var2 = tp->awp;

	EraseDolbyCtrl(var1);
	*(short *)((char *)var2 + 4) = 0xe;
	BSetMotion(var1, (struct bosswk *)var2);
	FreeEgm1JetTask();
}

#pragma optimize("", off)
// STUB: SADX 0x006c1c00
static void TaskBossExec(struct task *tp)
{
}
#pragma optimize("", on)

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
