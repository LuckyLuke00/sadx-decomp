#include "decls.h"

// FUNCTION: SADX 0x0068df80
void ObjectDisplayOn(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture();
	njPushMatrix(0);
	FUN_0067d830(0, var1->pos.x, var1->pos.y - 2.799999952316284, var1->pos.z);
	if (var1->ang.y)
	{
		njRotateY(0, var1->ang.y);
	}
	ds_DrawObjectClip(object_sssikake_eggstand_eggstand, 1.0f);
	FUN_0067d830(0, 0.0f, 3.5f, 0.0f);
	ds_DrawObjectClip(object_nisetama_tamago_tamago, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x0068e1b0
void ObjectMainOn(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (FUN_004c39c0(tp) == 0)
	{
		EntryColliList(var1);
	}
	ObjectDisplayOn(tp);
}
