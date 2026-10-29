#include "decls.h"
extern int DAT_05b9d838;

// FUNCTION: SADX 0x008a9eb0
void Disp2Task(struct task *tp)
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
	late_DrawModelClip(model_hasi_enhasi_bmerge1, 1, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x008a9f20
void Disp3Task(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	late_DrawModelClip(model_hasi_enhasi_enhasi, 1, 1.0f);
	njPopMatrix(1);
}
