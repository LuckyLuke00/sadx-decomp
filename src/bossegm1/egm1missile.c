#include "decls.h"
void ___njSetTexture(struct NJS_TEXLIST *texlist);
void late_DrawObjectClipEx(struct obj *obj, int flgs, float clipScl);
extern struct obj *object_egg_m1_em_mis_em_mis;
extern struct NJS_TEXLIST texlist_egm1mis;

// FUNCTION: SADX 0x006c4c20
void egm1missile_disp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	___njSetTexture(&texlist_egm1mis);
	njPushMatrix(NULL);
	njTranslateV(NULL, &var1->pos);
	if (var1->ang.y != 0)
	{
		njRotateY(NULL, (unsigned short)var1->ang.y);
	}
	if (var1->ang.x != 0)
	{
		njRotateX(NULL, (unsigned short)var1->ang.x);
	}
	late_DrawObjectClipEx((struct obj *)&object_egg_m1_em_mis_em_mis, 0, 1.0f);
	njPopMatrix(1);
}

// STUB: SADX 0x006c50b0
void FUN_006c50b0(struct NJS_POINT3 *param_1)
{
}
