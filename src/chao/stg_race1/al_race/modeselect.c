#include <stdlib.h>
#include "decls.h"

extern struct task *DAT_05b35c28;
extern int DAT_05b9d838;
extern short DAT_05b9d744;

extern struct obj object_medal_pal_pal;
extern struct obj object_medal_ame_ame;
extern struct obj object_medal_saf_saf;
extern struct obj object_medal_rub_rub;
extern struct obj object_medal_eme_eme;

// GLOBAL: SADX 0x05b35c24
static struct task **DAT_05b35c24;

// GLOBAL: SADX 0x009614c8
static const struct AlrDiamdlData mdata[5] = { { &object_medal_pal_pal }, { &object_medal_ame_ame }, { &object_medal_saf_saf }, { &object_medal_rub_rub }, { &object_medal_eme_eme } };

// FUNCTION: SADX 0x00488c80
void AllClearEntryDialog()
{
	if (DAT_05b35c24)
	{
		for (int var1 = 0; var1 < 12; var1++)
		{
			struct task *var2 = DAT_05b35c24[var1];
			if (var2)
			{
				DestroyTask(var2);
				DAT_05b35c24[var1] = 0;
			}
		}
	}
}

// FUNCTION: SADX 0x00488cc0
int SetCommandToDialog(int num, int command)
{
	if (DAT_05b35c24 && DAT_05b35c24[num])
	{
		DAT_05b35c24[num]->twp->smode = command;
		return 1;
	}
	return 0;
}

// FUNCTION: SADX 0x00488cf0
static void FUN_00488cf0(struct taskwk *param_1)
{
	if (param_1->scl.x > 1.0f)
	{
		param_1->scl.x -= 0.05f;
		if (param_1->scl.x < 1.0f)
		{
			param_1->scl.x = 1.0f;
		}
	}
	if (param_1->scl.y > 1.0f)
	{
		param_1->scl.y -= 0.05f;
		if (param_1->scl.y < 1.0f)
		{
			param_1->scl.y = 1.0f;
		}
	}
}

// FUNCTION: SADX 0x00488d60
static void dialog_select(struct taskwk *twp)
{
	float local_8 = njSin(twp->ang.x) * 0.125 + 0.125;
	twp->ang.x += 0x2d8;
	twp->scl.y = twp->scl.x = local_8 + 1.0;
}

// FUNCTION: SADX 0x00488da0
static void FUN_00488da0(struct taskwk *param_1)
{
	param_1->scl.y = param_1->scl.x = 1.25f;
}

// FUNCTION: SADX 0x00488db0
static void FUN_00488db0(struct taskwk *param_1)
{
	switch (param_1->mode)
	{
	case 0:
		param_1->scl.x = 0.0f;
		param_1->wtimer = 0;
		param_1->mode++;
		param_1->scl.y = 1.0f;
	case 1:
		param_1->scl.x += 0.1f;
		if (param_1->scl.x > 1.0f)
		{
			param_1->scl.x = 1.0f;
			if (param_1->wtimer > 60)
			{
				param_1->mode++;
			}
		}
		break;
	case 2:
		param_1->scl.z -= 0.05f;
		if (param_1->scl.z < -1.0f)
		{
			param_1->scl.z = -1.0f;
			param_1->smode = 8;
		}
		break;
	}
}

// FUNCTION: SADX 0x00488e30
static void dialog_dsp(struct taskwk *twp)
{
	NJS_SPRITE sprite;
	float local_28 = -2.0f;

	if (!DAT_05b9d838)
	{
		if (twp->smode == 4 || twp->smode == 5)
		{
			local_28 = -1.9f;
		}
		else if (twp->smode == 2)
		{
			local_28 = -45.0f;
		}
		sprite.p.x = twp->pos.x;
		sprite.ang = 0;
		sprite.p.y = twp->pos.y;
		sprite.p.z = 0.0f;
		struct NJS_TEXLIST *var1 = &texlist_chao_hyouji;
		if (twp->btimer < 0x1a)
		{
			var1 = &texlist_obj_al_race;
		}
		sprite.sx = twp->scl.x;
		sprite.tlist = var1;
		sprite.sy = twp->scl.y;
		sprite.tanim = (NJS_TEXANIM *)anim_dialog;
		___njSetTexture(var1);
		___njColorBlendingMode(0, 8);
		___njColorBlendingMode(1, 6);
		if (twp->smode == 1)
		{
			SetMaterial(twp->scl.z, 1.0f, 0.6f, 0.6f);
		}
		else if (twp->smode == 5 || twp->smode == 3)
		{
			SetMaterial(twp->scl.z, 1.0f, 1.0f, 0.5f);
		}
		else
		{
			SetMaterial(twp->scl.z, 1.0f, 1.0f, 1.0f);
		}
		int var2 = twp->btimer;
		float local_28g = local_28;
		if (local_28g >= -3.0f && local_28g < 12048.0f)
		{
			local_28g += 22048.0;
		}
		late_DrawSprite2D(&sprite, var2, local_28g, 0x22, 4);
		ResetMaterial();
	}
}

// FUNCTION: SADX 0x00488f90
void ClearPanel()
{
	if (DAT_05b35c28)
	{
		DestroyTask(DAT_05b35c28);
		DAT_05b35c28 = 0;
	}
}

// FUNCTION: SADX 0x00488fb0
static void Jewel_new(struct task *tp)
{
	struct NJS_POINT3 pos;
	float local_18;

	if (!(char)DAT_05b9d744)
	{
		DestroyTask(tp);
		return;
	}
	if (!DAT_05b9d838)
	{
		struct taskwk *var1 = tp->twp;
		var1->ang.z += 0x222;
		var1->ang.y += 0x16c;
		struct obj *var2 = (struct obj *)var1->value.ptr;
		local_18 = njCos(var1->ang.z);
		___njSetTexture(&texlist_obj_al_race);
		njPushMatrix(0);
		struct NJS_POINT3 *var3 = &var1->pos;
		local_18 = local_18 + var3->y;
		FUN_0067d830(0, var3->x, local_18, var3->z);
		if (var1->ang.y)
		{
			njRotateY(0, (unsigned short)var1->ang.y);
		}
		FUN_0067d2d0(0, 2.7f, 2.7f, 2.7f);
		___dsDrawObject(var2);
		njPopMatrix(1);
		if (var1->wtimer++ > 3)
		{
			local_18 = rand() * 3.0517578125e-05;
			pos.x = local_18 * 10.0 - 5.0;
			local_18 = rand() * 3.0517578125e-05;
			pos.z = local_18 * 10.0 - 5.0;
			local_18 = rand() * 3.0517578125e-05;
			pos.y = local_18 * 10.0 - 5.0;
			pos.x = var3->x + pos.x;
			pos.y = pos.y + var3->y;
			pos.z = var3->z + pos.z;
			CreateKiran2(&pos, 0.35f, 0.35f);
			var1->wtimer = 0;
		}
	}
}

// FUNCTION: SADX 0x00489180
void WinDestructor()
{
	if (DAT_05b35c24)
	{
		AllClearEntryDialog();
		Free(DAT_05b35c24);
	}
	DAT_05b35c24 = 0;
}

// FUNCTION: SADX 0x004891b0
static void dialog_new(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct task **var2 = (struct task **)var1->counter.ptr;

	var1->wtimer++;
	if (*var2 != tp)
	{
		var1->smode = 8;
	}
	switch (var1->smode)
	{
	case 4:
	case 5:
		dialog_select(var1);
		dialog_dsp(var1);
		var1->smode = 0;
		break;
	case 6:
		FUN_00488da0(var1);
		dialog_dsp(var1);
		var1->smode = 0;
		break;
	case 7:
		break;
	case 8:
		if (*var2 == tp)
		{
			*var2 = 0;
		}
		DestroyTask(tp);
		break;
	case 9:
	case 10:
	case 11:
		FUN_00488db0(var1);
		dialog_dsp(var1);
		break;
	case 0:
	case 1:
	case 2:
	case 3:
		FUN_00488cf0(var1);
		dialog_dsp(var1);
		var1->smode = 0;
		break;
	default:
		FUN_00488cf0(var1);
		dialog_dsp(var1);
		var1->smode = 0;
		break;
	}
}

// FUNCTION: SADX 0x00489260
void Jewel_Create(int cup, struct NJS_POINT3 *pos)
{
	int var1;

	switch (cup)
	{
	case 0:
		var1 = 0;
		break;
	case 1:
		var1 = 1;
		break;
	case 2:
		var1 = 2;
		break;
	case 3:
		var1 = 3;
		break;
	case 4:
		var1 = 4;
		break;
	default:
		return;
	}
	struct task *var2 = CreateElementalTask(2, 6, Jewel_new);
	if (var2)
	{
		struct taskwk *var3 = var2->twp;
		var3->pos = *pos;
		var3->ang.x = 0;
		var3->ang.y = 0;
		var3->ang.z = 0;
		var3->wtimer = 0;
		var3->value.ptr = (void *)mdata[var1].obj;
	}
}

// FUNCTION: SADX 0x00489300
static struct task *dialog_create(int id, float pos_x, float pos_y, struct task **entry)
{
	if (*entry)
	{
		DestroyTask(*entry);
	}
	struct task *var1 = CreateElementalTask(2, 6, dialog_new);
	if (var1)
	{
		struct taskwk *var2 = var1->twp;
		var2->scl.z = 1.0f;
		var2->wtimer = 0;
		var2->btimer = id;
		var2->pos.x = pos_x;
		var2->pos.y = pos_y;
		var2->mode = 0;
		var2->smode = 0;
		var2->counter.ptr = entry;
		var2->scl.y = var2->scl.x = 1.0f;
		*entry = var1;
		return var1;
	}
	return 0;
}

// FUNCTION: SADX 0x00489360
static void FUN_00489360(unsigned char param_1, float param_2, float param_3)
{
	if (DAT_05b35c24)
	{
		dialog_create(param_1, param_2, param_3, DAT_05b35c24);
	}
}

// FUNCTION: SADX 0x00489390
void CallStart()
{
	FUN_00489360(0x14, 320.0f, 240.0f);
}

// FUNCTION: SADX 0x004893c0
void CallGoalin()
{
	FUN_00489360(0x15, 320.0f, 240.0f);
}

// FUNCTION: SADX 0x004893f0
void CallCool()
{
	FUN_00489360(0x16, 320.0f, 240.0f);
}

// FUNCTION: SADX 0x00489420
void CallJewelGet()
{
	FUN_00489360(0x17, 320.0f, 240.0f);
}
