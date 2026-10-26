#include "decls.h"
static void Display(struct task *tp);
extern struct NJS_ARGB DAT_02b7ee4c;
extern struct NJS_ARGB DAT_02b7ee5c;
extern struct NJS_TEXANIM anim_Chaos7SDamage[1];
extern struct NJS_SPRITE sprite_Chaos7SDamage;
extern int DAT_05b9d838;
extern "C" int rand(void);

// FUNCTION: SADX 0x007014b0
static void Display(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	___njFogDisable();
	___njSetConstantMaterial(&DAT_02b7ee4c);
	___njColorBlendingMode(0, 0xa);
	___njColorBlendingMode(1, 0xa);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	anim_Chaos7Damage[0].texid = (short)(long)var1->counter.f;
	late_DrawSprite3D(&sprite_Chaos7Damage, 0, 0x30, 4);
	njPopMatrix(1);
	___njFogEnable();
}

// FUNCTION: SADX 0x00701530
void NormalD(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->counter.f = var1->counter.f + 0.3333333432674408;
	if (var1->counter.f >= 16.0)
	{
		FreeTask(tp);
	}
	else
	{
		Display(tp);
	}
}

// FUNCTION: SADX 0x00701570
void Sprite_Chaos7Damage(struct task *tp)
{
	tp->exec = NormalD;
	tp->disp = Display;
	tp->twp->counter.f = 0.0f;
}

// FUNCTION: SADX 0x00701590
void DisplayS(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	___njFogDisable();
	___njSetConstantMaterial(&DAT_02b7ee5c);
	___njColorBlendingMode(0, 0xa);
	___njColorBlendingMode(1, 0xa);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	anim_Chaos7SDamage[0].texid = *(short *)((char *)var1 + 0xe) + 0x10;
	sprite_Chaos7SDamage.sy = var1->scl.x;
	sprite_Chaos7SDamage.sx = sprite_Chaos7SDamage.sy;
	late_DrawSprite3D(&sprite_Chaos7SDamage, 0, 0x30, 4);
	njPopMatrix(1);
	___njFogEnable();
}

// STUB: SADX 0x00701620
void NormalS2(struct task *tp)
{
}

// FUNCTION: SADX 0x00701660
void Sprite_Chaos7DamageS2(struct task *tp)
{
	tp->exec = NormalS2;
	tp->disp = DisplayS;
	tp->twp->timer.l = 0;
}

// STUB: SADX 0x00701860
void DisplayMist(struct task *tp)
{
}

// STUB: SADX 0x00701950
void NormalMist(struct task *tp)
{
}

// STUB: SADX 0x00701c50
void SetMistDisplayTask(struct task *tp)
{
}

// FUNCTION: SADX 0x00701dd0
void objNormalR(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->counter.f = var1->counter.f + 0.33333334f;
	if (var1->counter.f >= 16.0f)
	{
		var1->timer.b[0]--;
		if (var1->timer.b[0] > 0)
		{
			var1->counter.f = 0.0f;
		}
		else
		{
			FreeTask(tp);
		}
	}
	objDisplayR(tp);
}

// FUNCTION: SADX 0x00701e30
void Chaos7NodamageEffect(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	var1->counter.f = 0.0f;
	var1->timer.b[0] = 3;
	tp->exec = objNormalR;
	tp->disp = objDisplayR;
}

// STUB: SADX 0x00701e50
void NormalS(struct task *tp)
{
}

// FUNCTION: SADX 0x00701f00
void Sprite_Chaos7DamageS(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	tp->exec = NormalS;
	tp->disp = DisplayS;
	var1->counter.f = 0.0f;
	var1->timer.l = 0;
	float var2 = (float)rand() * 3.0517578125e-05;
	var1->scl.x = var2 + 0.5;
}
