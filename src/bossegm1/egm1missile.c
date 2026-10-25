#include "decls.h"
void ___njSetTexture(struct NJS_TEXLIST *texlist);
extern void njPushMatrix(float *);
void njTranslateV(float *, struct NJS_POINT3 *);
extern void njRotateY(float *, unsigned short);
extern void njRotateX(float *, unsigned short);
void late_DrawObjectClipEx(struct obj *obj, int flgs, float clipScl);
void njPopMatrix(int param_1);
extern struct obj *object_egg_m1_em_mis_em_mis;
extern struct NJS_TEXLIST texlist_egm1mis;

// STUB: SADX 0x006c4c20
void egm1missile_disp(struct task *tp)
{
	struct taskwk *var1;
	struct Angle3 *var2;
	struct NJS_POINT3 *var3;
	var1 = tp->twp;
	___njSetTexture(&texlist_egm1mis);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	var2 = &var1->ang;
	if (var2->y != 0)
	{
		njRotateY(0, (unsigned short)var2->y);
	}
	if (var2->x != 0)
	{
		njRotateX(0, (unsigned short)var2->x);
	}
	late_DrawObjectClipEx((struct obj *)&object_egg_m1_em_mis_em_mis, 0, 1.0f);
	njPopMatrix(1);
}
