#include "decls.h"
extern int DAT_05b9d838;
extern "C" int rand(void);

// FUNCTION: SADX 0x008b2a40
void PieceDisp(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		SetObjectTexture();
		njPushMatrix((float *)0);
		njTranslateV((float *)0, &var1->pos);
		if (*(int *)((char *)var1 + 0x14) != 0)
		{
			njRotateX((float *)0, *(unsigned short *)((char *)var1 + 0x14));
		}
		if (*(int *)((char *)var1 + 0x18) != 0)
		{
			njRotateY((float *)0, *(unsigned short *)((char *)var1 + 0x18));
		}
		SetMaterial(*(float *)((char *)var1 + 0x10), 0.0f, 0.0f, 0.0f);
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
	var2 = var1->timer.f + *(float *)((char *)var1 + 0x24);
	*(float *)((char *)var1 + 0x24) = var2;
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
	var1->timer.f = (float)var2 * 3.0517578125e-05f;
	var1->timer.f = var1->timer.f * 0.5f + 0.2f;
}
