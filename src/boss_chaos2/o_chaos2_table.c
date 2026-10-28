#include "decls.h"
extern int DAT_05b9d838;
extern struct taskwk *DAT_05b42a7c;
extern struct NJS_MODEL model_caos2obj_tenhana_tenhana[];

// FUNCTION: SADX 0x006eb690
void objNormal(struct task *pTask)
{
	struct taskwk *var1;

	var1 = pTask->twp;
	if (DAT_05b9d838 == 0)
	{
		if (CheckRangeOut(pTask) == 0)
		{
			if (FUN_004c39c0(pTask) == 0)
			{
				ObjectSetupInput(var1, NULL);
			}
			njPushMatrix(NULL);
			njTranslateV(NULL, &var1->pos);
			njPushMatrix(NULL);
			___njSetTexture((struct NJS_TEXLIST *)var1->value.ptr);
			if (var1->ang.y != 0)
			{
				njRotateY(NULL, (unsigned short)var1->ang.y);
			}
			ds_DrawObjectClip((struct obj *)var1->counter.ptr, 1.0f);
			njPopMatrix(1);
			FUN_0067d830(NULL, 0.0f, 7.5f, 0.0f);
			if (DAT_05b42a7c->ang.y != 0)
			{
				njRotateY(NULL, (unsigned short)DAT_05b42a7c->ang.y);
			}
			ds_DrawModelClip(&model_caos2obj_tenhana_tenhana[0], 1.0f);
			njPopMatrix(1);
		}
	}
}

// STUB: SADX 0x006eb780
void Object_c2_table(struct task *pTask)
{
}
