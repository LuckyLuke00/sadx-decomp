#include "decls.h"
extern struct NJS_TEXLIST texlist_ev_spotlight;
extern struct obj _object_heli_light_light[1];

// FUNCTION: SADX 0x007da1a0
void light_draw(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	___njSetTexture(&texlist_ev_spotlight);
	njPushMatrix((float *)0);
	njTranslateV((float *)0, &var1->pos);
	if (*(int *)((char *)var1 + 0x18) + 0x8000 == 0)
	{
	}
	else
	{
		njRotateY((float *)0, (unsigned short)(*(short *)((char *)var1 + 0x18) + 0x8000));
	}
	if (*(int *)((char *)var1 + 0x14) != 0)
	{
		njRotateX((float *)0, (unsigned short)*(short *)((char *)var1 + 0x14));
	}
	if (*(int *)((char *)var1 + 0x1c) != 0)
	{
		njRotateZ((float *)0, (unsigned short)*(short *)((char *)var1 + 0x1c));
	}
	FUN_0067d2d0((float *)0, 0.5f, 1.0f, 0.5f);
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
