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
		njPushMatrix((float *)0);
		njTranslateV((float *)0, &var1->pos);
		if (*(int *)((char *)var1 + 0x1c) != 0)
		{
			njRotateZ((float *)0, (unsigned short)*(short *)((char *)var1 + 0x1c));
		}
		if (*(int *)((char *)var1 + 0x14) != 0)
		{
			njRotateX((float *)0, *(unsigned short *)((char *)var1 + 0x14));
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
