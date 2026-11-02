#include "decls.h"

// GLOBAL: SADX 0x026dd198
static char *get_message[5];

// GLOBAL: SADX 0x026dd110
static struct CCL_INFO cci_sscard[2];

static void dispSSCard(struct task *tp);
static void exitSSCard(struct task *tp);
static long SeqCheck();
static void Exec(struct task *tp);
extern unsigned char DAT_060b5fdc;

#pragma optimize("", off)
// STUB: SADX 0x006882b0
static long SeqCheck()
{
	return (long)0;
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00688370
static void dispSSCard(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct task *var2 = GetPlayerTaskPointer(0);
	if (var2->exec != NULL)
	{
		njPushMatrix(NULL);
		njTranslateV(NULL, &var1->pos);
		if (*(int *)((char *)var1 + 0x18) != 0)
		{
			njRotateY(NULL, *(unsigned short *)((char *)var1 + 0x18));
		}
		SetObjectTexture();
		late_ActionClipMesh((NJS_ACTION *)(*(int *)((char *)var1 + 8)), *(float *)((char *)var1 + 0xc), 0, 1.0f);
		njPopMatrix(1);
		if (FUN_004c39c0(tp) == 0)
		{
			if ((var1->flag & 0x1000) != 0)
			{
				*(float *)((char *)var1 + 0xc) = 0.0f;
				*(int *)((char *)var1 + 0x18) = -DAT_05baf368[0]->ang.y;
				return;
			}
			float var3 = *(float *)((char *)var1 + 0xc) + 0.5;
			*(float *)((char *)var1 + 0xc) = var3;
			struct NJS_MOTION *var4 = *(struct NJS_MOTION **)((char *)(*(void **)((char *)var1 + 8)) + 4);
			if ((float)(unsigned int)var4->nbFrame <= var3)
			{
				*(float *)((char *)var1 + 0xc) = 0.0f;
			}
		}
	}
}

// FUNCTION: SADX 0x00688450
static void exitSSCard(struct task *tp)
{
	tp->ocp->ssCondition &= 0xbfff;
	DAT_060b5fdc = 0;
}

// FUNCTION: SADX 0x00688470
static void Exec(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOut(tp))
	{
		return;
	}
	if (FUN_004c39c0(tp))
	{
		dispSSCard(tp);
		return;
	}
	dispSSCard(tp);
	switch (var1->mode)
	{
	case 0:
	case 1:
		ObjectMovableSRegularExecute(tp);
		if (var1->mode == 1)
		{
			var1->wtimer++;
			if (var1->wtimer > 0x708)
			{
				FreeTask(tp);
			}
		}
		if (var1->flag & 0x1000)
		{
			SetHoldingItemIDP(0, 1);
			var1->mode = 2;
			HintMainMessagesTime((const char **)get_message[DAT_05b3ebbc], 0xb4);
		}
		break;
	case 2:
		var1->ang.y = -DAT_05baf368[0]->ang.y;
		ObjectMovableSRegularExecute(tp);
		if (!(var1->flag & 0x1000))
		{
			SetHoldingItemIDP(0, 0);
			var1->wtimer = 0;
			var1->mode = 1;
			tp->ocp->ssCondition &= 0xbfff;
			return;
		}
		SetContinue(tp);
		return;
	}
}

// FUNCTION: SADX 0x00688570
void ObjectSSKeyice(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct motionwk *var2 = tp->mwp;

	var1->ang.x = 0;
	var1->ang.z = 0;
	var1->wtimer = 0;
	if (!FUN_004c39c0(tp) && SeqCheck() == 0)
	{
		return;
	}
	if (DAT_060b5fdc != 0 && tp->ocp != 0)
	{
		FreeTask(tp);
		return;
	}
	DAT_060b5fdc = 1;
	var1->mode = GetHoldingItemIDP(0) == 1 ? 3 : 0;
	var1->counter.l = (long)&action_ssobj_keyice;
	if (!FUN_004c39c0(tp))
	{
		CCL_Init(tp, cci_sscard, 2, 4);
	}
	ObjectMovableInitialize(var1, var2, 4);
	var1->flag |= 2;
	tp->exec = Exec;
	tp->dest = exitSSCard;
	tp->disp = dispSSCard;
}
