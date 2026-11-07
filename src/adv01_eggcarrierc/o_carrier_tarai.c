#include "decls.h"
extern struct CCL_INFO c_info_button[1];
extern struct NJS_TEXLIST texlist_ec_tarai;
extern int DAT_05b9d838;
extern struct obj *DAT_060eea98;
extern float TARAI_Y;
void TaraiDisp(struct task *tp);
void TaraiExec(struct task *tp);

// STUB: SADX 0x006a4860
float GetPlayerHeight()
{
	return (float)0;
}

// FUNCTION: SADX 0x006a4cc0
void TaraiDisp(struct task *tp)
{
	struct taskwk *var1;
	struct motionwk *var2;

	var1 = tp->twp;
	var2 = tp->mwp;
	if (DAT_05b9d838 == 0)
	{
		___njSetTexture(&texlist_ec_tarai);
		njPushMatrix(NULL);
		njTranslateV(NULL, &var1->pos);
		if (var2->ang_aim.y != 0)
		{
			njRotateY(NULL, (unsigned short)var2->ang_aim.y);
		}
		if (var2->ang_spd.x != 0)
		{
			njRotateX(NULL, (unsigned short)var2->ang_spd.x);
		}
		if (var2->ang_spd.y != 0)
		{
			njRotateY(NULL, (unsigned short)var2->ang_spd.y);
		}
		if (var2->ang_spd.z != 0)
		{
			njRotateZ(NULL, (unsigned short)var2->ang_spd.z);
		}
		SetMaterial(var1->value.f, 0.0f, 0.0f, 0.0f);
		late_DrawObjectClipMesh(*(struct obj **)((char *)DAT_060eea98 + 0x18), 1, 1.0f);
		ResetMaterial();
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x006a4da0
void TateTaraiDisp(struct task *tp)
{
	struct taskwk *var1;
	struct motionwk *var2;

	var1 = tp->twp;
	var2 = tp->mwp;
	if (DAT_05b9d838 == 0)
	{
		___njSetTexture(&texlist_ec_tarai);
		njPushMatrix(NULL);
		njTranslateV(NULL, &var1->pos);
		FUN_0067d830(NULL, -1.5f, 0.0f, 0.0f);
		if (var1->ang.z != 0)
		{
			njRotateZ(NULL, (unsigned short)var1->ang.z);
		}
		FUN_0067d830(NULL, 0.0f, 5.0f, 0.0f);
		if (var2->ang_aim.z != 0)
		{
			njRotateZ(NULL, (unsigned short)var2->ang_aim.z);
		}
		SetMaterial(var1->value.f, 0.0f, 0.0f, 0.0f);
		late_DrawObject(*(struct obj **)((char *)DAT_060eea98 + 0x18), 1);
		ResetMaterial();
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x006a4e90
void HugeTaraiDisp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		___njSetTexture(&texlist_ec_tarai);
		njPushMatrix(NULL);
		njTranslateV(NULL, &var1->pos);
		if (var1->ang.y != 0)
		{
			njRotateY(NULL, (unsigned short)var1->ang.y);
		}
		if (var1->ang.z != 0)
		{
			njRotateZ(NULL, (unsigned short)var1->ang.z);
		}
		FUN_0067d2d0((float *)0, var1->scl.x, var1->scl.y, var1->scl.z);
		SetMaterial(var1->value.f, 0.0f, 0.0f, 0.0f);
		late_DrawObject((struct obj *)(DAT_060eea98->ang[1]), 1);
		ResetMaterial();
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x006a4f50
void BadeffDisp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	___njSetTexture(&texlist_ec_tarai);
	SetMaterial(var1->counter.f, 0.0f, 0.0f, 0.0f);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	late_DrawObject(*(struct obj **)((char *)DAT_060eea98 + 0x28), 4);
	njPopMatrix(1);
	ResetMaterial();
}

// STUB: SADX 0x006a5790
void BadeffExec(struct task *tp)
{
}

// FUNCTION: SADX 0x006a5810
void TaraiInit(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	var1->pos.y = TARAI_Y;
	var1->mode = 0x13;
	var1->wtimer = 0;
	tp->exec = TaraiExec;
	tp->disp = TaraiDisp;
}

// FUNCTION: SADX 0x006a5840
void TateTaraiInit(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	var1->pos.y = TARAI_Y;
	var1->wtimer = 0;
	var1->mode = 0x11;
	tp->exec = TateTaraiExec;
	tp->disp = TateTaraiDisp;
}

// FUNCTION: SADX 0x006a5870
void HugeTaraiInit(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	var1->pos.y = TARAI_Y;
	var1->wtimer = 0;
	var1->mode = 0x14;
	tp->exec = HugeTaraiExec;
	tp->disp = HugeTaraiDisp;
}

// FUNCTION: SADX 0x006a58a0
void FUN_006a58a0(float param_1, float param_2, float param_3)
{
	struct task *var1 = CreateElementalTask(2, 3, BadeffExec);
	struct taskwk *var2 = var1->twp;
	var2->pos.x = param_1;
	var2->pos.y = param_2;
	var2->pos.z = param_3;
	var2->counter.f = -1.0f;
	var2->timer.f = 0.05f;
	var1->disp = BadeffDisp;
}

// FUNCTION: SADX 0x006a5d10
void ButtonInit(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->mode = 0;
	var1->smode = 0xf;
	var1->wtimer = 0;
	CCL_Init(tp, c_info_button, 1, 4);
	tp->exec = ButtonExec;
	tp->disp = ButtonDisp;
}
