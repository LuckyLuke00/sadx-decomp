#include "decls.h"

// FUNCTION: SADX 0x0085e430
void Object_IcecapHasihasiDraw(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOut(tp))
	{
		return;
	}
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
	FUN_0067d2d0(0, var1->scl.x + 1.0f, var1->scl.y + 1.0f, var1->scl.z + 1.0f);
	ds_DrawObjectClip(object_snow_sn_h_hasi01a_sn_h_hasi01a, FUN_00500c70(var1->scl.x + 1.0f, var1->scl.y + 1.0f, var1->scl.z + 1.0f));
	njPopMatrix(1);
}

// FUNCTION: SADX 0x0085e530
void Object_IcecapHasihasiExec(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOut(tp))
	{
		return;
	}
	Object_IcecapHasihasiDraw(tp);
	if (!FUN_004c39c0(tp))
	{
		EntryColliList(var1);
	}
}

// FUNCTION: SADX 0x0085e570
void ObjectIcecapHasihasi(struct task *tp)
{
	struct taskwk *var1;
	if (CheckRangeOut(tp) == 0)
	{
		var1 = tp->twp;
		if (FUN_004c39c0(tp) == 0)
		{
			CCL_Init(tp, &object_hasihasi_info[0], 1, 4);
			CheckCollisionScale(var1);
		}
		tp->disp = Object_IcecapHasihasiDraw;
		tp->exec = Object_IcecapHasihasiExec;
		tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
	}
}
