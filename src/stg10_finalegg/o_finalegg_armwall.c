#include "decls.h"
struct task;

// FUNCTION: SADX 0x00897400
void WallPartsDisplayer(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	SetObjectTexture();
	njPushMatrix(NULL);
	njTranslateV((float *)0, &var1->pos);
	if (*(int *)((char *)var1 + 0x18) != 0)
	{
		njRotateY(NULL, *(unsigned short *)((char *)var1 + 0x18));
	}
	if (*(int *)((char *)var1 + 0x1c) != 0)
	{
		njRotateX(NULL, *(unsigned short *)((char *)var1 + 0x1c));
	}
	___dsDrawModel((struct NJS_MODEL *)var1->counter.ptr);
	njPopMatrix(1);
}

// STUB: SADX 0x008974f0
void EffectArmFlash(struct sp_task *tp, struct sp_link *lp)
{
}

// FUNCTION: SADX 0x008975c0
void FUN_008975c0(struct task *param_1)
{
	struct taskwk *var1 = param_1->twp;

	SetObjectTexture();
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, (Uint16)var1->ang.y);
	}
	ds_DrawObjectClip(object_kowarekabe_mae_mae, 1.0f);
	njPopMatrix(1);
}
