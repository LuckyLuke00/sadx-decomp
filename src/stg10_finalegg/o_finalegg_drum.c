#include "decls.h"
extern int DAT_05b9d838;
extern struct obj object_dramcan_can_can;

// FUNCTION: SADX 0x00897b70
void DrumPartsDisplayer(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		SetObjectTexture();
		njPushMatrix(NULL);
		njTranslateV(NULL, &var1->pos);
		if (var1->ang.z != 0)
		{
			njRotateZ(NULL, (unsigned short)(short)var1->ang.z);
		}
		if (var1->ang.x != 0)
		{
			njRotateX(NULL, (unsigned short)var1->ang.x);
		}
		___dsDrawModel((struct NJS_MODEL *)var1->counter.ptr);
		njPopMatrix(1);
	}
}

// STUB: SADX 0x00897bf0
void EffectBomb(struct sp_task *tp, struct sp_link *lp)
{
}

// FUNCTION: SADX 0x00897eb0
void DrumDisplayer(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	ds_DrawObjectClip(&object_dramcan_can_can, 1.0f);
	njPopMatrix(1);
}
