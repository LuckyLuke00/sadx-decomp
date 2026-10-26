#include "decls.h"
extern struct obj object_l01_wt_hebimizu_wt_hebimizu[];

// FUNCTION: SADX 0x008535a0
void dispcNormal(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	late_DrawObjectClipEx(object_lwobj_lwswitch_lwswitch, 0, 1.0f);
	njPopMatrix(1);
}
