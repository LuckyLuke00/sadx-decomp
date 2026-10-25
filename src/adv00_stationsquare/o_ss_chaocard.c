#include "decls.h"
extern int DAT_05b9d838;
extern struct taskwk *DAT_05baf368[8];

// FUNCTION: SADX 0x006862e0
static void disp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, var1->ang.y);
	}
	ds_DrawObjectClip(object_ssobj_chaocard_chaocard, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x00686350
static void Exec(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOut(tp))
	{
		return;
	}
	if (FUN_004c39c0(tp))
	{
		disp(tp);
		return;
	}
	disp(tp);
	switch (var1->mode)
	{
	case 0:
	case 1:
		ObjectMovableSRegularExecute(tp);
		var1->ang.y += 0x400;
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
			SetHoldingItemIDP(0, 0x21);
			var1->mode = 2;
			HintMainMessages((const char **)get_message);
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
			return;
		}
		SetContinue(tp);
		return;
	case 6:
		DeadOut(tp);
		break;
	}
}

// FUNCTION: SADX 0x00686470
void ObjectSSChaocard(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct motionwk *var2 = tp->mwp;

	var1->ang.x = 0;
	var1->ang.z = 0;
	var1->wtimer = 0;
	if (!FUN_004c39c0(tp))
	{
		switch (GetPlayerCharacterName(0))
		{
		case 0:
		case 2:
		case 3:
		case 5:
		case 6:
		case 7:
			break;
		default:
			DeadOut(tp);
			return;
		}
	}
	var1->mode = GetHoldingItemIDP(0) == 0x21 ? 3 : 0;
	if (!FUN_004c39c0(tp))
	{
		CCL_Init(tp, obj_c_info, 2, 4);
	}
	ObjectMovableInitialize(var1, var2, 4);
	tp->exec = Exec;
	tp->disp = disp;
}
