#include "decls.h"
static void ExecATask(struct task *tp);
static void DispATask(struct task *tp);
static void DesertATask(struct task *tp);

// GLOBAL: SADX 0x0270a848
static struct CCL_INFO ColliInfo[2];

extern struct task *DAT_060b90fc;

// FUNCTION: SADX 0x006b0790
static void DispATask(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct task *var2 = GetPlayerTaskPointer(0);

	if (var2->exec == 0)
	{
		return;
	}
	___njSetTexture(&texlist_mr_egg);
	njPushMatrix(NULL);
	njTranslateV(NULL, &var1->pos);
	if (*(int *)((char *)var1 + 0x18) != 0)
	{
		njRotateY(NULL, *(unsigned short *)((char *)var1 + 0x18));
	}
	ds_DrawObjectClip((struct obj *)&object_tamago_e2_tama_e2_tama, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x006b0800
static void DesertATask(struct task *tp)
{
	if (DAT_060b90fc == tp)
	{
		DAT_060b90fc = 0;
	}
}

#pragma optimize("", off)
// STUB: SADX 0x006b0820
static void ExecATask(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x006b0940
void ObjectMysticRuinEgg(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	var1->ang.x = 0;
	var1->ang.z = 0;
	var1->wtimer = 0;
	if (FUN_004c39c0(tp))
	{
		DispATask(tp);
		return;
	}
	if (SeqCheckFlag(0x50))
	{
		FreeTask(tp);
		return;
	}
	if (DAT_060b90fc != 0)
	{
		FreeTask(tp);
		return;
	}
	DAT_060b90fc = tp;
	var1->wtimer = ((short)(DAT_05b9d724 << 8) | DAT_05b9d744);
	var1->mode = GetHoldingItemIDP(0) == 0xa ? 3 : 0;
	CCL_Init(tp, ColliInfo, 2, 4);
	SET_COLLI_RANGE(var1->cwp, 50.0f);
	ObjectMovableInitialize(var1, tp->mwp, 4);
	var1->flag |= 2;
	tp->exec = ExecATask;
	tp->disp = DispATask;
	tp->dest = DesertATask;
	var1->mode = 1;
}
