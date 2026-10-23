#include "decls.h"
extern int DAT_060dc4dc;

// FUNCTION: SADX 0x0088e030
void AnnouncementTask(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	switch (var1->mode)
	{
	case 0:
		var1->wtimer = 0xb4;
		var1->mode = 1;
		break;
	case 1:
		var1->wtimer--;
		if (var1->wtimer == 0)
		{
			Serif_Play(0x639);
			var1->wtimer = 0xf0;
			var1->mode = 2;
		}
		break;
	case 2:
		var1->wtimer--;
		if (var1->wtimer == 0)
		{
			Serif_Play(0x638);
			var1->wtimer = 0xf0;
			var1->mode = 3;
		}
		break;
	case 3:
		FreeTask(tp);
		break;
	}
}

// FUNCTION: SADX 0x0088e0c0
void AnnouncementTask2(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	switch (var1->mode)
	{
	case 0:
		if (DAT_060dc4dc != 0)
		{
			var1->mode = 4;
			return;
		}
		var1->wtimer = 0x78;
		var1->mode = 1;
		DAT_060dc4dc = 1;
		return;
	case 1:
		var1->wtimer--;
		if (var1->wtimer == 0)
		{
			Serif_Play(0x634);
			var1->wtimer = 0x1a4;
			var1->mode = 2;
		}
		return;
	case 2:
		var1->wtimer--;
		if (var1->wtimer == 0)
		{
			Serif_Play(0x634);
			var1->wtimer = 0x1a4;
			var1->mode = 3;
		}
		return;
	case 3:
		var1->wtimer--;
		if (var1->wtimer == 0)
		{
			Serif_Play(0x634);
			var1->wtimer = 0x1a4;
			var1->mode = 4;
		}
		return;
	case 4:
		FreeTask(tp);
		return;
	}
}

// FUNCTION: SADX 0x0088e190
void FUN_0088e190()
{
	SetViewAngle(0x2aaa);
	___njSetBackColor(0, 0, 0);
}

// FUNCTION: SADX 0x0088e1b0
void ACT3_init(struct task *tp)
{
	CreateElementalTask(2, 3, GachaponManager);
	ADXTaskInit();
	RoundBGM_Play(0x2a);
	ClearAllSwitches();
	TexMakeInit();
	*(int *)&DAT_05cbef64 = 0xffffffff;
	if (GetPlayerNumber() == 6)
	{
		CreateElementalTask(2, 3, AnnouncementTask);
	}
	if (GetPlayerNumber() == 0)
	{
		CreateElementalTask(2, 3, AnnouncementTask2);
	}
}
