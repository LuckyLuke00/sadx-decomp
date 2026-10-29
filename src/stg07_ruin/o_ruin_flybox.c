#include "decls.h"
extern int DAT_05b9d838;
extern void FUN_0067d830(float *param_1, float param_2, float param_3, float param_4);

// FUNCTION: SADX 0x00851c80
void DrawHasira(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		SetObjectTexture();
		njPushMatrix(NULL);
		njTranslateV(NULL, &var1->pos);
		if (*(int *)((char *)var1 + 0x1c) != 0)
		{
			njRotateZ(NULL, (unsigned short)*(short *)((char *)var1 + 0x1c));
		}
		if (*(int *)((char *)var1 + 0x14) != 0)
		{
			njRotateX(NULL, *(unsigned short *)((char *)var1 + 0x14));
		}
		if (*(int *)((char *)var1 + 0x18) != 0)
		{
			njRotateY(NULL, *(unsigned short *)((char *)var1 + 0x18));
		}
		FUN_0067d830((float *)0, 0.0f, *(float *)((char *)var1 + 0x30), 0.0f);
		ds_DrawModelClip(&model_lwobj_prop_a01_prop_a01[0], 1.0f);
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x00851e70
void DrawNormHasira(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		SetObjectTexture();
		njPushMatrix(NULL);
		njTranslateV(NULL, &var1->pos);
		if (*(int *)((char *)var1 + 0x1c) != 0)
		{
			njRotateZ(NULL, (unsigned short)*(short *)((char *)var1 + 0x1c));
		}
		if (*(int *)((char *)var1 + 0x14) != 0)
		{
			njRotateX(NULL, *(unsigned short *)((char *)var1 + 0x14));
		}
		if (*(int *)((char *)var1 + 0x18) != 0)
		{
			njRotateY(NULL, *(unsigned short *)((char *)var1 + 0x18));
		}
		FUN_0067d830((float *)0, 0.0f, *(float *)((char *)var1 + 0x30), 0.0f);
		ds_DrawModelClip(&model_lwobj_prop_a02_prop_a02[0], 1.0f);
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x00851f20
void ObjectRuinUkidai(struct task *tp)
{
	tp->twp->timer.ptr = object_ukidai_ukidai_ukidai;
	ObjectGCollision(tp);
}
