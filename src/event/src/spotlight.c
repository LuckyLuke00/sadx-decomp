#include "decls.h"
void FUN_0067d2d0(float *param_1, float param_2, float param_3, float param_4);
void late_DrawObjectClipEx(struct obj *obj, int flgs, float clipScl);
extern struct NJS_TEXLIST texlist_ev_spotlight;
extern struct obj _object_heli_light_light[1];

// FUNCTION: SADX 0x007da1a0
void light_draw(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	___njSetTexture(&texlist_ev_spotlight);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y + 0x8000 != 0)
	{
		njRotateY(0, (unsigned short)(0x8000 + var1->ang.y));
	}
	if (var1->ang.x != 0)
	{
		njRotateX(0, (unsigned short)var1->ang.x);
	}
	if (var1->ang.z != 0)
	{
		njRotateZ(0, (unsigned short)var1->ang.z);
	}
	FUN_0067d2d0(0, 0.5f, 1.0f, 0.5f);
	late_DrawObjectClipEx((struct obj *)&_object_heli_light_light, 0, 1.0f);
	njPopMatrix(1);
}

// STUB: SADX 0x007da3a0
void light_init(struct task *tp)
{
}

// FUNCTION: SADX 0x007da440
void light_turn(struct task *tp, float x, float y, float z)
{
	struct taskwk *var1 = tp->twp;
	var1->scl.x = x;
	var1->mode = 1;
	var1->scl.y = y;
	var1->scl.z = z;
}
