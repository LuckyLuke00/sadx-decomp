#include "decls.h"
extern struct obj object_cas_obj_cris_cris;
extern int DAT_05b9d838;

// FUNCTION: SADX 0x0087e360
void ObjectCasinoCrisDraw(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	if (CheckRangeOutWithR(tp, 360010.0f))
	{
		return;
	}
	SetObjectTexture2(0xc);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (*(int *)((char *)var1 + 8) + *(int *)((char *)var1 + 0x18))
	{
		njRotateY(0, *(unsigned short *)((char *)var1 + 8) + *(unsigned short *)((char *)var1 + 0x18));
	}
	ds_DrawModelClip(object_cas_obj_cris_cris.model, 1.0f);
	njPopMatrix(1);
}
