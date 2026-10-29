#include "decls.h"

// FUNCTION: SADX 0x0068ab70
void ObjectDisplayMiles(struct task *tp)
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
	ds_DrawObjectClip(object_sssikake_hwbhutter_blkn_hwbhutter_blkn, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x0068abe0
void ObjectBroken(struct task *tp)
{
	if (FUN_004c39c0(tp) != 0)
	{
		ObjectDisplayMiles(tp);
	}
	else if (CheckRangeOut(tp) == 0)
	{
		ObjectDisplayMiles(tp);
	}
}

// STUB: SADX 0x0068ac10
void ObjectMainMiles(struct task *tp)
{
}

// STUB: SADX 0x0068ada0
void ObjectSSHwbshutter(struct task *tp)
{
}
