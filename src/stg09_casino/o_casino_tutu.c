#include "decls.h"
extern struct obj *DAT_04786eb0;
extern struct obj *DAT_04786ed8;

// FUNCTION: SADX 0x0087ee30
void ObjectCasinoTutuADraw(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOutWithR(tp, 62510.0f))
	{
		return;
	}
	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture2(0xc);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->value.w[0])
	{
		njRotateY(0, (unsigned short)var1->value.w[0]);
	}
	late_DrawModelClip((struct NJS_MODEL *)DAT_04786eb0, 0, 1.0f);
	if (var1->ang.y - var1->value.w[0])
	{
		njRotateY(0, (unsigned short)(var1->ang.y - var1->value.w[0]));
	}
	late_DrawObjectClip(DAT_04786ed8, 0, 1.0f);
	njPopMatrix(1);
}

// STUB: SADX 0x0087ef00
void ObjectCasinoTutuBDraw(struct task *tp)
{
}

// STUB: SADX 0x0087efc0
void ObjectCasinoTutuCDraw(struct task *tp)
{
}

#pragma optimize("", off)
// STUB: SADX 0x0087f530
void ObjectCasinoTutuAInit(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x0087f590
void ObjectCasinoTutuA(struct task *tp)
{
	if (CheckRangeOutWithR(tp, 62510.0f) == 0)
	{
		ObjectCasinoTutuAInit(tp);
	}
}

// STUB: SADX 0x0087f5c0
void ObjectCasinoTutuB(struct task *tp)
{
}

// STUB: SADX 0x0087f610
void ObjectCasinoTutuC(struct task *tp)
{
}
