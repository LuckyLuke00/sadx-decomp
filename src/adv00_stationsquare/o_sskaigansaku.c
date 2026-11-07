#include "decls.h"

// GLOBAL: SADX 0x026dd970
static struct CCL_INFO object_c_info[1];

// FUNCTION: SADX 0x0068a220
void SakuDisp(struct task *tp)
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
		njRotateY(0, (Uint16)var1->ang.y);
	}
	ds_DrawObjectClip(object_sssikake_kaigansaku_kaigansaku, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x0068a3a0
void E_MatoDisp(struct task *tp)
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
		njRotateY(0, (Uint16)var1->ang.y);
	}
	ds_DrawObjectClip(object_sssikake_kaiganmato_kaiganmato, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x0068a410
void MatoDisp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		SetObjectTexture();
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		if (var1->ang.x != 0)
		{
			njRotateX(0, (unsigned short)var1->ang.x);
		}
		if (var1->ang.y != 0)
		{
			njRotateY(0, (unsigned short)var1->ang.y);
		}
		if (var1->mode == 1)
		{
			SaveConstantAttr();
			OnConstantAttr(0, 0x100000);
			SetMaterial(var1->timer.f, 0.0f, 0.0f, 0.0f);
			ds_DrawObjectClip(object_sssikake_kaiganmato_kaiganmato, 1.0f);
			ResetMaterial();
			LoadConstantAttr();
		}
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x0068a4d0
void SakuExec(struct task *tp)
{
	EntryColliList(tp->twp);
	SakuDisp(tp);
}

// STUB: SADX 0x0068a6c0
void MatoExec(struct task *tp)
{
}

// FUNCTION: SADX 0x0068a7c0
void MatoInit(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->timer.f = 1.0;
	var1->value.f = 1.0;
	var1->mode = 1;
	var1->counter.f = 2.6f;
	var1->wtimer = 0;
	var1->ang.x = 0;
	var1->ang.z = 0x7d0;
	tp->exec = MatoExec;
	tp->disp = MatoDisp;
}

// STUB: SADX 0x0068a800
void E_MatoExec(struct task *tp)
{
}

// FUNCTION: SADX 0x0068a8c0
void E_MatoInit(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	EnemyInitialize(tp, var1);
	var1->mode = 0;
	CCL_Init(tp, object_c_info, 1, 2);
	tp->exec = E_MatoExec;
	tp->disp = E_MatoDisp;
	tp->dest = FUN_00850d10;
}
