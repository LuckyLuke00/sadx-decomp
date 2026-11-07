#include "decls.h"
#include <stdlib.h>

// GLOBAL: SADX 0x04ad8624
static struct NJS_SPRITE sprite_o_bubble;

extern int DAT_05b9d838;
extern "C" int rand(void);

// FUNCTION: SADX 0x008b2a40
void PieceDisp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		SetObjectTexture();
		njPushMatrix(NULL);
		njTranslateV(NULL, &var1->pos);
		if (var1->ang.x != 0)
		{
			njRotateX(NULL, (unsigned short)var1->ang.x);
		}
		if (var1->ang.y != 0)
		{
			njRotateY(NULL, (unsigned short)var1->ang.y);
		}
		SetMaterial(var1->value.f, 0.0f, 0.0f, 0.0f);
		late_DrawModelClip(*(struct NJS_MODEL **)((char *)var1->timer.ptr + 4), 0, 1.0f);
		ResetMaterial();
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x008b2af0
void BubbleDisp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838 == 0)
	{
		sprite_o_bubble.p.x = var1->pos.x;
		sprite_o_bubble.p.y = var1->pos.y;
		sprite_o_bubble.p.z = var1->pos.z;
		___njColorBlendingMode(0, 8);
		___njColorBlendingMode(1, 10);
		SetMaterial(1.0f, 1.0f, 1.0f, 1.0f);
		___njDrawSprite3D(&sprite_o_bubble, 0, 0x32);
	}
}

// FUNCTION: SADX 0x008b2d20
void BubbleExec(struct task *tp)
{
	struct taskwk *var1;
	float var2;
	var1 = tp->twp;
	var2 = var1->timer.f + var1->pos.y;
	var1->pos.y = var2;
	if (var1->counter.f < var2)
	{
		FreeTask(tp);
	}
	BubbleDisp(tp);
}

// FUNCTION: SADX 0x008b2e50
void BubbleInit(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	int var2 = rand();
	tp->exec = BubbleExec;
	tp->disp = BubbleDisp;
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
	var1->timer.f = (float)var2 * 3.0517578e-5f;
	var1->timer.f = var1->timer.f * 0.5f + 0.2f;
}

// STUB: SADX 0x008b32d0
void ObjShelterKowaresuisou(struct task *tp)
{
}
