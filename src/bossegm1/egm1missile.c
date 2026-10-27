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

// FUNCTION: SADX 0x006c4c20
void egm1missile_disp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	___njSetTexture(&texlist_egm1mis);
	njPushMatrix((float *)0);
	njTranslateV((float *)0, &var1->pos);
	if (*(int *)((char *)var1 + 0x18) != 0)
	{
		njRotateY((float *)0, *(unsigned short *)((char *)var1 + 0x18));
	}
	if (*(int *)((char *)var1 + 0x14) != 0)
	{
		njRotateX((float *)0, *(unsigned short *)((char *)var1 + 0x14));
	}
	late_DrawObjectClipEx((struct obj *)&object_egg_m1_em_mis_em_mis, 0, 1.0f);
	njPopMatrix(1);
}

// STUB: SADX 0x006c50b0
void FUN_006c50b0(struct NJS_POINT3 *posp)
{
}
