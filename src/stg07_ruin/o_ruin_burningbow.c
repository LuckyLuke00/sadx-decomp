#include "decls.h"
extern struct obj object_lwobj_bow_bow[1];
extern struct obj object_lwobj_arrow_arrow[1];

// FUNCTION: SADX 0x00855220
void Object_Ruin_BurningArrow_Display(struct task *tp)
{
	struct taskwk *var1;
	var1 = tp->twp;
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	SetObjectTexture();
	if (var1->ang.y != 0)
	{
		njRotateY(0, (Uint16)var1->ang.y);
	}
	___dsDrawModel(object_lwobj_arrow_arrow[0].model);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x00855280
void Object_Ruin_BurningBow_Display(struct task *tp)
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
	ds_DrawModelClip(object_lwobj_bow_bow[0].model, 1.0f);
	njPopMatrix(1);
}
