#include "decls.h"
extern float DAT_02a6a8ec;
extern float c60_taileffpos_x;
extern float DAT_060c3358;
extern float DAT_060c335c;
extern long DAT_060c3354;
extern float DAT_060c32b8[16];
extern unsigned char DAT_060c3350;

// FUNCTION: SADX 0x006f86b0
void objDisplayT(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	___njSetTexture(&texlist_chaos6_effect);
	DAT_02a6a8ec = var1->counter.f;
	___njSetConstantMaterial((struct NJS_ARGB *)&DAT_02a6a8ec);
	njPushMatrix(NULL);
	njMultiMatrix(NULL, &DAT_060c32b8);
	FUN_0067d830(NULL, c60_taileffpos_x, DAT_060c3358, DAT_060c335c);
	if (c60_taileffang_y != 0)
	{
		njRotateY(NULL, (unsigned short)c60_taileffang_y);
	}
	if (DAT_060c3354 != 0)
	{
		njRotateZ(NULL, (unsigned short)DAT_060c3354);
	}
	if (c60_taileffang_x != 0)
	{
		njRotateX(NULL, (unsigned short)c60_taileffang_x);
	}
	late_DrawObjectClipMesh((struct obj *)&object_c6_taileff_taileff, 4, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x006f8780
void objNormalT(struct task *tp)
{
	struct taskwk *local_8 = tp->twp;
	switch (local_8->mode)
	{
	case 0:
		local_8->counter.f = local_8->counter.f + 0.01666666753590107f;
		if (local_8->counter.f >= 1.0f)
		{
			local_8->counter.f = 1.0f;
			local_8->mode = 1;
			objDisplayT(tp);
			return;
		}
		break;
	case 1:
		if (DAT_060c3350 == 0)
		{
			local_8->mode = 2;
			objDisplayT(tp);
			return;
		}
		break;
	case 2:
		local_8->counter.f = local_8->counter.f - 0.01666666753590107f;
		if (local_8->counter.f <= 0.0f)
		{
			FreeTask(tp);
			return;
		}
		break;
	}
	objDisplayT(tp);
}

// FUNCTION: SADX 0x006f8810
void Chaos6HTtaileff(struct task *tp)
{
	DAT_060c3350 = 1;
	tp->exec = objNormalT;
	tp->disp = objDisplayT;
}

// FUNCTION: SADX 0x006f8830
void Chaos6HTtaileffDisappear()
{
	DAT_060c3350 = 0;
}
