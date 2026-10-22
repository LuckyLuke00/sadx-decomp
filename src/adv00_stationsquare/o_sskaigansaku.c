#include "decls.h"

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
		njRotateY(0, var1->ang.y);
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
		njRotateY(0, var1->ang.y);
	}
	ds_DrawObjectClip(object_sssikake_kaiganmato_kaiganmato, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x0068a4d0
void SakuExec(struct task *tp)
{
	EntryColliList(tp->twp);
	SakuDisp(tp);
}

// STUB: SADX 0x0068a7c0
void MatoInit(struct task *tp)
{
}
