#include "decls.h"

// FUNCTION: SADX 0x0085bcb0
void EffectColdGenerator(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	var1->counter.f = (float)var1->ang.x / 65535.0;
	var1->timer.f = (float)var1->ang.y / 65535.0;
	tp->exec = EffectColdGeneratorMain;
}

// FUNCTION: SADX 0x0085bce0
void EffectSnowPieceDisplay(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	float var2 = var1->value.f;
	___njSetTexture(&texlist_piece[0]);
	njPushMatrix((float *)0);
	njTranslateV((float *)0, &var1->pos);
	if (*(int *)((char *)var1 + 0x1c) != 0)
	{
		njRotateZ((float *)0, (unsigned short)*(short *)((char *)var1 + 0x1c));
	}
	if (*(int *)((char *)var1 + 0x14) != 0)
	{
		njRotateX((float *)0, *(unsigned short *)((char *)var1 + 0x14));
	}
	if (*(int *)((char *)var1 + 0x18) != 0)
	{
		njRotateY((float *)0, *(unsigned short *)((char *)var1 + 0x18));
	}
	FUN_0067d2d0((float *)0, var2, var2, var2);
	ds_DrawObjectClip(&object_s_yukitsubu_yukitsubu[0], var2);
	njPopMatrix(1);
}

// STUB: SADX 0x0085bd90
void EffectSnowPieceExecute(struct task *tp)
{
}
