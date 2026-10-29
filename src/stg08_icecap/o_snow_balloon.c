#include "decls.h"
static void Normal(struct task *tp);
static void Disp(struct task *tp);

// FUNCTION: SADX 0x00860b50
static void Disp(struct task *tp)
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
	switch (var1->btimer)
	{
		case 0:
			ds_DrawModelClip((struct NJS_MODEL *)&model_obj_balloon_01_balloon_01, 1.0f);
			break;
		case 1:
			ds_DrawModelClip((struct NJS_MODEL *)&model_obj_balloon_02_balloon_02, 1.0f);
			break;
		case 2:
			ds_DrawModelClip((struct NJS_MODEL *)&model_obj_balloon_03_balloon_03, 1.0f);
			break;
		case 3:
			ds_DrawModelClip((struct NJS_MODEL *)&model_obj_balloon_04_balloon_04, 1.0f);
			break;
	}
	njPopMatrix(1);
}

#pragma optimize("", off)
// STUB: SADX 0x00860c00
static void Normal(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00860c80
void ObjectSnowBalloon01(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->timer.f = 1.0;
	var1->counter.l = 0x66;
	var1->btimer = 0;
	tp->exec = Normal;
	tp->disp = Disp;
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
}

// FUNCTION: SADX 0x00860cb0
void ObjectSnowBalloon02(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->timer.f = 1.0;
	var1->counter.l = 0x66;
	var1->btimer = 1;
	tp->exec = Normal;
	tp->disp = Disp;
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
}

// FUNCTION: SADX 0x00860ce0
void ObjectSnowBalloon03(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->timer.f = 1.0;
	var1->counter.l = 0x66;
	var1->btimer = 2;
	tp->exec = Normal;
	tp->disp = Disp;
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
}

// FUNCTION: SADX 0x00860d10
void ObjectSnowBalloon04(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->timer.f = 1.0;
	var1->counter.l = 0x66;
	var1->btimer = 3;
	tp->exec = Normal;
	tp->disp = Disp;
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
}
