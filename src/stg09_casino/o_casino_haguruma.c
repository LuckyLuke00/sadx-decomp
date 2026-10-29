#include "decls.h"
void ObjectCasinoHagurumaDraw(struct task *tp);

// FUNCTION: SADX 0x0087e100
void ObjectCasinoHagurumaDraw(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	if (CheckRangeOutWithR(tp, 62510.0f))
	{
		return;
	}
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, (Uint16)var1->ang.y);
	}
	SetObjectTexture2(0xc);
	ds_DrawObjectClip(object_csn_obj_haguruma_obj_haguruma, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x0087e2d0
void ObjectCasinoHagurumaInit(struct task *tp)
{
	struct taskwk *var1;
	var1 = tp->twp;
	if (FUN_004c39c0(tp) == 0)
	{
		ObjCasino_InitGColl(tp, (struct obj *)&object_csn_obj_haguruma_obj_haguruma, 97.0f, 0x8000000);
	}
	tp->disp = ObjectCasinoHagurumaDraw;
	tp->exec = ObjectCasinoHagurumaExec;
	tp->dest = ObjectCasinoManfEnd;
	var1->wtimer = 0;
	var1->mode = 0;
}

// FUNCTION: SADX 0x0087e330
void ObjectCasinoHaguruma(struct task *tp)
{
	if (CheckRangeOutWithR(tp, 62510.0f) == 0)
	{
		ObjectCasinoHagurumaInit(tp);
	}
}
