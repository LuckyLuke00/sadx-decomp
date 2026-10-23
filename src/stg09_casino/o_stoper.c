#include "decls.h"
extern struct NJS_MODEL model_casi_stop01a_stop01a[];
extern struct NJS_MODEL model_casi_stop01a_k_stop01a_k[];
extern struct NJS_MODEL model_casi_stop02a_k_stop02a_k[];
extern int DAT_05b9d838;
extern int DAT_060dbcb0;

// FUNCTION: SADX 0x00886090
void DispC(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture2(0x22);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (!(DAT_060dbcb0 & 1))
	{
		late_DrawModelClipEx((struct NJS_MODEL *)&model_casi_stop02b_k_stop02b_k, 1, 1.0f);
		FUN_0067d830(0, 0.0f, var1->timer.f, 0.0f);
		late_DrawModelClipEx((struct NJS_MODEL *)&model_casi_stop01b_k_stop01b_k, 1, 1.0f);
	}
	else
	{
		late_DrawModelClipEx((struct NJS_MODEL *)&model_casi_stop02b_stop02b, 1, 1.0f);
		FUN_0067d830(0, 0.0f, var1->timer.f, 0.0f);
		late_DrawModelClipEx((struct NJS_MODEL *)&model_casi_stop01b_stop01b, 1, 1.0f);
	}
	njPopMatrix(1);
}

// FUNCTION: SADX 0x00886150
void DispLR(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		SetObjectTexture2(0x22);
		njPushMatrix(NULL);
		njTranslateV(NULL, &var1->pos);
		if (var1->ang.y != 0)
		{
			njRotateY(NULL, (unsigned short)var1->ang.y);
		}
		if ((var1->mode == 1 && (DAT_060dbcb0 & 2) == 0) || (var1->mode == 2 && (DAT_060dbcb0 & 4) == 0))
		{
			late_DrawModelClip(&model_casi_stop02a_k_stop02a_k[0], 1, 1.0f);
			if (var1->ang.x != 0)
			{
				njRotateX(NULL, (unsigned short)var1->ang.x);
			}
			late_DrawModelClip(&model_casi_stop01a_k_stop01a_k[0], 1, 1.0f);
		}
		else
		{
			late_DrawModelClip(&model_casi_stop01a_k_stop01a_k[0], 1, 1.0f);
			if (var1->ang.x != 0)
			{
				njRotateX(NULL, (unsigned short)var1->ang.x);
			}
			late_DrawModelClip(&model_casi_stop01a_stop01a[0], 1, 1.0f);
		}
		njPopMatrix(1);
	}
}

// STUB: SADX 0x00886240
void cNormalLR(struct task *ctp)
{
}

// STUB: SADX 0x008862e0
void NormalC(struct task *tp)
{
}

// STUB: SADX 0x008863a0
void NormalL(struct task *tp)
{
}

// STUB: SADX 0x008864a0
void NormalR(struct task *tp)
{
}
