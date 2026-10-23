#include "decls.h"
extern int DAT_05b9d838;
extern struct NJS_MODEL model_casi_tuure01a_tuure01a[1];
extern struct NJS_MODEL model_casi_tuure01b_tuure01b[1];
extern struct NJS_MODEL model_casi_tuure02a_tuure02a[1];
extern struct NJS_MODEL model_casi_tuure02b_tuure02b[1];
extern struct NJS_MODEL model_casi_tuure03a_tuure03a[1];
extern struct NJS_MODEL model_casi_tuure03b_tuure03b[1];

// FUNCTION: SADX 0x008841e0
void DispUR(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture2(0x22);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, var1->ang.y);
	}
	ds_DrawModelClip((struct NJS_MODEL *)&model_casi_tuure01a_tuure01a, 1.0f);
	ds_DrawModelClip((struct NJS_MODEL *)&model_casi_tuure02a_tuure02a, 1.0f);
	ds_DrawModelClip((struct NJS_MODEL *)&model_casi_tuure03a_tuure03a, 1.0f);
	ds_DrawModelClip((struct NJS_MODEL *)&model_casi_tuure01b_tuure01b, 1.0f);
	ds_DrawModelClip((struct NJS_MODEL *)&model_casi_tuure02b_tuure02b, 1.0f);
	ds_DrawModelClip((struct NJS_MODEL *)&model_casi_tuure03b_tuure03b, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x00884330
void DispDL(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture2(0x22);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, var1->ang.y);
	}
	ds_DrawModelClip((struct NJS_MODEL *)&model_casi_tuule01b_tuule01b, 1.0f);
	ds_DrawModelClip((struct NJS_MODEL *)&model_casi_tuule02b_tuule02b, 1.0f);
	ds_DrawModelClip((struct NJS_MODEL *)&model_casi_tuule03b_tuule03b, 1.0f);
	njPopMatrix(1);
}

// STUB: SADX 0x008844d0
void NormalDL(struct task *tp)
{
}
